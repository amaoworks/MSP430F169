/*
 * PWM.c
 *
 *  Created on: 2018��12��5��
 *      Author: Brown
 */
#include "PWM.h"

/*
 * ����:  PWM��ʼ������
 * ����:  ��ʼ��TimerB PWM
 * ����:  Clk:    ʱ��    1 SMCLK 0 ACLK
 *       Output: ���    1 P4.2  0 P4.3
 *       Model:  ģʽ    1 �ߵ�ƽ    2 �͵�ƽ
 *       ccr0:   ����
 *       ccrX:   ռ�ձ�Ϊ   ccrX / ccr0
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
            P4SEL |= BIT2;          //��P4.2���
            P4DIR |= BIT2;          //��P4.2���
        }else{
            TBCCTL3 = OUTMOD_7;
            P4SEL |= BIT3;          //��P4.3���
            P4DIR |= BIT3;          //��P4.3���
        }
        break;
    }
    case 2:{
        if(Output){
            TBCCTL2 = OUTMOD_3;
            P4SEL |= BIT2;          //��P4.2���
            P4DIR |= BIT2;          //��P4.2���
        }else{
            TBCCTL3 = OUTMOD_3;
            P4SEL |= BIT3;          //��P4.3���
            P4DIR |= BIT3;          //��P4.3���
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
