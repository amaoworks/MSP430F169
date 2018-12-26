/*
 * LCD.h
 *
 *  Created on: 2018��12��13��
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef LCD_H_
#define LCD_H_

#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

#define set_RS   P5OUT |=  BIT5          //����RSΪ1
#define clr_RS   P5OUT &= ~BIT5          //����RSΪ0
#define set_EN   P5OUT |=  BIT7          //����ENΪ1
#define clr_EN   P5OUT &= ~BIT7          //����ENΪ0
#define set_RW   P5OUT |=  BIT6          //����RWΪ1
#define clr_RW   P5OUT &= ~BIT6          //����RWΪ0
#define dataout  P4DIR=0xff             //��ʼ��D0~D7
#define dataport P4OUT

void Write_com(uchar com);
void Write_data(uchar date);
void LCD_init();
void LCD_Portinit();
void Display_Num(unsigned char x,unsigned char y,unsigned long num);
void LCD_clear(void);
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s);
void LCD_write_char(unsigned char x,unsigned char y,unsigned char data);

#endif /* LCD_H_ */
