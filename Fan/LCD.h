/*
 * LCD.h
 *
 *  Created on: 2018年12月4日
 *      Author: Brown
 */
#include "Config.h"
#ifndef LCD_H_
#define LCD_H_

void LCD_Write_com(unsigned char com);
void LCD_Write_data(unsigned char date);
void LCD_Init();
void LCD_Port_init();
void LCD_Display_num(unsigned char x, unsigned char y, unsigned long int num);
void LCD_Write_str(unsigned char x, unsigned char y, unsigned char *s);
void LCD_Desk();
//void LCD_Statu();

#define set_RS P5OUT |=  BIT5          //设置RS为1
#define clr_RS P5OUT &= ~BIT5          //设置RS为0
#define set_EN P5OUT |=  BIT7          //设置EN为1
#define clr_EN P5OUT &= ~BIT7          //设置EN为0
#define set_RW P5OUT |=  BIT6          //设置RW为1
#define clr_RW P5OUT &= ~BIT6          //设置RW为0
#define dataout P4DIR=0xff             //初始化D0~D7
#define dataport P4OUT

#endif /* LCD_H_ */
