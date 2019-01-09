#include <msp430f169.h>
#include "Config.h"
#include "SRF05.h"
#include "LCD.h"
#include "Key.h"
#include "LED.h"

//ʹ�õ�ȫ�ֱ���
unsigned int  TA_Overflow_Cnt;         //TA���������ű���
unsigned long Period;             //�����Ž������
unsigned long S;
unsigned int  distance;
unsigned int  RiseCapVal;              //������ʱ�̲���ֵ��ű���
unsigned char Edge=1;                 //��ǰ������
unsigned char disbuff[4]="0.00";
unsigned char temp,A1,A2,A3,A4,A5,A6,A7,A8;            //����ı���,��ʾ���ݴ���
unsigned long safe;
//Trig�Ž�P14��Echo�Ž�P12
/**
 * main.c
 */
void main()
{
    WDTCTL = WDTPW | WDTHOLD;           // stop watchdog timer
    Clock_Init();                       //ϵͳʱ������
    LCD_Portinit();                     //ϵͳ��ʼ��������IO������
    LCD_init();                         //Һ��������ʼ������
    Key_init();
    LED_Portinit();
    LCD_clear();                        //����
    LCD_Desk();

    SRF05_IOinit();
    init_timerA();

    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //��Ϊ�����ز���

    _EINT();


    safe=1000;
    while(1)
    {
        P1OUT |= BIT4;              //�ߵ�ƽ����10us�������������
        delay_ms(10);
        P1OUT &=~BIT4;              //�������60ms�Ĳ�������
        delay_ms(200);

        LCD_DisplayDistance(S);      //��̬��ʾ���룬��λm
        LCD_DisplaySafe(safe);
        if(S>(safe+50)||S<(safe-50)){
            LED8 |=  BIT0;
        }else{
            LED8 &= ~BIT0;
        }
    }

}
