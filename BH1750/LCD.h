/*
 * LCD.h
 *
 *  Created on: 2018��12��5��
 *      Author: Brown
 */
#include "BH1750.h"
#ifndef LCD_H_
#define LCD_H_

#define DataDir     P4DIR
#define DataPort    P4OUT

#define set_RS P5OUT |=  BIT5          //����RSΪ1
#define clr_RS P5OUT &= ~BIT5          //����RSΪ0
#define set_EN P5OUT |=  BIT7          //����ENΪ1
#define clr_EN P5OUT &= ~BIT7          //����ENΪ0
#define set_RW P5OUT |=  BIT6          //����RWΪ1
#define clr_RW P5OUT &= ~BIT6          //����RWΪ0
#define dataout P4DIR=0xff             //��ʼ��D0~D7

void write_com(uchar com);
void write_date(uchar date);
void DisplayOneChar(unsigned char x, unsigned char date);
void init();
void port_init();
void display(unsigned long int num);
void inmaindispaly();

#endif /* LCD_H_ */
