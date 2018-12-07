#include <msp430f169.h>
#include "Config.h"
#include "LCD.h"
#include "PWM.h"
#include "UART.h"
#include "ADC.h"

unsigned char key = 0;
unsigned char Statu = 0;
unsigned int a = 0;
unsigned char ths = 0;
unsigned int long temp;
unsigned int long TemperC;                                   //�����¶�
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

    ADC12_Init();

    _BIS_SR(GIE);               // ����ϵͳ�ж�
    UART0_Init();

    LCD_Desk();                 // �����ʼ��ʾ�ַ�
    LCD_Write_str(7,0,"OFF");

    while(1){
        ADC12CTL0 |= ADC12SC;                                //��ʼ������ADת��

        TemperC = (temp - 2692) * 423;
        TemperC = TemperC / 4096;                            //�򻯵������¶�ת����ʽ
        LCD_Display_num(13,1,TemperC);

        switch(key){
        case 49:start();LCD_Write_str(6,0,"ON   ");LCD_Write_str(7,1,"0");break;
        case 50:speed(1);LCD_Write_str(6,0,"ON   ");LCD_Display_num(7,1,1);break;
        case 51:speed(2);LCD_Write_str(6,0,"ON   ");LCD_Display_num(7,1,2);break;
        case 52:speed(3);LCD_Write_str(6,0,"ON   ");LCD_Display_num(7,1,3);break;
        case 53:stop();LCD_Write_str(6,0,"OFF  ");LCD_Write_str(7,1," ");break;
        case 54:ths=1;LCD_Write_str(6,0,"Smart");LCD_Write_str(7,1,"S");break;
        default:break;
        }
        while(ths == 1){
            ADC12CTL0 |= ADC12SC;
            Smart_speed();
            LCD_Display_num(13,1,TemperC);
        }
        key=0;
    }
}
