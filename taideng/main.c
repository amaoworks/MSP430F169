#include <msp430f169.h>
#include "Config.h"
#include "SRF05.h"
#include "TFT.h"
#include "SPI.h"
#include "Key.h"
#include "PWM.h"

unsigned int TA_Overflow_Cnt;         //TA���������ű���
unsigned long int Period;             //�����Ž������
unsigned long int S;                  //��������λΪ����
unsigned int RiseCapVal;               //������ʱ�̲���ֵ��ű���
unsigned char Edge=1;                 //��ǰ������ ��ʼֵΪ������
uchar    temp,A1,A2,A3,A4;            //����ı���,��ʾ���ݴ���
unsigned char Temp_Value[7];
unsigned char key, statu, open, clear, choose;

/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    Clock_Init();

    Key_Portinit();

    init_spi();
    TFT_port_init();
    TFT_init();
    LCD_Clear(MAGENTA);

    SRF05_IOinit();
    init_timerA();
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //��Ϊ�����ز���

    _EINT();
    statu = 0;
    clear = 0;
    key = 3;

    LCD_PutString24(60,60,"�� �� ̨ ��",BLUE,MAGENTA);
    LCD_PutString(58,140,"����S1:�ֶ�ģʽ",YELLOW,MAGENTA);
    LCD_PutString(58,180,"����S2:�Զ�ģʽ",YELLOW,MAGENTA);
    choose = 0;

    while(1){
        P1OUT |= BIT4;              //�ߵ�ƽ����10us�������������
        delay_ms(10);
        P1OUT &=~BIT4;              //�������60ms�Ĳ�������
        delay_ms(200);
        Data_do(S);
        Auto();

        if(clear == 1){
            LCD_Clear(BLACK);
            clear = 0;
        }
        if(choose == 1)
            LCD_PutString24(60,60,"�� �� ̨ ��",GBLUE,BLACK);

        if(statu == 1){
            choose = 1;
            Light();
        }else if(statu == 2){
            key = 3;
            choose = 1;
            LCD_PutString(80,124,"�Զ�ģʽ",GBLUE,BLACK);
            LCD_PutString(60,180,"����̨��",GBLUE,BLACK);
            LCD_PutString(130,180,Temp_Value,YELLOW,BLACK);
            LCD_PutString(60,210,"̨��״̬:",GBLUE,BLACK);
            if(open == 1){
                PWM_Init(1, 1, 1, 10000, 10000);
                LCD_PutString(140,210,"����",YELLOW,BLACK);
            }
            else{
                PWM_Init(1, 1, 1, 10000, 0);
                LCD_PutString(140,210,"�ر�",YELLOW,BLACK);
            }
        }
    }
}
