#include <msp430f169.h>
#include "Config.h"
#include "SRF05.h"
#include "LCD.h"
#include "Key.h"
#include "LED.h"

//使用的全局变量
unsigned int  TA_Overflow_Cnt;         //TA溢出次数存放变量
unsigned long Period;             //脉宽存放结果变量
unsigned long S;
unsigned int  distance;
unsigned int  RiseCapVal;              //上升沿时刻捕获值存放变量
unsigned char Edge=1;                 //当前触发沿
unsigned char disbuff[4]="0.00";
unsigned char temp,A1,A2,A3,A4,A5,A6,A7,A8;            //定义的变量,显示数据处理
unsigned long safe;
//Trig脚接P14，Echo脚接P12
/**
 * main.c
 */
void main()
{
    WDTCTL = WDTPW | WDTHOLD;           // stop watchdog timer
    Clock_Init();                       //系统时钟设置
    LCD_Portinit();                     //系统初始化，设置IO口属性
    LCD_init();                         //液晶参数初始化设置
    Key_init();
    LED_Portinit();
    LCD_clear();                        //清屏
    LCD_Desk();

    SRF05_IOinit();
    init_timerA();

    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //改为上升沿捕获

    _EINT();


    safe=1000;
    while(1)
    {
        P1OUT |= BIT4;              //高电平至少10us启动超声波测距
        delay_ms(10);
        P1OUT &=~BIT4;              //建议大于60ms的测量周期
        delay_ms(200);

        LCD_DisplayDistance(S);      //动态显示距离，单位m
        LCD_DisplaySafe(safe);
        if(S>(safe+50)||S<(safe-50)){
            LED8 |=  BIT0;
        }else{
            LED8 &= ~BIT0;
        }
    }

}
