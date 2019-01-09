#include <msp430x16x.h>
#include "GUI.h"
#include "TFT2.8.h"
#include "Touch.h"
#include "Touch_operation.h"
#define uchar unsigned char
#define uint unsigned int
unsigned int LCD_X,LCD_Y;
unsigned char Display_flag=0;
unsigned char Display_flag1=0;
//**************�����ⲿ�����ͱ���********************
uchar button;
//**************�����ⲿ�����ͱ���********************
extern void delayms(unsigned int count);
/********************************************************************
            ��ʼ��IO���ӳ���
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;
  P3SEL=0x00;                    //����IO��Ϊ��ͨI/Oģʽ
  P3DIR = 0xff;                  //����IO�ڷ���Ϊ���
  P3OUT = 0x00;                  //��ʼ����Ϊ00,LED������IO��
  P2SEL = 0x00;
  P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;               //����������
}

/********************************************************************
    LED��˸һ�Σ�������Ҫ�鿴����ִ��λ��ʱ������ã����ƶϵ�
********************************************************************/
void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //��XT2����
  BCSCTL2|=SELM1+SELS;              //MCLKΪ8MHZ��SMCLKΪ8MHZ
  do{
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
  IFG1&=~OFIFG;
}

void touch_my_screen()
{
    if(Getpix()==1)
    {
        CLR_Screen(White);               //�ñ���ɫ����
    }
}

/********************************************************************
                      ������
********************************************************************/
void main()
{  // unsigned char i,j;
    WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
    Clock_Init();                      //ϵͳʱ������
    Port_Init();                       //ϵͳ��ʼ��������IO������
    Device_code=0x9320;                //TFT����IC�ͺ�
    TFT_Initial();                     //��ʼ��LCD
    start_7843();
    CLR_Screen(White);               //�ñ���ɫ����
    while(1)                           //ѭ��ִ�г���
    {
        touch_my_screen();
        PutString(0,0,"�Ž�ѧԺ",Red,White);
    }
}
