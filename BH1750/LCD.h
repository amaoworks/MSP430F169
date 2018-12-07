/*
 * LCD.h
 *
 *  Created on: 2018年12月5日
 *      Author: Brown
 */
#include "BH1750.h"
#ifndef LCD_H_
#define LCD_H_

#define DataDir     P4DIR
#define DataPort    P4OUT

#define set_RS P5OUT |=  BIT5          //设置RS为1
#define clr_RS P5OUT &= ~BIT5          //设置RS为0
#define set_EN P5OUT |=  BIT7          //设置EN为1
#define clr_EN P5OUT &= ~BIT7          //设置EN为0
#define set_RW P5OUT |=  BIT6          //设置RW为1
#define clr_RW P5OUT &= ~BIT6          //设置RW为0
#define dataout P4DIR=0xff             //初始化D0~D7

void write_com(uchar com);
void write_date(uchar date);
void DisplayOneChar(unsigned char x, unsigned char date);
void init();
void port_init();
void display(unsigned long int num);
void inmaindispaly();

#endif /* LCD_H_ */
