/*
 * IIC.h
 *
 *  Created on: 2018��12��5��
 *      Author: Brown
 */
#include "Config.h"
#ifndef IIC_H_
#define IIC_H_

unsigned char IICRead(unsigned char addr);//��IIC������
unsigned char IICWrite(unsigned char addr,unsigned char dat);//��IICд����
void IIC_init(unsigned char addr);//IIC��ʼ��,������ӻ���ַ

#endif /* IIC_H_ */
