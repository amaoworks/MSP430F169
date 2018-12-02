/*
 * I2C_reg.c
 *
 *  Created on: 2018Äê11ÔÂ16ÈÕ
 *      Author: Maos
 */
#include "I2C_reg.h"
unsigned char IICRead(unsigned char addr){
    I2CNDAT=0x01;
    unsigned char ctlbyte;
    U0CTL |= MST;
    I2CTCTL |= I2CSTT+I2CSTP+I2CTRX;
    while((I2CIFG&TXRDYIFG)==0);
    I2CDRB=addr;
    delay_ms(9);
    U0CTL |= MST;
    I2CIFG &= ~ARDYIFG;
    I2CTCTL &= ~I2CTRX;
    I2CTCTL = I2CSTT+I2CSTP;
    while((I2CIFG&RXRDYIFG)==0);
    ctlbyte=I2CDRB;
    delay_ms(9);
    while((I2CTCTL&I2CSTP)==0x02);
    return ctlbyte;
}


unsigned char IICWrite(unsigned char addr,unsigned char dat){
    //I2CNDAT=2;
    I2CNDAT=0x02;
    //I2CSA=(0xd0>>1);

    U0CTL |= MST;
    I2CTCTL |= I2CSTT+I2CSTP+I2CTRX;
    while((I2CIFG&TXRDYIFG)==0);
    I2CDRB=addr;
    delay_ms(9);
    while((I2CIFG&TXRDYIFG)==0);
    I2CDRB=dat;
    delay_ms(9);
    while((I2CTCTL&I2CSTP)==0x02);
}

void IIC_init(unsigned char addr){

    P3SEL|=0x0a;
    P3DIR&=~0x0a;
    U0CTL|=I2C+SYNC;
    U0CTL&=~I2CEN;
    I2CTCTL=I2CSSEL_2;
    I2CSA=(addr>>1);
    U0CTL|=I2CEN;
    _EINT();
}
