#include <msp430f169.h>
#include "Config.h"
//#include <stdio.h>
//#include <string.h>
#include "LCD1602.h"


void UART_Init()
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
}

//*************************************************************************
//              串口0发送数据函数
//*************************************************************************

void Send_Byte(uchar data)
{
  while((IFG1&UTXIFG0)==0);          //发送寄存器空的时候发送数据
    U0TXBUF=data;
}

//*************************************************************************
//               处理来自串口 0 的接收中断
//*************************************************************************

#pragma vector=USART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  uchar data=0;
  data=U0RXBUF;
  P6OUT=~data;//接收到的数据存起来
  Send_Byte(data);                    //将接收到的数据再发送出去
  LCD_write_single_char(0,0,data+'30');
}


//*************************************************************************
//           主函数
//*************************************************************************
void main(void)
{
    P6DIR=0xff;
    P6OUT=0xff;
    WDT_Init();                         //看门狗设置
    Clock_Init();                       //系统时钟设置
    UART_Init();                        //串口设置初始化
    _EINT();                            //开中断                               //无限循环
     while(1)
     {
         Send_Byte(0x02);
     }

}

