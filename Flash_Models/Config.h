/*
 * Config.h
 *
 *  Created on: 2018年11月18日
 *      Author: myy12
 */
#include <msp430f169.h>

#ifndef CONFIG_H_
#define CONFIG_H_

void FlashInit();
void FlashErase(unsigned int Addr);
void WaitForEnable();
void FlashWriteChar(unsigned int addr,char Data);
void FlashWriteWord(unsigned long addr,unsigned long Data);
unsigned char FlashReadChar(unsigned int Addr);
unsigned int FlashReadWord(unsigned int Addr);
void Clock_Init();

#define InfoB  (0x1000)
unsigned char key;
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
//Test For Display Info From Flash By 1602
//延时函数，IAR自带，经常使用到
#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//自定义数据结构，方便使用
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

/*
void Write();
void Read();*/

#endif /* CONFIG_H_ */
