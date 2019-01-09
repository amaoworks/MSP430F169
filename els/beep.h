#include "msp430x16x.h"

extern void beep();

#define beep1_OFF P1OUT |= BIT4;
#define beep1_ON P1OUT &= ~BIT4;
