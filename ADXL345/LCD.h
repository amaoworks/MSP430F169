/*
 * LCD.h
 *
 *  Created on: 2018Äê12ÔÂ2ÈÕ
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef LCD_H_
#define LCD_H_

#define uchar unsigned char
#define uint unsigned int
#define CPU_F ((double)8000000)
#define delay_us(x) __delay_cycles((long)CPU_F*(double)x/1000000.0)
#define delay_ms(x) __delay_cycles((long)CPU_F*(double)x/1000.0)
#define RS_H P3OUT|=BIT1;
#define RS_L P3OUT&=~BIT1;
#define RW_H P3OUT|=BIT2;
#define RW_L P3OUT&=~BIT2;
#define E_H P3OUT|=BIT3;
#define E_L P3OUT&=~BIT3;
#define Data_DIR P4DIR
#define Data_IN P4IN
#define Data_OUT P4OUT

uchar busy;
static uchar data_scan[10]={'0','1','2','3','4','5','6','7','8','9'};
void init_LCD1602_IO(void);
void write_data(uchar data);
void write_commond(uchar commond);
uchar read_sta(void);
void read_busy(void);
void init_LCD1602(void);
void disp(uchar location,uchar data);
void DisplayOneChar(uchar X,uchar Y ,uchar DData);

#endif /* LCD_H_ */
