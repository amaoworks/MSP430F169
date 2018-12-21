#include <msp430f169.h>
#include "SPI.h"
#include "TFT.h"
#include "Touch.h"
#define CPU_F ((double)8000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define uchar unsigned char

void Clock_Init(){
    unsigned char i;
    BCSCTL1&=~XT2OFF;
    BCSCTL2|=(SELM1+SELS);
    do{
        IFG1&=~OFIFG;
        for(i=0;i<100;i++){
            _NOP();
        }
    }
    while((IFG1&OFIFG)!=0);
    IFG1&=~OFIFG;
}
/*
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock_Init();
    init_spi();
    TFT_port_init();
    TFT_init();
    start_7843();
    LCD_Clear(GREEN);
    Show_Image(0,80,0,80,gImage_xiaohui);
    LCD_PutString24(0,200,"ÕýÏÒ²¨",RED,GREEN);
    while(1){
        if(Getpix()==1)   Put_pixel(lx,ly,WHITE);
    }
}

