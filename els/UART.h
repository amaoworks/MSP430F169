/*
 * UART.h
 *
 *  Created on: 2018��12��28��
 *      Author: yule
 */
#include <msp430f169.h>
#ifndef UART_H_
#define UART_H_

#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define baud           9600                                //���ò����ʵĴ�С
#define baud_setting   (unsigned int)((unsigned long)CPU_F/((unsigned long)baud))  //�����ʼ��㹫ʽ
#define baud_h         (unsigned char)(baud_setting>>8)            //��ȡ��λ
#define baud_l         (unsigned char)(baud_setting)               //��λ

void UART0_Init();
void Uart0Send_Byte(unsigned char data);

#endif /* UART_H_ */
