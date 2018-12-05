#include <msp430f169.h>
#include "Config.h"
#include "PWM.h"
/**
 * main.c
 */

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PWM_Init(0, 1, 1, 10000, 8000);
    P6DIR = 0xff;
    P6OUT = 0xFF;
	while(1){
	    P6OUT |= 0x01;
	    delay_ms(150);
	    P6OUT &= ~0x01;
	    delay_ms(150);
	}
}
