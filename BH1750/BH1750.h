/*
 * BH1750.h
 *
 *  Created on: 2018年12月5日
 *      Author: Brown
 */
#include "Config.h"
#ifndef BH1750_H_
#define BH1750_H_

#define LEDDIR  P1DIR
#define LED     P1OUT

#define SCL_H P3OUT |= BIT3//此IO在硬件上需要更改
#define SCL_L P3OUT &= ~BIT3
#define SDA_H P3OUT |= BIT1
#define SDA_L P3OUT &= ~BIT1

#define SCL_OUT P3DIR |= BIT3
#define SDA_IN  P3DIR &= ~BIT1   //SDA改成输入模式
#define SDA_OUT P3DIR |= BIT1    //SDA变回输出模式
#define SDA_VAL P3IN&BIT1        //SDA的位值

#define SlaveAddress 0x46  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改

void LED_init();
void I2C_init();
void Delay5us(void);
void Delay5ms(void);
void delay(uint x);
void BH1750_Start();
void BH1750_Stop();
void BH1750_SendACK(void);
void mnack(void);
uchar BH1750_RecvACK();
void write1(void);
void write0(void);
void BH1750_SendByte(unsigned char dat);
unsigned char BH1750_RecvByte();
void Single_Write_BH1750(unsigned char REG_Address);
void Init_BH1750();
void Multiple_Read_BH1750(void);
void conversion(unsigned int temp_data);

#endif /* BH1750_H_ */
