/*
 * Touch.h
 *
 *  Created on: 2018年12月20日
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef TOUCH_H_
#define TOUCH_H_

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
/*
 * 接线：IRQ 2.0 DO 2.1 DI 2.4 CS 2.5 CLK 2.6
 */
#define PEN_CLR         P2OUT &= ~BIT0           //PEN置低,触碰触摸屏时，Penirq引脚由未触摸时的高电平变为低电平
#define PEN_SET         P2OUT |=  BIT0           //PEN置高
#define PEN             (P2IN & 0x01)            //P2.0输入的值

#define TPDO_CLR    P2OUT &= ~BIT1           //TPDO置低
#define TPDO_SET    P2OUT |=  BIT1           //TPDO置高
#define TPDOUT      ((P2IN>>1)&0x01)         //P2.1输入的值

#define TPDI_CLR    P2OUT &= ~BIT4            //TPDI置低
#define TPDI_SET    P2OUT |=  BIT4            //TPDI置高

#define TPCS_CLR    P2OUT &= ~BIT5            //TPCS置低
#define TPCS_SET    P2OUT |=  BIT5            //TPCS置高

#define TPCLK_CLR   P2OUT &= ~BIT6            //TPCLK置低
#define TPCLK_SET   P2OUT |=  BIT6            //TPCLK置高

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
