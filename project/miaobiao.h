#ifndef MIAOBIAO_H_
#define MIAOBIAO_H_

#include <msp430f169.h>
//#include "delay.h"
//#include "type.h"
#include "config.h"

char flag;
uchar aa,sec,min,hour,year,month,day;
uchar cflag;
uchar PP;

void xianshi();
void stopwatch();
void timer_B_init();
void init_port1();
#endif /* MIAOBIAO_H_ */
