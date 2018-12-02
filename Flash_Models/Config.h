/*
 * Config.h
 *
 *  Created on: 2018��11��18��
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
//��ʱ������IAR�Դ�������ʹ�õ�
#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//�Զ������ݽṹ������ʹ��
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

/*
void Write();
void Read();*/

#endif /* CONFIG_H_ */
