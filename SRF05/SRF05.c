/*
 * SRF05.c
 *
 *  Created on: 2018年12月13日
 *      Author: Brown
 */
#include "SRF05.h"

extern unsigned int  TA_Overflow_Cnt;
extern unsigned long Period;
extern unsigned long S;
extern unsigned int  distance;
extern unsigned int  RiseCapVal;
extern unsigned char Edge;
extern unsigned char disbuff[4];
extern unsigned char temp,A1,A2,A3,A4;

//初始化定时器A函数
void init_timerA()
{
    TACTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3;//SMCLK,连续计数，中断允许，计数器清零
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//捕获模式，上升沿捕获，CCI1A输入，同步捕获，中断允许
}

//SRF05模块控制口初始化函数
void SRF05_IOinit()
{
    P1DIR |= BIT4;                  //P1.4输出
    P1DIR &=~ BIT2;                 //P1.2输入
    P1SEL =  BIT2;                  //P1.2第二功能，捕获输入

    P1OUT &=~BIT4;                  //清零P14控制端
    delay_ms(1000);
}

//定时器A服务程序
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{

    switch(TAIV)
    {
    case 2 :if(Edge==RISE)
    {
        RiseCapVal = TACCR1;
        TACCTL1 |= CAP+CM_2+CCIS_0+SCS+CCIE;//改为下降沿捕获
        //TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//改为上升沿捕获
        Edge = FALL;//下降沿捕获标志
    }
    else
    {
        _DINT();

        Period = TACCR1-RiseCapVal;
        S=(Period*17)/100;
        TACCR1 = 0;
        TACCTL1|= CAP+CM_1+CCIS_0+SCS+CCIE;//改为上升沿捕获
        Edge = RISE;//上升沿捕获标志
        _EINT();
    }
    break;
    case 4 : break;
    case 10: TA_Overflow_Cnt++;
    break;
    }
}
