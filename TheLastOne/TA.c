/*
 * TA.c
 *
 *  Created on: 2018��12��29��
 *      Author: Brown
 */
#include "TA.h"

extern int Asecond , count;

//TIMERA��ʼ��������ΪUPģʽ����
void TIMERA_Init(void)                                   //UPģʽ��������������ΪCCR0+1
{
    TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK��ʱ��Դ��8��Ƶ�����Ӽ���ģʽ�����ж�
    TACCR0 = 9999;                                         //CCR0=9999��10ms�ж�һ��
    _EINT();
}

//�رռ�ʱ����ͣ����
void TimerA_end(void)
{
    TACTL &= 0xfffd;
    Asecond = 0;
    _DINT();
}

//TIMERA�жϷ��������Ҫ�ж��ж�����
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
    switch(TAIV)                                  //��Ҫ�ж��жϵ�����
    {
    case 2:break;
    case 4:break;
    case 10:count++;break;                         //���ñ�־λFlag
    }
    if(count==100)                                 //100��Ϊ1��
    {
        Asecond++;
        count=0;
    }
}
