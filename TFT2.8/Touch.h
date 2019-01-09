/*
 * Touch.h
 *
 *  Created on: 2018年11月28日
 *      Author: liu
 */

#ifndef TOUCH_H_
#define TOUCH_H_
#include "Config.h"
#define uchar unsigned char
#define uint unsigned int
struct struct1                          //定义一个类型名为struct1的结构,包含两个成员x和y
{
    uint x;                         //成员x
    uint y;                         //成员y
};

extern struct struct1 coordinate;      //定义一个名为Tp_pix的结构变量,用于存放处理后的触摸坐标参数
extern uint  lx,ly;

void start_7843();
void Write_7843(uchar temp);          //SPI写8位命令到触摸控制IC
uint Read_7843();                     //SPI 读数据
struct struct1 AD7843() ;
uchar pix_filter(struct struct1 pix1,struct struct1 pix2);
uchar Getpix();




#endif /* TOUCH_H_ */
