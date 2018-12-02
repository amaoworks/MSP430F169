/*
 * PWM.c
 *
 *  Created on: 2018年11月28日
 *      Author: Brown
 */
#include "PWM.h"

/*
 * 名称:  PWM初始化函数
 * 功能:  初始化TimerA PWM
 * 方法:  Clk:    时钟    1 SMCLK 0 ACLK
 *       Output: 输出    1 P1.2  0 P1.3
 *       Model:  模式    1 高电平    2 低电平
 *       ccr0:   周期
 *       ccrX:   占空比为   ccrX / ccr0
 */

void PWM_Init(unsigned char Clk, unsigned char Output, unsigned char Model, unsigned int ccr0, unsigned int ccrX){
    if(Clk){
        TACTL=TASSEL_2+MC_1;        //SMCLK
    }else{
        TACTL=TASSEL_1+MC_1;        //ACLK
    }
    switch(Model){
    case 1:{
        if(Output){
            TACCTL1 = OUTMOD_7;
            P1SEL |= BIT2;          //从P1.2输出
            P1DIR |= BIT2;          //从P1.2输出
        }else{
            TACCTL2 = OUTMOD_7;
            P1SEL |= BIT3;          //从P1.3输出
            P1DIR |= BIT3;          //从P1.3输出
        }
        break;
    }
    case 2:{
        if(Output){
            TACCTL1 = OUTMOD_3;
            P1SEL |= BIT2;          //从P1.2输出
            P1DIR |= BIT2;          //从P1.2输出
        }else{
            TACCTL2 = OUTMOD_3;
            P1SEL |= BIT3;          //从P1.3输出
            P1DIR |= BIT3;          //从P1.3输出
        }
    }
    default:return;
    }
    TACCR0 = ccr0;
    if(Output){
        TACCR1 = ccrX;
    }else{
        TACCR2 = ccrX;
    }
}

