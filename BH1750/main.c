#include <msp430f169.h>
#include "Config.h"
#include "BH1750.h"
#include "LCD.h"

unsigned char ge,shi,bai,qian,wan;  //显示变量
int dis_data;
uchar BUF[8];

void main( void )
{
    uint temp = 0;
    uint a = 0;
    uint b = 10;
    uint c = 30;
//    uint d = 50;
    P4DIR=0XFF;
    P5DIR|=0X07;
    P3DIR|=0XC0;
    WDTCTL = WDTPW + WDTHOLD;// Stop watchdog timer to prevent time out reset
    Clock_Init();
    delay(20);     //延时200ms
    //  InitLcd();           //初始化LCD
    Init_BH1750();       //初始化BH1750
    I2C_init();
    port_init();
    init();
    LED_init();
    while(1)
    {
        Single_Write_BH1750(0x01);   // power on
        Single_Write_BH1750(0x10);   // H- resolution mode

        delay(180);              //延时180ms

        Multiple_Read_BH1750();       //连续读出数据，存储在BUF中


        inmaindispaly();
        temp=dis_data;
        if(temp > a && temp < b){
            LED = 0xFD;
        }else if(temp>b && temp<c){
            LED = 0xF9;
        }else if(temp>c){
            LED = 0xF1;
        }
        delay(100);

    }
}
