/*
 * PWM.c
 *
 *  Created on: 2018��12��4��
 *      Author: Brown
 */
#include "PWM.h"

extern unsigned int a;
extern unsigned int long TemperC;

void PWM_init(){
    P1DIR = 0xff;                   // P1���
    TACTL=TASSEL_2+MC_1;
    P1OUT &= ~BIT2;
    CCR0 = 20000;                   // PWM ����
    CCTL1 = OUTMOD_7;               // CCR1��λ/��λ
    CCR1 = a;                       // CCR1 PWM ռ�ձ�50%
}

void start(){
    TACCTL1 = OUTMOD_7;
    P1SEL |= BIT2;          //��P1.2���
    P1DIR |= BIT2;          //��P1.2���
    CCR0 = 20000;
//    P1SEL |= BIT2;              //P1.2�ڶ����� TA1 ���PWM
    a=12000;
    CCR1 = a;
    P1DIR |= BIT2;
}

void stop(){
    P1SEL = 0x00;               //P1.2�ڶ����� TA1 ���PWM
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
    P1SEL |= BIT2;          //��P1.2���
    P1DIR |= BIT2;          //��P1.2���
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
