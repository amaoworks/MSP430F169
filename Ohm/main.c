#include <msp430f169.h>
#include "Config.h"
#include "LCD.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Clock_Init();
	port_init();
    dataout;
    init();
    //ADC²¿·Ö
    P6SEL
}
