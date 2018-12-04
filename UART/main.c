/*
 * main.c
 *
 *  Created on: 2018年11月11日
 *      Author: Cal
 */

#include"UART.h"

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX_ISR(void)
{
  unsigned char data=0;
  data=U0RXBUF;                       //接收到的数据存起来
  Uart0Send_Byte(data);                    //将接收到的数据再发送出去

}


#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX_ISR(void)
{

}

#pragma vector=USART1RX_VECTOR
__interrupt void USART1_RX_ISR(void)
{
  unsigned char data=0;
  data=U1RXBUF;                       //接收到的数据存起来
  Uart1Send_Byte(data);                    //将接收到的数据再发送出去

}


#pragma vector=USART1TX_VECTOR
__interrupt void USART1_TX_ISR(void)
{

}
void main(){
    WDTCTL = WDTPW | WDTHOLD;//关闭看门狗
    Clock_Init();
    UART0_Init();
    UART1_Init();
    while(1){
        Uart1Send_Byte(0x24);
        Uart0Send_Byte(0x65);
        delay_ms(500);
    }

}


