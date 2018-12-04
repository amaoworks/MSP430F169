/*
 * UART.h
 *
 *  Created on: 2018��12��3��
 *      Author: Brown
 */
#include "Config.h"
#ifndef UART_H_
#define UART_H_

//���ڲ����ʼ��㣬��BRCLK=CPU_Fʱ������Ĺ�ʽ���Լ��㣬����Ҫ�������ü����Ƶϵ��
#define baud           9600                                //���ò����ʵĴ�С
#define baud_setting   (unsigned int)((unsigned long)CPU_F/((unsigned long)baud))  //�����ʼ��㹫ʽ
#define baud_h         (unsigned char)(baud_setting>>8)            //��ȡ��λ
#define baud_l         (unsigned char)(baud_setting)               //��λ

void UART0_Init();
void Uart0Send_Byte(unsigned char data);


void UART1_Init();
void Uart1Send_Byte(unsigned char data);

#endif /* UART_H_ */
