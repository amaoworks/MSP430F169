/*
 * Config.h
 *
 *  Created on: 2018��11��11��
 *      Author: Cal
 */
#include<msp430f169.h>
#ifndef CONFIG_H_
#define CONFIG_H_

#define CPU_F ((double)8000000)
//#define CPU_F ((double)32768)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define uchar unsigned char


void Clock_Init();//ʱ�ӳ�ʼ��



#endif /* CONFIG_H_ */
