/*
 * I2C_reg.h
 *
 *  Created on: 2018��11��16��
 *      Author: myy12
 */
#include "Config.h"
#ifndef I2C_REG_H_
#define I2C_REG_H_

//#define SLAVEADDR 0xd0    //�ӻ���ַ

unsigned char IICRead(unsigned char addr);//��IIC������
unsigned char IICWrite(unsigned char addr,unsigned char dat);//��IICд����
void IIC_init(unsigned char addr);//IIC��ʼ��,������ӻ���ַ

#endif /* I2C_REG_H_ */
