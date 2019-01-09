/*
 * UART.h
 *
 *  Created on: 2018年12月28日
 *      Author: yule
 */
#include <msp430f169.h>
#ifndef UART_H_
#define UART_H_

#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define baud           9600                                //设置波特率的大小
#define baud_setting   (unsigned int)((unsigned long)CPU_F/((unsigned long)baud))  //波特率计算公式
#define baud_h         (unsigned char)(baud_setting>>8)            //提取高位
#define baud_l         (unsigned char)(baud_setting)               //低位

void UART0_Init();
void Uart0Send_Byte(unsigned char data);

#endif /* UART_H_ */
