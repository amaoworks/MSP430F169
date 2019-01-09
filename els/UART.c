/*
 * UART.c
 *
 *  Created on: 2018年12月28日
 *      Author: yule
 */
#include "UART.h"

void UART0_Init()
{
  U0CTL|=SWRST;               //复位SWRST
  U0CTL|=CHAR;                //8位数据模式
  U0TCTL|=SSEL1;              //SMCLK为串口时钟
  U0BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;               //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                //微调寄存器为0，波特率9600bps
  ME1|=UTXE0;                 //UART0发送使能
  ME1|=URXE0;                 //UART0接收使能
  U0CTL&=~SWRST;
  IE1|=URXIE0;                //接收中断使能位

  P3SEL|= BIT4;               //设置IO口为普通I/O模式
  P3DIR|= BIT4;               //设置IO口方向为输出
  P3SEL|= BIT5;
//  _EINT();
}


void Uart0Send_Byte(unsigned char data)
{
  while((IFG1&UTXIFG0)==0);          //发送寄存器空的时候发送数据
    U0TXBUF=data;
}

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX_ISR(void)
{
  unsigned char data=0;
  data=U0RXBUF;                       //接收到的数据存起来
  Uart0Send_Byte(data);               //将接收到的数据再发送出去
}

#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX_ISR(void)
{

}
