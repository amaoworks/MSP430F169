#include "config.h"

#pragma vector = TIMERB0_VECTOR
__interrupt void Timer_B(void)
{
    bb++;
    if(bb == 800)
    {
        bb = 0;
    }
}

void ele_init(){
    P4DIR |= 0x0c;
    P4SEL |= 0x0c;
}

void timer_B_init(){
    TBCCR0 = 10000;
    TBCTL = CNTL_0 + TASSEL_2 + MC_1;
}
