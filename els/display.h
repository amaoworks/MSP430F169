#include "msp430x16x.h"

#define NOKIA5110_CLK_H	P5OUT |= BIT0
#define NOKIA5110_DIN_H	P5OUT |= BIT1
#define NOKIA5110_DC_H	P5OUT |= BIT2
#define NOKIA5110_CE_H	P5OUT |= BIT3
#define NOKIA5110_RST_H	P5OUT |= BIT4
#define NOKIA5110_LED_ON	P5OUT |= BIT5

#define NOKIA5110_CLK_L	P5OUT &= ~BIT0
#define NOKIA5110_DIN_L	P5OUT &= ~BIT1
#define NOKIA5110_DC_L	P5OUT &= ~BIT2
#define NOKIA5110_CE_L	P5OUT &= ~BIT3
#define NOKIA5110_RST_L	P5OUT &= ~BIT4
#define NOKIA5110_LED_OFF	P5OUT &= ~BIT5



extern void lcd_init();
extern void lcd_clear();
extern void set_xy(unsigned char x,unsigned char y);
extern void write(unsigned char a,unsigned char b,unsigned char add);
extern void write_string(unsigned char x,unsigned char y,unsigned char *p);
extern void write(unsigned char a,unsigned char b,unsigned char add);
extern void send(unsigned char dat,unsigned char command);
extern void writeshuzi(unsigned char a,unsigned char b,unsigned char add);
