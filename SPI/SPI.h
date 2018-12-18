#ifndef SPI_H
#define SPI_H
#include "msp430f169.h"
#define CPU_F ((double)8000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define uchar unsigned char
#define uint unsigned int
void init_spi();
void spi_sendByte(unsigned char dat);
#endif
