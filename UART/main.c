/*
 * main.c
 *
 *  Created on: 2018��11��11��
 *      Author: Cal
 */

#include"UART.h"

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX_ISR(void)
{
  unsigned char data=0;
  data=U0RXBUF;                       //���յ������ݴ�����
  Uart0Send_Byte(data);                    //�����յ��������ٷ��ͳ�ȥ

}


#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX_ISR(void)
{

}

#pragma vector=USART1RX_VECTOR
__interrupt void USART1_RX_ISR(void)
{
  unsigned char data=0;
  data=U1RXBUF;                       //���յ������ݴ�����
  Uart1Send_Byte(data);                    //�����յ��������ٷ��ͳ�ȥ

}


#pragma vector=USART1TX_VECTOR
__interrupt void USART1_TX_ISR(void)
{

}
void main(){
    WDTCTL = WDTPW | WDTHOLD;//�رտ��Ź�
    Clock_Init();
    UART0_Init();
    UART1_Init();
    while(1){
        Uart1Send_Byte(0x24);
        Uart0Send_Byte(0x65);
        delay_ms(500);
    }

}


