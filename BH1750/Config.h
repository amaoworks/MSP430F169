/*
 * Config.h
 *
 *  Created on: 2018��12��5��
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef CONFIG_H_
#define CONFIG_H_

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define _NOP()  __no_operation()

void Clock_Init();

#endif /* CONFIG_H_ */