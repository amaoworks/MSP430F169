#include <msp430f169.h>
#include "Config.h"
#include "SRF05.h"
#include "TFT.h"
#include "SPI.h"
#include "PWM.h"
#include "Touch.h"
#include "TouchKey.h"
#include "GUI.h"

unsigned int TA_Overflow_Cnt;         //TA���������ű���
unsigned long int Period;             //�����Ž������
unsigned long int S;                  //��������λΪ����
unsigned int RiseCapVal;               //������ʱ�̲���ֵ��ű���
unsigned char Edge=1;                 //��ǰ������ ��ʼֵΪ������
uchar    temp,A1,A2,A3,A4;            //����ı���,��ʾ���ݴ���
unsigned char Temp_Value[7];
unsigned char key = 0, statu= 0, open= 0, clear= 0,voice= 0, enter= 0, out= 0;

/**
 * main.c
 */

void zidong(){
    if(voice == 0)
        Show_Image(170,210,114,154,gImage_hlaba);
    else if(voice == 1)
        Show_Image(170,210,114,154,gImage_laba);
    LCD_PutString(130,180,Temp_Value,YELLOW,BLACK);
    if(open == 1){
        out = 0;
        PWM_Init(1, 1, 1, 10000, 10000);
        LCD_PutString(140,210,"����",YELLOW,BLACK);
        if(enter == 0 && voice == 1){
            P6OUT &= ~BIT0;
            delay_ms(1000);
            P6OUT |= BIT0;
            enter = 1;
        }
    }
    else{
        enter = 0;
        PWM_Init(1, 1, 1, 10000, 0);
        LCD_PutString(140,210,"�ر�",YELLOW,BLACK);
        if(out == 0 && voice == 1){
            P6OUT &= ~BIT1;
            delay_ms(1000);
            P6OUT |= BIT1;
            out = 1;
        }
    }
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    Clock_Init();

    //    Key_Portinit();
    start_7843();

    init_spi();
    TFT_port_init();
    TFT_init();
    LCD_Clear(MAGENTA);

    SRF05_IOinit();
    init_timerA();
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //��Ϊ�����ز���

    _EINT();
    P6DIR = 0xff;
    P6OUT |= BIT0 + BIT1;
//    statu = 0;
//    //statu  = 1;
//    clear  = 0;
//    voice  = 0;
//
//    key    = 0;

    //    LCD_PutString24(60,60,"�� �� ̨ ��",BLUE,MAGENTA);
    //    LCD_PutString(58,140,"����S1:�ֶ�ģʽ",YELLOW,MAGENTA);
    //    LCD_PutString(58,180,"����S2:�Զ�ģʽ",YELLOW,MAGENTA);

    while(1){
//test
//        if(Getpix()==1){
//            Data_do(lx);
//            LCD_PutString(0,0,Temp_Value,YELLOW,MAGENTA);
//            Data_do(ly);
//            LCD_PutString(50,0,Temp_Value,YELLOW,MAGENTA);
//        }

        if(clear == 1){
            LCD_Clear(BLACK);
            clear = 0;
        }else if(clear == 2){
            LCD_Clear(MAGENTA);
            clear = 0;
        }

        if(statu == 0){
            key=0;
            LCD_PutString24(60,60,"�� �� ̨ ��",BLUE,MAGENTA);
            LCD_PutString(88,140,"�ֶ�ģʽ",YELLOW,MAGENTA);
            LCD_PutString(88,200,"�Զ�ģʽ",YELLOW,MAGENTA);
            GUIsquare2pix(78,130,162,166,YELLOW);
            GUIsquare2pix(78,190,162,226,YELLOW);
            while(statu == 0)
                touchMain();
        }else if(statu == 1){
            LCD_PutString24(60,60,"�� �� ̨ ��",GBLUE,BLACK);
            GUIsquare1pix(92,255,148,281,GBLUE);
            LCD_PutString(102,260,"�� ��",GBLUE,BLACK);
            GUIcircle(120,165,19,GBLUE);
            GUIcircle(120,165,20,GBLUE);
            GUIcircle(120,165,21,GBLUE);
            GUIfull(118,141,122,170,BLACK);
            GUIfull(110,141,117,150,BLACK);
            GUIfull(123,141,130,150,BLACK);
            while(statu == 1){
                touchBack();
                touchButton();
                Light();
            }
        }else if(statu == 2){
            key = 0;
            LCD_PutString(80,124,"�Զ�ģʽ",GBLUE,BLACK);
            LCD_PutString(60,180,"����̨��",GBLUE,BLACK);
            LCD_PutString(60,210,"̨��״̬:",GBLUE,BLACK);
            GUIsquare1pix(92,255,148,281,GBLUE);
            LCD_PutString(102,260,"�� ��",GBLUE,BLACK);
            LCD_PutString24(60,60,"�� �� ̨ ��",GBLUE,BLACK);
            Show_Image(170,210,114,154,gImage_hlaba);
            while(statu == 2){
                P1OUT |= BIT4;              //�ߵ�ƽ����10us�������������
                delay_ms(10);
                P1OUT &=~BIT4;              //�������60ms�Ĳ�������
                delay_ms(200);
                Data_do(S);
                Auto();
                touchBack();
                touchVoice();
                zidong();
            }
        }
    }
}
