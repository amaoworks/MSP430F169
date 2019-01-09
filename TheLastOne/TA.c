/*
 * TA.c
 *
 *  Created on: 2018年12月29日
 *      Author: Brown
 */
#include "TA.h"

extern int Asecond , count;

//TIMERA初始化，设置为UP模式计数
void TIMERA_Init(void)                                   //UP模式计数，计数周期为CCR0+1
{
    TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK做时钟源，8分频，增加计数模式，开中断
    TACCR0 = 9999;                                         //CCR0=9999，10ms中断一次
    _EINT();
}

//关闭计时，暂停计数
void TimerA_end(void)
{
    TACTL &= 0xfffd;
    Asecond = 0;
    _DINT();
}

//TIMERA中断服务程序，需要判断中断类型
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
    switch(TAIV)                                  //需要判断中断的类型
    {
    case 2:break;
    case 4:break;
    case 10:count++;break;                         //设置标志位Flag
    }
    if(count==100)                                 //100次为1秒
    {
        Asecond++;
        count=0;
    }
}
