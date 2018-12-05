#include <msp430.h>
#include<stdio.h>
#include "Config.h"
#include "UART.h"
#include "HX711.h"

/*
 * ��ʱʹ�ô�����ʾ���ݣ����������У�ѹ��Խ����ֵԽС��
 * ��Ҫ�����
 * ѹ�������������ڽ��ʾ�����⣡
 * 15:32
 */

int shu = 0;
uchar cishu = 0;
int chushi = 0;
/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    Clock_Init();
    UART0_Init();
    unsigned char data[10];
    int z = 0;
    while(1){
        Uart0Send_Byte(0x65);
        shu = HX711_Read();
        if(cishu<5){
            chushi = shu;
            cishu++;
        }
        shu = shu-chushi;
        sprintf(data,"%d",shu);
        for(z=0;z<10;z++)
            Uart0Send_Byte(data[z]);
        delay_ms(100);
    }
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

#pragma vector=USART1RX_VECTOR
__interrupt void USART1_RX_ISR(void)
{
    unsigned char data=0;
    data=U1RXBUF;                       //���յ������ݴ�����
    Uart1Send_Byte(data);               //�����յ��������ٷ��ͳ�ȥ

}


#pragma vector=USART1TX_VECTOR
__interrupt void USART1_TX_ISR(void)
{

}
