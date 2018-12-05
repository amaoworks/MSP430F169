/*
 * LCD.h
 *
 *  Created on: 2018��12��4��
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

#define set_RS P5OUT |=  BIT5          //����RSΪ1
#define clr_RS P5OUT &= ~BIT5          //����RSΪ0
#define set_EN P5OUT |=  BIT7          //����ENΪ1
#define clr_EN P5OUT &= ~BIT7          //����ENΪ0
#define set_RW P5OUT |=  BIT6          //����RWΪ1
#define clr_RW P5OUT &= ~BIT6          //����RWΪ0
#define dataout P4DIR=0xff             //��ʼ��D0~D7
#define dataport P4OUT

#endif /* LCD_H_ */
