/*
 * LCD.h
 *
 *  Created on: 2018年12月13日
 *      Author: Brown
 */
#include "Config.h"
#ifndef LCD_H_
#define LCD_H_

#define set_RS   P5OUT |=  BIT5          //设置RS为1
#define clr_RS   P5OUT &= ~BIT5          //设置RS为0
#define set_EN   P5OUT |=  BIT7          //设置EN为1
#define clr_EN   P5OUT &= ~BIT7          //设置EN为0
#define set_RW   P5OUT |=  BIT6          //设置RW为1
#define clr_RW   P5OUT &= ~BIT6          //设置RW为0
#define dataout  P4DIR=0xff             //初始化D0~D7
#define dataport P4OUT

void Write_com(uchar com);
void Write_data(uchar date);
void LCD_init();
void LCD_Portinit();
void Display_Num(unsigned char x,unsigned char y,unsigned long num);
void LCD_clear(void);
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s);
void LCD_write_char(unsigned char x,unsigned char y,unsigned char data);
void LCD_Desk();
void Data_do(uint temp_d);
void LCD_DisplayDistance(long distance);
void DataS_do(uint temp_d);
void LCD_DisplaySafe(long distance);

#endif /* LCD_H_ */
