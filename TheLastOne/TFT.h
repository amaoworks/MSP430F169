/*
 * TFT.h
 *
 *  Created on: 2018��12��27��
 *      Author: Brown
 */

#ifndef TFT_H_
#define TFT_H_

#include <msp430f169.h>
#include "font8x16.h"
#include "font16x16.h"
#include "font24x24.h"

#ifndef __NBCTFT_H__
#define __NBCTFT_H__

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

//��ʱ������IAR�Դ�������ʹ�õ�
#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//2.8��TFT������ʾ�������Ӳ������
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�

#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�

#define RD_CLR          P5OUT &= ~BIT7           //E�õ�
#define RD_SET          P5OUT |=  BIT7           //E�ø�

#define CS_CLR          P5OUT &= ~BIT0            //CS�õ�
#define CS_SET          P5OUT |=  BIT0            //CS�ø�

#define RST_CLR         P5OUT &= ~BIT3            //RST�õ�
#define RST_SET         P5OUT |=  BIT3            //RST�ø�

#define LE_CLR          P5OUT &= ~BIT1            //LE�õ�
#define LE_SET          P5OUT |=  BIT1            //LE�ø�

//����/12864Һ��/1602Һ�������ݿڣ���Һ������
#define DataDIR         P4DIR                     //���ݿڷ���
#define DataPort        P4OUT                     //P4��Ϊ���ݿ�

//��ɫ���룬TFT��ʾ��
#define White          0xFFFF                                                               //��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

unsigned char pic[];

void TFT_PortInit();
void TFT_Initial(void);
void show_colour_bar (void);
void Write_Cmd_Data(unsigned char x, unsigned int y);
void Write_Cmd(unsigned char DH,unsigned char DL);
void Write_Data(unsigned char DH,unsigned char DL);
void delayms(unsigned int tt);
void show_photo(void);
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color);

void  Write_Data_U16(unsigned int y);
//Read_RegData(unsigned char Regaddr);
void CLR_Screen(unsigned int bColor);
void PutGB3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);
void Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor);
void LCD_PutString24(unsigned short x, unsigned short y, uchar *s, uint fColor, uint bColor);
void Put_pixel(unsigned int x,unsigned int y,unsigned int color);
void address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void line(int x1,int y1,int x2,int y2,int color);
void draw_circle(int x, int y, int r, int color);

void Line(  uchar X0,
            uchar Y0,
            uchar X1,
            uchar Y1,
            unsigned int color);

void Rectangle( uchar left,
                uchar top,
                uchar right,
                uchar bottom,
                unsigned int color);

void Bar(   uchar left,
            uchar top,
            uchar right,
            uchar bottom,
            unsigned int color);

#endif

#endif /* TFT_H_ */
