/*
 * I2C_reg.h
 *
 *  Created on: 2018年11月16日
 *      Author: myy12
 */
#include "Config.h"
#ifndef I2C_REG_H_
#define I2C_REG_H_

//#define SLAVEADDR 0xd0    //从机地址

unsigned char IICRead(unsigned char addr);//用IIC读数据
unsigned char IICWrite(unsigned char addr,unsigned char dat);//用IIC写数据
void IIC_init(unsigned char addr);//IIC初始化,并传入从机地址

#endif /* I2C_REG_H_ */
