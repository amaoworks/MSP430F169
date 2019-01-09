/*
 * LCD1602.h
 *
 *  Created on: 2018年11月3日
 *      Author: liu
 */

#ifndef LCD1602_H_
#define LCD1602_H_
#include <msp430x16x.h>
#define CPU_F ((double)8000000)
#define delay_us(x) __delay_cycles((long)(CPU_F)*(double)x/1000000.0)
#define delay_ms(x) __delay_cycles((long)(CPU_F)*(double)x/1000.0)
#define DataDIR         P4DIR                     //数据口方向
#define DataPort        P4OUT                     //P4口为数据口
//12864/1602液晶控制管脚
#define RS_CLR          P5OUT &= ~BIT5           //RS置低
#define RS_SET          P5OUT |=  BIT5           //RS置高
#define RW_CLR          P5OUT &= ~BIT6           //RW置低
#define RW_SET          P5OUT |=  BIT6           //RW置高
#define EN_CLR          P5OUT &= ~BIT7           //E置低
#define EN_SET          P5OUT |=  BIT7           //E置高
#define PSB_CLR         P5OUT &= ~BIT0            //PSB置低，串口方式
#define PSB_SET         P5OUT |=  BIT0            //PSB置高，并口方式
#define RST_CLR         P5OUT &= ~BIT1            //RST置低
#define RST_SET         P5OUT |= BIT1             //RST置高
#define uchar unsigned char
#define uint unsigned int
void clk_init();
void LCD_Port_init();
void LCD_write_com(unsigned char com);
void LCD_write_data(unsigned char data);
void LCD_clear(void);
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s);
void LCD_write_num(unsigned char x,unsigned char y,unsigned int data);
void LCD_write_single_char(unsigned char x,unsigned char y,unsigned char data);
void LCD_init(void);
#endif /* LCD1602_H_ */

