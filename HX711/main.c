#include <msp430.h>
#include<stdio.h>
#include "Config.h"
#include "UART.h"
#include "HX711.h"
#include "IIC.h"
//#include "OLED.h"

/*
 * 暂时使用串口显示数据，发现问题有，压得越重数值越小！
 * 需要解决！
 * 压的问题解决，现在解决示数问题！
 * 示数问题解决，现在解决OLED显示问题，暂时无其他问题。
 * OLED显示出现问题，想改数据口使用12864或1602显示，或者使用SPI接口的OLED显示。
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
//    OLED_init();
//    clearOLED();
    unsigned char data[10];
    int z = 0;
    while(1){
        shu = HX711_Read();
//        if(cishu<5){
//            chushi = shu;
//            cishu++;
//        }
//        shu = shu-chushi;
//        OLED_ShowNum(0,0,shu,5);
        sprintf(data,"%d",shu);
        for(z=0;z<10;z++)
            Uart0Send_Byte(data[z]);
        delay_ms(100);
//        NewClear(1);
    }
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

#pragma vector=USART1RX_VECTOR
__interrupt void USART1_RX_ISR(void)
{
    unsigned char data=0;
    data=U1RXBUF;                       //接收到的数据存起来
    Uart1Send_Byte(data);               //将接收到的数据再发送出去

}


#pragma vector=USART1TX_VECTOR
__interrupt void USART1_TX_ISR(void)
{

}
