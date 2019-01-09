/*
 * Config.h
 *
 *  Created on: 2018年12月13日
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef CONFIG_H_
#define CONFIG_H_

//延时函数，IAR自带，经常使用到
#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//自定义数据结构，方便使用
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//8个LED灯，连接在P6口，可通过断开电源停止使用，ADC使用时断开电源
#define LED8DIR         P2DIR
#define LED8            P2OUT                             //P6口接LED灯，8个

//4个独立按键连接在P10~P13
#define KeyPort         P1IN                              //独立键盘接在P10~P13

#define  RISE  1
#define  FALL  0

void Clock_Init();

#endif /* CONFIG_H_ */
