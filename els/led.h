#include "msp430x16x.h"

#define led1_ON		P6OUT |= BIT0;
#define led1_OFF	P6OUT &=~BIT0;
#define led2_ON		P6OUT |= BIT1;
#define led2_OFF	P6OUT &=~BIT1;
#define led3_ON		P6OUT |= BIT2;
#define led3_OFF	P6OUT &=~BIT2;
#define led4_ON		P6OUT |= BIT3;
#define led4_OFF	P6OUT &=~BIT3;

extern void led_init();
