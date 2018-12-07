/*
 * IIC.h
 *
 *  Created on: 2018年12月5日
 *      Author: Brown
 */
#include "Config.h"
#ifndef IIC_H_
#define IIC_H_

unsigned char IICRead(unsigned char addr);//用IIC读数据
unsigned char IICWrite(unsigned char addr,unsigned char dat);//用IIC写数据
void IIC_init(unsigned char addr);//IIC初始化,并传入从机地址

#endif /* IIC_H_ */
