#include <msp430f169.h>
#include "LCD1602.h"
#define CPU_F ((double)8000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define uchar unsigned char
/**
 * main.c
 */

void init_spi(){
    U0CTL |= SWRST;
    U0CTL |= CHAR+SYNC+MM;
    U0TCTL |= SSEL1+SSEL0+STC+CKPH;
    //U0TCTL=CKPH;
    //U0TCTL &= ~CKPL;
    U0BR0=0x02;
    U0BR1=0x00;
    ME1 |= USPIE0;
    U0CTL&=~SWRST;
    IE1 |= URXIE0;                            // 接收中断使能
    P3SEL|=0x0e;
    P3DIR|=0x01;
    _EINT();
}

void spi_sendByte(unsigned char dat){
    U0TXBUF=dat;
    while((IFG1&UTXIFG0)==0);
}



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

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P6DIR=0xff;
    P6OUT=0x00;
    Clock_Init();
    Port_init();
    LCD_init();
    LCD_clear();
    init_spi();
    while(1){
            spi_sendByte(0x04);
        }
}

#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void){
    unsigned char data=0;
    data=U0RXBUF;
        P6OUT=~data;
        LCD_write_single_char(0,0,data+'0');
}
