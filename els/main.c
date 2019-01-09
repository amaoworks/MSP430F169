#include "msp430x16x.h"
#include "display.h"
#include "key.h"
#include "process.h"
#include "golbal.h"
#include "led.h"
#include "UART.h"

unsigned char speedtemp;
unsigned char bt;
unsigned int bt_led;
unsigned int bt_led1;

void timer_init();

void main()
{
    WDTCTL = WDTPW + WDTHOLD;//停止看门狗

    lcd_init(); //LCD初始化
    key_init(); //按键初始化
    led_init(); //led初始化
    welcome();  //显示欢迎画面(NOKIA andriod)
    ping();     //划分activity
    timer_init();//定时器初始化
    UART0_Init();
//    _EINT();
    bg_init();  //背景赋初值
    create();   //产生方块
    fangkuai_init();//把下一个要显示的方块显示出来
    renew();
    disscore();
    disguan();
    _EINT();
    while(1)
    {
        key();
//        Uart0Send_Byte(0x30);
//        delay_ms(100);
    }
}


/**************************************************
            TA产生随机数     TB控制下降速度
***************************************************/
void timer_init()
{
    TACTL |= TASSEL_2 + ID_0 + MC_1;//SMCLK作时钟，无分频，增计数模式，开启TA溢出中断
    TACCTL0|=CCIE;
    TACCR0 = 210 - 1;//0.2ms中断一次

    TBCTL |= TBSSEL_2 + ID_0 + MC_1 ;//SMCLK作时钟，无分频，增计数模式，开启TB溢出中断
    TBCCTL0|=CCIE;
    TBCCR0 = 10000-1;//5ms中断一次
}
/**************************************************
                      中断处理
***************************************************/

/****************************************************************************
* 名    称：BT_ISR()
* 功    能：定时唤醒CPU。
* 入口参数：无
* 出口参数：无
****************************************************************************/
#pragma vector = TIMERA0_VECTOR
__interrupt void TA_ISR(void)   // 1/Div_Sec 秒一次中断（由BasicTimer所产生）
{

    if(suijishu < 6)
        suijishu++;
    else
        suijishu = 0;

    if(bt_led==2500)
    {
        bt_led = 0;
        P1OUT^=BIT0;
    }
    bt_led++;
}

#pragma vector = TIMERB0_VECTOR
__interrupt void TB_ISR(void)   // 1/Div_Sec 秒一次中断（由BasicTimer所产生）
{
    if(speedtemp<speed)
    {
        speedtemp++;
    }
    else
    {
        move();
        speedtemp = 0;
    }

    if(bt_led1==25)
    {
        bt_led1 = 0;
        P1OUT^=BIT3;
    }
    bt_led1++;
}
