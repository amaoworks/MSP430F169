#ifndef TFT_H
#define TFT_H
#include "SPI.h"
#include "font8x16.h"
#include "font16x16.h"
#include "font24x24.h"
#include "image.h"
#include<msp430f169.h>
/*SDA接P3.1 SCL 接P3.3 cs 3.4 reset 3.5 dc 3.6*/
#define CS_DIR_O P3DIR |=BIT4
#define CS_H P3OUT |=BIT4
#define CS_L P3OUT &=~BIT4

#define RESET_DIR_O P3DIR |=BIT5
#define RESET_H P3OUT |=BIT5
#define RESET_L P3OUT &=~BIT5

#define DC_DIR_O P3DIR |=BIT6
#define DC_H P3OUT |=BIT6
#define DC_L P3OUT &=~BIT6

#define LCD_W 240
#define LCD_H 320


//画笔颜色
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN            0XBC40 //棕色
#define BRRED            0XFC07 //棕红色
#define GRAY             0X8430 //灰色
//GUI颜色

#define DARKBLUE         0X01CF //深蓝色
#define LIGHTBLUE        0X7D7C //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN       0X841F //浅绿色
#define LGRAY            0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void LCD_write_command(unsigned char com);
void TFT_port_init();
void LCD_LCD_write_data8(unsigned char data);
void LCD_LCD_write_data(unsigned int data);
void TFT_init();
void LCD_Clear(unsigned int Color);
void PutGB2424(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);
void LCD_PutString24(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) ;
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color);
void Put_pixel(unsigned int x,unsigned int y,unsigned int color);
void Show_Image(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,const unsigned char *gImage);
#endif
