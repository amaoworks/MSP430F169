/*
 * PWM.c
 *
 *  Created on: 2018年12月4日
 *      Author: Brown
 */
#include "PWM.h"

extern unsigned int a;
extern unsigned int long TemperC;

void PWM_init(){
    P1DIR = 0xff;                   // P1输出
    TACTL=TASSEL_2+MC_1;
    P1OUT &= ~BIT2;
    CCR0 = 20000;                   // PWM 周期
    CCTL1 = OUTMOD_7;               // CCR1复位/置位
    CCR1 = a;                       // CCR1 PWM 占空比50%
}

void start(){
    TACCTL1 = OUTMOD_7;
    P1SEL |= BIT2;          //从P1.2输出
    P1DIR |= BIT2;          //从P1.2输出
    CCR0 = 20000;
//    P1SEL |= BIT2;              //P1.2第二功能 TA1 输出PWM
    a=12000;
    CCR1 = a;
    P1DIR |= BIT2;
}

void stop(){
    P1SEL = 0x00;               //P1.2第二功能 TA1 输出PWM
    P1OUT &= ~BIT2;
    a = 0;
    CCR1 = a;
}

void speed(unsigned char shift){
    if(shift == 1){
        a = 14000;
    }else if(shift == 2){
        a = 16000;
    }else if(shift == 3){
        a = 19000;
    }
    TACCTL1 = OUTMOD_7;
    P1SEL |= BIT2;          //从P1.2输出
    P1DIR |= BIT2;          //从P1.2输出
    CCR0 = 20000;
    CCR1 = a;
    P1DIR |= BIT2;
}

void Smart_speed(){
    start();
    if(TemperC > 20 && TemperC < 25){
        speed(2);
        delay_ms(100);
        speed(1);
    }
    if(TemperC > 20 && TemperC < 25){
        speed(3);
        delay_ms(100);
        speed(2);
        delay_ms(100);
        speed(1);
    }
}
