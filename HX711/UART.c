/*
 * UART.c
 *
 *  Created on: 2018年12月3日
 *      Author: Brown
 */
#include"UART.h"

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
    _EINT();
}


void Uart0Send_Byte(unsigned char data)
{
    while((IFG1&UTXIFG0)==0);          //发送寄存器空的时候发送数据
    U0TXBUF=data;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//UART1
////////////////////////////////////////////////////////////////////////////////////////////////

void UART1_Init()
{
    U1CTL|=SWRST;               //复位SWRST
    U1CTL|=CHAR;                //8位数据模式
    U1TCTL|=SSEL1;              //SMCLK为串口时钟
    U1BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
    U1BR0=baud_l;               //N=UBR+(UxMCTL)/8
    U0MCTL=0x00;                //微调寄存器为0，波特率9600bps
    ME2|=UTXE1;                 //UART0发送使能
    ME2|=URXE1;                 //UART0接收使能
    U1CTL&=~SWRST;
    IE2|=URXIE1;                //接收中断使能位

    P3SEL|= BIT6;               //设置IO口为普通I/O模式
    P3DIR|= BIT6;               //设置IO口方向为输出
    P3SEL|= BIT7;
    _EINT();
}


void Uart1Send_Byte(unsigned char data)
{
    while((IFG2&UTXIFG1)==0);          //发送寄存器空的时候发送数据
    U1TXBUF=data;
}
