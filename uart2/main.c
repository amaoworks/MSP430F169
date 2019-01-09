#include <msp430f169.h>
#include "Config.h"
//#include <stdio.h>
//#include <string.h>
#include "LCD1602.h"


void UART_Init()
{
  U0CTL|=SWRST;               //��λSWRST
  U0CTL|=CHAR;                //8λ����ģʽ
  U0TCTL|=SSEL1;              //SMCLKΪ����ʱ��
  U0BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //΢���Ĵ���Ϊ0��������9600bps
  ME1|=UTXE0;                 //UART0����ʹ��
  ME1|=URXE0;                 //UART0����ʹ��
  U0CTL&=~SWRST;
  IE1|=URXIE0;                //�����ж�ʹ��λ

  P3SEL|= BIT4;               //����IO��Ϊ��ͨI/Oģʽ
  P3DIR|= BIT4;               //����IO�ڷ���Ϊ���
  P3SEL|= BIT5;
}

//*************************************************************************
//              ����0�������ݺ���
//*************************************************************************

void Send_Byte(uchar data)
{
  while((IFG1&UTXIFG0)==0);          //���ͼĴ����յ�ʱ��������
    U0TXBUF=data;
}

//*************************************************************************
//               �������Դ��� 0 �Ľ����ж�
//*************************************************************************

#pragma vector=USART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  uchar data=0;
  data=U0RXBUF;
  P6OUT=~data;//���յ������ݴ�����
  Send_Byte(data);                    //�����յ��������ٷ��ͳ�ȥ
  LCD_write_single_char(0,0,data+'30');
}


//*************************************************************************
//           ������
//*************************************************************************
void main(void)
{
    P6DIR=0xff;
    P6OUT=0xff;
    WDT_Init();                         //���Ź�����
    Clock_Init();                       //ϵͳʱ������
    UART_Init();                        //�������ó�ʼ��
    _EINT();                            //���ж�                               //����ѭ��
     while(1)
     {
         Send_Byte(0x02);
     }

}

