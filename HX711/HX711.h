/*
 * HX711.h
 *
 *  Created on: 2018Äê12ÔÂ3ÈÕ
 *      Author: Brown
 */
#include "Config.h"
#ifndef HX711_H_
#define HX711_H_

static int i,j;

#define HX P4OUT
#define HX711_DOUT0 HX&0Xef
#define HX711_DOUT1 HX|0X10
#define HX711_SCK0 HX&0Xdf
#define HX711_SCK1 HX|0X20

int HX711_Read(void);

#endif /* HX711_H_ */
