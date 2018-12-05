/*
 * PWM.c
 *
 *  Created on: 2018年12月5日
 *      Author: Brown
 */
#include "PWM.h"

/*
 * 名称:  PWM初始化函数
 * 功能:  初始化TimerB PWM
 * 方法:  Clk:    时钟    1 SMCLK 0 ACLK
 *       Output: 输出    1 P4.2  0 P4.3
 *       Model:  模式    1 高电平    2 低电平
 *       ccr0:   周期
 *       ccrX:   占空比为   ccrX / ccr0
 */

void PWM_Init(unsigned char Clk, unsigned char Output, unsigned char Model, unsigned int ccr0, unsigned int ccrX){
    if(Clk){
        TBCTL=TBSSEL_2+MC_1;        //SMCLK
    }else{
        TBCTL=TBSSEL_1+MC_1;        //ACLK
    }
    switch(Model){
    case 1:{
        if(Output){
            TBCCTL2 = OUTMOD_7;
            P4SEL |= BIT2;          //从P4.2输出
            P4DIR |= BIT2;          //从P4.2输出
        }else{
            TBCCTL3 = OUTMOD_7;
            P4SEL |= BIT3;          //从P4.3输出
            P4DIR |= BIT3;          //从P4.3输出
        }
        break;
    }
    case 2:{
        if(Output){
            TBCCTL2 = OUTMOD_3;
            P4SEL |= BIT2;          //从P4.2输出
            P4DIR |= BIT2;          //从P4.2输出
        }else{
            TBCCTL3 = OUTMOD_3;
            P4SEL |= BIT3;          //从P4.3输出
            P4DIR |= BIT3;          //从P4.3输出
        }
    }
    default:return;
    }
    TBCCR0 = ccr0;
    if(Output){
        TBCCR2 = ccrX;
    }else{
        TBCCR3 = ccrX;
    }
}
