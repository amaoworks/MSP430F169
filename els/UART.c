/*
 * UART.c
 *
 *  Created on: 2018��12��28��
 *      Author: yule
 */
#include "UART.h"

void UART0_Init()
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
//  _EINT();
}


void Uart0Send_Byte(unsigned char data)
{
  while((IFG1&UTXIFG0)==0);          //���ͼĴ����յ�ʱ��������
    U0TXBUF=data;
}

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX_ISR(void)
{
  unsigned char data=0;
  data=U0RXBUF;                       //���յ������ݴ�����
  Uart0Send_Byte(data);               //�����յ��������ٷ��ͳ�ȥ
}

#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX_ISR(void)
{

}
