/*
 * SRF05.c
 *
 *  Created on: 2018��12��17��
 *      Author: hp
 */
#include"SRF05.h"

extern unsigned int TA_Overflow_Cnt;         //TA���������ű���
extern unsigned long int Period;             //�����Ž������
extern unsigned long int S;                  //��������λΪ����
extern unsigned int  RiseCapVal;               //������ʱ�̲���ֵ��ű���
extern unsigned char Edge;                 //��ǰ������ ��ʼֵΪ������
extern unsigned char temp,A1,A2,A3,A4,open;            //����ı���,��ʾ���ݴ���
extern char   Temp_Value[7];

/********************************************************************
    ��ʼ����ʱ��A����
********************************************************************/
void init_timerA()
{
  TACTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3;//SMCLK,�����������ж���������������
  TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//����ģʽ�������ز���CCI1A���룬ͬ�������ж�����
}

/********************************************************************
    SRF05ģ����ƿڳ�ʼ������
********************************************************************/
void SRF05_IOinit()
{
  P1DIR |= BIT4;                  //P1.4���
  P1DIR &=~ BIT2;                 //P1.2����
  P1SEL =  BIT2;                  //P1.2�ڶ����ܣ���������

  P1OUT &=~BIT4;                  //����P1.4���ƶ�
  delay_ms(1000);
  //P1�˿��ⲿ�ж�
//   P1DIR|=0X00;  //P1.0��P1.1��P1.2��P1.3Ϊ����ģʽ
//   P1IE|=0X0F;   //P1.0��P1.1��P1.2��P1.3�����ж�
//   P1IES|=0x0F;  //P1.0��P1.1��P1.2��P1.3Ϊ�½��ش���
}

//*************************************************************************
//      ����ֵ������
//*************************************************************************
void Data_do(uint temp_d)
{
  uint temp_1,temp_2;
  A1=temp_d/1000;                       //�ֳ�ǧ���٣�ʮ���͸�λ
  temp_1=temp_d%1000;
  A2=temp_1/100;
  temp_2=temp_1%100;
  A3=temp_2/10;
  A4=temp_2%10;

  Temp_Value[0]=A1+0x30;
  Temp_Value[1]='.';
  Temp_Value[2]=A2+0x30;
  Temp_Value[3]=A3+0x30;
  Temp_Value[4]=A3+0x30;
  Temp_Value[5]='m';
  Temp_Value[6]=' ';
}

void Auto(){
    if(S < 1000){
        open = 1;
    }else{
        open = 0;
    }
}

/********************************************************************
                      ��ʱ��A�������
********************************************************************/
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
