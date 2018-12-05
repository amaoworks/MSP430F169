/*
 * Port.c
 *
 *  Created on: 2018��10��28��
 *      Author: Jack
 */
#include<msp430f169.h>
void init_nRF_port()
{
    P1DIR |= BIT6;
    P1DIR &= ~BIT7;
    P3DIR |= BIT3 + BIT0 + BIT1;
    P3DIR &= ~BIT2;
}

void init_1602_port()
{
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5DIR |= BIT5 + BIT6 + BIT7 + BIT0 + BIT1 + BIT2;
}


