/*
 * UART.h
 *
 *  Created on: 2018年12月3日
 *      Author: Brown
 */
#include "Config.h"
#ifndef UART_H_
#define UART_H_

//串口波特率计算，当BRCLK=CPU_F时用下面的公式可以计算，否则要根据设置加入分频系数
#define baud           9600                                //设置波特率的大小
#define baud_setting   (unsigned int)((unsigned long)CPU_F/((unsigned long)baud))  //波特率计算公式
#define baud_h         (unsigned char)(baud_setting>>8)            //提取高位
#define baud_l         (unsigned char)(baud_setting)               //低位

void UART0_Init();
void Uart0Send_Byte(unsigned char data);


void UART1_Init();
void Uart1Send_Byte(unsigned char data);

#endif /* UART_H_ */
