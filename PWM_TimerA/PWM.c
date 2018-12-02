/*
 * PWM.c
 *
 *  Created on: 2018��11��28��
 *      Author: Brown
 */
#include "PWM.h"

/*
 * ����:  PWM��ʼ������
 * ����:  ��ʼ��TimerA PWM
 * ����:  Clk:    ʱ��    1 SMCLK 0 ACLK
 *       Output: ���    1 P1.2  0 P1.3
 *       Model:  ģʽ    1 �ߵ�ƽ    2 �͵�ƽ
 *       ccr0:   ����
 *       ccrX:   ռ�ձ�Ϊ   ccrX / ccr0
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
            P1SEL |= BIT2;          //��P1.2���
            P1DIR |= BIT2;          //��P1.2���
        }else{
            TACCTL2 = OUTMOD_7;
            P1SEL |= BIT3;          //��P1.3���
            P1DIR |= BIT3;          //��P1.3���
        }
        break;
    }
    case 2:{
        if(Output){
            TACCTL1 = OUTMOD_3;
            P1SEL |= BIT2;          //��P1.2���
            P1DIR |= BIT2;          //��P1.2���
        }else{
            TACCTL2 = OUTMOD_3;
            P1SEL |= BIT3;          //��P1.3���
            P1DIR |= BIT3;          //��P1.3���
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

