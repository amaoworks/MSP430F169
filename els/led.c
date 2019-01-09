#include "msp430x16x.h"

void led_init()
{
	P6DIR |= BIT0+BIT1+BIT2+BIT3;
	P6OUT &=~(BIT0+BIT1+BIT2+BIT3);
}
