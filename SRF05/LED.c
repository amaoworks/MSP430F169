/*
 * LED.c
 *
 *  Created on: 2018年12月13日
 *      Author: Brown
 */
#include "LED.h"

void LED_Portinit()
{
  LED8DIR = 0xff;                    //设置IO口方向为输出
  LED8 = 0xFF;                       //初始设置为00
}
