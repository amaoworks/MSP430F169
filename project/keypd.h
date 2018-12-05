#ifndef KEYPD_H_
#define KEYPD_H_

#include <msp430f169.h>
#include "type.h"
//#include "delay.h"

/***************全局变量***************/
uchar key_Pressed;      //按键是否被按下:1--是，0--否
uchar key_val;          //存放键值
uchar key_Flag;         //按键是否已放开：1--是，0--否
//设置键盘逻辑键值与程序计算键值的映射
//uchar key_Map[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

void Check_Key(void);
void delay15ms();
void Key_Event(void);

#endif /* KEYPD_H_ */
