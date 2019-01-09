/*
 * LCD1602.h
 *
 *  Created on: 2018��11��3��
 *      Author: liu
 */

#ifndef LCD1602_H_
#define LCD1602_H_
#include <msp430x16x.h>
#define CPU_F ((double)8000000)
#define delay_us(x) __delay_cycles((long)(CPU_F)*(double)x/1000000.0)
#define delay_ms(x) __delay_cycles((long)(CPU_F)*(double)x/1000.0)
#define DataDIR         P4DIR                     //���ݿڷ���
#define DataPort        P4OUT                     //P4��Ϊ���ݿ�
//12864/1602Һ�����ƹܽ�
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�
#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�
#define EN_CLR          P5OUT &= ~BIT7           //E�õ�
#define EN_SET          P5OUT |=  BIT7           //E�ø�
#define PSB_CLR         P5OUT &= ~BIT0            //PSB�õͣ����ڷ�ʽ
#define PSB_SET         P5OUT |=  BIT0            //PSB�øߣ����ڷ�ʽ
#define RST_CLR         P5OUT &= ~BIT1            //RST�õ�
#define RST_SET         P5OUT |= BIT1             //RST�ø�
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

