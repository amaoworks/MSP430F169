#include <msp430f169.h>
#include "Config.h"
#include "LCD.h"
#include "PWM.h"
#include "UART.h"
//#include "Key.h"

unsigned char key = 0;
unsigned char Statu = 0;
unsigned int a = 0;

/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    Clock_Init(1);              // 0 ���� 1M�� 1 ���� 8M

    PWM_init();                 // Init the PWM

    LCD_Port_init();            // Init the LCD1602
    LCD_Init();

    UART0_Init();

    while(1){
        LCD_Desk();
        switch(key){
        case 49:start();LCD_Write_str(7,0,"ON ");LCD_Write_str(7,1,"0");break;
        case 50:speed(1);LCD_Display_num(7,1,1);break;
        case 51:speed(2);LCD_Display_num(7,1,2);break;
        case 52:speed(3);LCD_Display_num(7,1,3);break;
        case 53:stop();LCD_Write_str(7,0,"OFF");LCD_Write_str(7,1," ");break;
        default:break;
        }
        key=0;
    }
}

#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX_ISR(void)
{
  unsigned char data=0;
  data=U0RXBUF;                       //���յ������ݴ�����
  key = data;
  Uart0Send_Byte(data);               //�����յ��������ٷ��ͳ�ȥ

}


#pragma vector=USART0TX_VECTOR
__interrupt void USART0_TX_ISR(void)
{

}

//#pragma vector = PORT1_VECTOR
//__interrupt void p1init(void)
//{
//
//    if((P1IN&BIT0)==0){
//        Keyvalue = 1;
//        statu = ~statu;
//    }
//
//    if((P1IN&BIT1)==0){
//        Keyvalue = 2;
//    }
//
//    if((P1IN&BIT2)==0){
//        Keyvalue = 3;
//    }
//
//    if((P1IN&BIT3)==0){
//        Keyvalue = 4;
//    }
//
//    delay_ms(100);
//    P1IFG=0;                    //�жϱ�־λ���㣡����P1�˿��ⲿ�жϲ����Զ����㣬������Ҫ�ֶ�����
//}

