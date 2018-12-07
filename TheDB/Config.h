/*
 * Config.h
 *
 *  Created on: 2018年12月6日
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef CONFIG_H_
#define CONFIG_H_

//延时函数，IAR自带，经常使用到
#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//自定义数据结构，方便使用
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//8个LED灯，连接在P6口，可通过断开电源停止使用，ADC使用时断开电源
#define LED8DIR         P6DIR
#define LED8            P6OUT                             //P6口接LED灯，8个

//2.8寸TFT彩屏显示控制相关硬件配置
#define RS_CLR          P5OUT &= ~BIT5           //RS置低
#define RS_SET          P5OUT |=  BIT5           //RS置高

#define RW_CLR          P5OUT &= ~BIT6           //RW置低
#define RW_SET          P5OUT |=  BIT6           //RW置高

#define RD_CLR          P5OUT &= ~BIT7           //E置低
#define RD_SET          P5OUT |=  BIT7           //E置高

#define CS_CLR          P5OUT &= ~BIT0            //CS置低
#define CS_SET          P5OUT |=  BIT0            //CS置高

#define RST_CLR         P5OUT &= ~BIT3            //RST置低
#define RST_SET         P5OUT |=  BIT3            //RST置高

#define LE_CLR          P5OUT &= ~BIT1            //LE置低
#define LE_SET          P5OUT |=  BIT1            //LE置高

//2.8寸TFT彩屏触摸屏控制相关硬件配置
#define PEN_CLR         P2OUT &= ~BIT0           //PEN置低,触碰触摸屏时，Penirq引脚由未触摸时的高电平变为低电平
#define PEN_SET         P2OUT |=  BIT0           //PEN置高
#define PEN             (P2IN & 0x01)            //P2.0输入的值

#define TPDO_CLR    P2OUT &= ~BIT1           //TPDO置低
#define TPDO_SET    P2OUT |=  BIT1           //TPDO置高
#define TPDOUT          ((P2IN>>1)&0x01)         //P2.1输入的值

#define BUSY_CLR    P2OUT &= ~BIT3           //BUSY置低
#define BUSY_SET    P2OUT |=  BIT3           //BUSY置高

#define TPDI_CLR    P2OUT &= ~BIT4            //TPDI置低
#define TPDI_SET    P2OUT |=  BIT4            //TPDI置高

#define TPCS_CLR    P2OUT &= ~BIT5            //TPCS置低
#define TPCS_SET    P2OUT |=  BIT5            //TPCS置高

#define TPCLK_CLR   P2OUT &= ~BIT6            //TPCLK置低
#define TPCLK_SET   P2OUT |=  BIT6            //TPCLK置高

//彩屏/12864液晶/1602液晶的数据口，三液晶共用
#define DataDIR         P4DIR                     //数据口方向
#define DataPort        P4OUT                     //P4口为数据口

//颜色代码，TFT显示用
#define White          0xFFFF                                                               //显示颜色代码
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

void Clock_Init();
void WDT_Init();

#endif /* CONFIG_H_ */
