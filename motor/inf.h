#ifndef INF_H_
#define INF_H_
#include<msp430f169.h>
#include"lcd_1602.h"

void infrared_decode();
void set_value(unsigned char);
void init_port2();
void init_device();

#endif /* INF_H_ */
