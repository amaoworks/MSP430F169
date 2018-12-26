/*
 * I2C.h
 *
 *  Created on: 2018Äê12ÔÂ26ÈÕ
 *      Author: Brown
 */
#include "Config.h"
#ifndef I2C_H_
#define I2C_H_

#define year   0x06
#define month  0x05
#define m_day  0x04
#define w_day  0x03
#define hour   0x02
#define minute 0x01
#define second 0x00

void i2c_write(unsigned char naddr,unsigned char data);
unsigned char i2c_read(unsigned char naddr);

#endif /* I2C_H_ */
