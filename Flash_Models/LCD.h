/*
 * LCD.h
 *
 *  Created on: 2018��11��18��
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

//4����������������P10~P13
#define KeyPort         P1IN                              //�������̽���P10~P13

#define set_RS P5OUT |=  BIT5          //����RSΪ1
#define clr_RS P5OUT &= ~BIT5          //����RSΪ0
#define set_EN P5OUT |=  BIT7          //����ENΪ1
#define clr_EN P5OUT &= ~BIT7          //����ENΪ0
#define set_RW P5OUT |=  BIT6          //����RWΪ1
#define clr_RW P5OUT &= ~BIT6          //����RWΪ0
#define dataout P4DIR=0xff             //��ʼ��D0~D7
#define dataport P4OUT


#endif /* LCD_H_ */
