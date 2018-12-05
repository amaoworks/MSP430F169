#include<msp430f169.h>
#include"type.h"
//#include"delay.h"

#ifndef UART_H_
#define UART_H_

uchar keyvalue;

void UART_Init();
void Send_Byte(uchar data);

#endif /* UART_H_ */
