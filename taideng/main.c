#include <msp430f169.h>
#include "Config.h"
#include "SRF05.h"
#include "TFT.h"
#include "SPI.h"
#include "Key.h"
#include "PWM.h"

unsigned int TA_Overflow_Cnt;         //TA溢出次数存放变量
unsigned long int Period;             //脉宽存放结果变量
unsigned long int S;                  //计算结果单位为毫米
unsigned int RiseCapVal;               //上升沿时刻捕获值存放变量
unsigned char Edge=1;                 //当前触发沿 初始值为上升沿
uchar    temp,A1,A2,A3,A4;            //定义的变量,显示数据处理
unsigned char Temp_Value[7];
unsigned char key, statu, open, clear;

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
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //改为上升沿捕获

    _EINT();
    statu = 0;
    clear = 0;

    LCD_PutString(32,48,"1.手动模式",BLACK,MAGENTA);
    LCD_PutString(32,64,"2.自动模式",BLACK,MAGENTA);

    while(1){
        P1OUT |= BIT4;              //高电平至少10us启动超声波测距
        delay_ms(10);
        P1OUT &=~BIT4;              //建议大于60ms的测量周期
        delay_ms(200);
        Data_do(S);
        Auto();

        if(clear == 1){
            LCD_Clear(MAGENTA);
            clear = 0;
        }


        if(statu == 1){
            Light();
        }else if(statu == 2){
            LCD_PutString(32,32,Temp_Value,BLACK,MAGENTA);
            if(open == 1){
                PWM_Init(1, 1, 1, 10000, 10000);
                LCD_PutString(32,64,"开启",BLACK,MAGENTA);
            }
            else{
                PWM_Init(1, 1, 1, 10000, 0);
                LCD_PutString(32,64,"关闭",BLACK,MAGENTA);
            }
        }
    }
}
