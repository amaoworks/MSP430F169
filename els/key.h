#include "msp430x16x.h"

#define k1	(P1IN & BIT0)
#define k2	(P1IN & BIT1)
#define k3	(P1IN & BIT2)
#define k4	(P1IN & BIT3)

#define Key	(P1IN & 0x0F)

extern void key_init();
extern unsigned char scankey();
extern void test_key();
extern void key();




