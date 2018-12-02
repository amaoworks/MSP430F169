/*
 * LCD.h
 *
 *  Created on: 2018年11月18日
 *      Author: myy12
 */
#include "Config.h"
#ifndef LCD_H_
#define LCD_H_

void write_com(uchar com);
void write_date(uchar date);
void init();
void port_init();
void display(unsigned long int num);
void Port_In();
uchar Key_Scan(void);

//void Write();
//void Read();
//void Watch();

//4个独立按键连接在P10~P13
#define KeyPort         P1IN                              //独立键盘接在P10~P13

#define set_RS P5OUT |=  BIT5          //设置RS为1
#define clr_RS P5OUT &= ~BIT5          //设置RS为0
#define set_EN P5OUT |=  BIT7          //设置EN为1
#define clr_EN P5OUT &= ~BIT7          //设置EN为0
#define set_RW P5OUT |=  BIT6          //设置RW为1
#define clr_RW P5OUT &= ~BIT6          //设置RW为0
#define dataout P4DIR=0xff             //初始化D0~D7
#define dataport P4OUT


#endif /* LCD_H_ */
