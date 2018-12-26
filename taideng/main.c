#include <msp430f169.h>
#include "Config.h"
#include "SRF05.h"
#include "TFT.h"
#include "SPI.h"
#include "PWM.h"
#include "Touch.h"
#include "TouchKey.h"
#include "GUI.h"

unsigned int TA_Overflow_Cnt;         //TA溢出次数存放变量
unsigned long int Period;             //脉宽存放结果变量
unsigned long int S;                  //计算结果单位为毫米
unsigned int RiseCapVal;               //上升沿时刻捕获值存放变量
unsigned char Edge=1;                 //当前触发沿 初始值为上升沿
uchar    temp,A1,A2,A3,A4;            //定义的变量,显示数据处理
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
        LCD_PutString(140,210,"开启",YELLOW,BLACK);
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
        LCD_PutString(140,210,"关闭",YELLOW,BLACK);
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
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //改为上升沿捕获

    _EINT();
    P6DIR = 0xff;
    P6OUT |= BIT0 + BIT1;
//    statu = 0;
//    //statu  = 1;
//    clear  = 0;
//    voice  = 0;
//
//    key    = 0;

    //    LCD_PutString24(60,60,"智 能 台 灯",BLUE,MAGENTA);
    //    LCD_PutString(58,140,"按键S1:手动模式",YELLOW,MAGENTA);
    //    LCD_PutString(58,180,"按键S2:自动模式",YELLOW,MAGENTA);

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
            LCD_PutString24(60,60,"智 能 台 灯",BLUE,MAGENTA);
            LCD_PutString(88,140,"手动模式",YELLOW,MAGENTA);
            LCD_PutString(88,200,"自动模式",YELLOW,MAGENTA);
            GUIsquare2pix(78,130,162,166,YELLOW);
            GUIsquare2pix(78,190,162,226,YELLOW);
            while(statu == 0)
                touchMain();
        }else if(statu == 1){
            LCD_PutString24(60,60,"智 能 台 灯",GBLUE,BLACK);
            GUIsquare1pix(92,255,148,281,GBLUE);
            LCD_PutString(102,260,"返 回",GBLUE,BLACK);
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
            LCD_PutString(80,124,"自动模式",GBLUE,BLACK);
            LCD_PutString(60,180,"距离台灯",GBLUE,BLACK);
            LCD_PutString(60,210,"台灯状态:",GBLUE,BLACK);
            GUIsquare1pix(92,255,148,281,GBLUE);
            LCD_PutString(102,260,"返 回",GBLUE,BLACK);
            LCD_PutString24(60,60,"智 能 台 灯",GBLUE,BLACK);
            Show_Image(170,210,114,154,gImage_hlaba);
            while(statu == 2){
                P1OUT |= BIT4;              //高电平至少10us启动超声波测距
                delay_ms(10);
                P1OUT &=~BIT4;              //建议大于60ms的测量周期
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
