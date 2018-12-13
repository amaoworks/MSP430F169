/*
 * SRF05.c
 *
 *  Created on: 2018��12��13��
 *      Author: Brown
 */
#include "SRF05.h"

extern unsigned int  TA_Overflow_Cnt;
extern unsigned long Period;
extern unsigned long S;
extern unsigned int  distance;
extern unsigned int  RiseCapVal;
extern unsigned char Edge;
extern unsigned char disbuff[4];
extern unsigned char temp,A1,A2,A3,A4;

//��ʼ����ʱ��A����
void init_timerA()
{
    TACTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3;//SMCLK,�����������ж���������������
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//����ģʽ�������ز���CCI1A���룬ͬ�������ж�����
}

//SRF05ģ����ƿڳ�ʼ������
void SRF05_IOinit()
{
    P1DIR |= BIT4;                  //P1.4���
    P1DIR &=~ BIT2;                 //P1.2����
    P1SEL =  BIT2;                  //P1.2�ڶ����ܣ���������

    P1OUT &=~BIT4;                  //����P14���ƶ�
    delay_ms(1000);
}

//��ʱ��A�������
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{

    switch(TAIV)
    {
    case 2 :if(Edge==RISE)
    {
        RiseCapVal = TACCR1;
        TACCTL1 |= CAP+CM_2+CCIS_0+SCS+CCIE;//��Ϊ�½��ز���
        //TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//��Ϊ�����ز���
        Edge = FALL;//�½��ز����־
    }
    else
    {
        _DINT();

        Period = TACCR1-RiseCapVal;
        S=(Period*17)/100;
        TACCR1 = 0;
        TACCTL1|= CAP+CM_1+CCIS_0+SCS+CCIE;//��Ϊ�����ز���
        Edge = RISE;//�����ز����־
        _EINT();
    }
    break;
    case 4 : break;
    case 10: TA_Overflow_Cnt++;
    break;
    }
}
