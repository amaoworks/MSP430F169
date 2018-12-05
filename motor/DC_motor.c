/*
 * SG90.c
 *
 *  Created on: 2018年10月15日
 *      Author: Jack
 */
#include<msp430f169.h>
#include"lcd_1602.h"
extern unsigned int a;
extern unsigned char STATUS;

void Init_PWM()
{
      BCSCTL2 |= SELS ;                 //SMCLK = XT2
      BCSCTL2 = DIVS0 + DIVS1;
      P1DIR = 0xff;               // P1输出
      P1OUT &= ~BIT2;
      CCR0 = 20000;                // PWM 周期
      CCTL1 = OUTMOD_7;            // CCR1复位/置位
      CCR1 = a;                // CCR1 PWM 占空比50%
      TACTL = TASSEL_2 + MC_1;     // 定时器A时钟源为SMCLK,增计数模式
}
void start()    //启动
{
    P1SEL |= 0x04;  //P1.2第二功能 TA1 输出PWM
    TACTL= TASSEL_2 + MC_1; //定时器A时钟源为SMCLK，增计数模式
    STATUS = 1;
    a=12000;
    CCR1 = a;

    return;
}

void stop()    //停止
{
    P1SEL = 0x00;    //P1.2第二功能 TA1 输出PWM
    TACTL= MC_0;
    P1OUT &=  ~BIT2;
    STATUS = 0;
    a = 0;
    CCR1 = a;

    return;
}

void speed_add()    //加速
{
    a+=1000;
    CCR1 = a;
    if(a >= 19000)
        a = 19000;



    return;
}

void speed_sub()    //减速
{
    a -= 1000;
    CCR1 = a;
    if(a <= 12000)
        a = 12000;

    return;
}
void show_status(unsigned char status, unsigned int speed)
{
    if(STATUS == 1){
        dis_str(0x80+8, "RUN ");
    }
    else
        dis_str(0x80+8, "STOP");
    write_cmd(0x80+0x40+8);
    switch(speed)
    {
    case 0:     write_data('0');  break;
    case 12000: write_data('1');  break;
    case 13000: write_data('2');  break;
    case 14000: write_data('3');  break;
    case 15000: write_data('4');  break;
    case 16000: write_data('5');  break;
    case 17000: write_data('6');  break;
    case 18000: write_data('7');  break;
    case 19000: write_data('8');  break;
    default: break;
    }
}
