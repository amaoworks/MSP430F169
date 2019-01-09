
/*-----------------------------------------------
6 x 8 font
1 pixel space at left and bottom
index = ASCII - 32             按ASCII-32排列的
-----------------------------------------------*/
unsigned char const font6x8[][6] =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },// sp
{ 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },// !
{ 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },// "
{ 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },// #
{ 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },// $
{ 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },// %
{ 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },// &
{ 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },// '
{ 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },// (
{ 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },// )
{ 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },// *
{ 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },// +
{ 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },// ,
{ 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },// -
{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },// .
{ 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },// /
{ 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },// 0
{ 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },// 1
{ 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },// 2
{ 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },// 3
{ 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },// 4
{ 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },// 5
{ 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },// 6
{ 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },// 7
{ 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },// 8
{ 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },// 9
{ 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },// :
{ 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },// ;
{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },// <
{ 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },// =
{ 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },// >
{ 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },// ?
{ 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },// @
{ 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },// A
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },// B
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },// C
{ 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },// D
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },// E
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },// F
{ 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },// G
{ 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },// H
{ 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },// I
{ 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },// J
{ 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },// K
{ 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },// L
{ 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },// M
{ 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },// N
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },// O
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },// P
{ 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },// Q
{ 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },// R
{ 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },// S
{ 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },// T
{ 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },// U
{ 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },// V
{ 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },// W
{ 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },// X
{ 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },// Y
{ 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },// Z
{ 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },// [
{ 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },// 55
{ 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },// ]
{ 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },// ^
{ 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },// _
{ 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },// '
{ 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },// a
{ 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },// b
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },// c
{ 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },// d
{ 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },// e
{ 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },// f
{ 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },// g
{ 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },// h
{ 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },// i
{ 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },// j
{ 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },// k
{ 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },// l
{ 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },// m
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },// n
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },// o
{ 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },// p
{ 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },// q
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },// r
{ 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },// s
{ 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },// t
{ 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },// u
{ 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },// v
{ 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },// w
{ 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },// x
{ 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },// y
{ 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },// z
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }// horiz lines
};

unsigned char const shuzi[]={
/*--  文字:  0  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,

/*--  文字:  1  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

/*--  文字:  2  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,

/*--  文字:  3  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  4  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,

/*--  文字:  5  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  6  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  7  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,

/*--  文字:  8  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,

/*--  文字:  9  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,
};

unsigned char const han[]=
{
/*--  文字:  俄  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x20,0xF8,0x17,0x12,0x14,0xFC,0x12,0x92,0x10,0xFF,0x10,0x12,0xDC,0x90,0x00,
0x00,0x00,0x7F,0x00,0x24,0x62,0x3F,0x01,0x20,0x10,0x0B,0x0C,0x33,0x41,0x30,0x00,

/*--  文字:  罗  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x7E,0x22,0x22,0x22,0xFE,0xA2,0xA2,0xBE,0xA2,0xA2,0xA2,0xBE,0x00,0x00,
0x80,0x88,0x88,0x84,0x42,0x43,0x25,0x28,0x10,0x10,0x08,0x04,0x03,0x00,0x00,0x00,

/*--  文字:  斯  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x04,0x04,0xFF,0x94,0x94,0x94,0xFF,0x04,0x00,0xFE,0x22,0x22,0xE1,0x21,0x20,0x00,
0x44,0x24,0x37,0x04,0x04,0x14,0x67,0x44,0x30,0x0F,0x00,0x00,0xFF,0x00,0x00,0x00,

/*--  文字:  方  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x08,0x08,0x08,0x08,0x08,0xF9,0x4A,0x4C,0x48,0x48,0xC8,0x08,0x08,0x08,0x00,
0x40,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x20,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,

/*--  文字:  块  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0xFF,0x10,0x10,0x00,0x08,0x08,0xFF,0x08,0x08,0x08,0xF8,0x00,0x00,0x00,
0x08,0x18,0x0F,0x04,0x85,0x41,0x31,0x0D,0x03,0x05,0x09,0x11,0x31,0x61,0x21,0x00,

/*--  文字:  第  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x08,0x04,0xD3,0x56,0x5A,0x52,0x5A,0xF4,0x53,0x56,0x5A,0x72,0x02,0x02,0x00,
0x00,0x20,0x20,0x23,0x12,0x12,0x0A,0x06,0xFF,0x02,0x02,0x12,0x22,0x1E,0x00,0x00,

/*--  文字:  关  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x10,0x10,0x10,0x11,0x1E,0x14,0xF0,0x10,0x18,0x17,0x12,0x18,0x10,0x00,0x00,
0x01,0x81,0x41,0x21,0x11,0x09,0x05,0x03,0x05,0x09,0x31,0x61,0xC1,0x41,0x01,0x00,
};



/*-----------头像-----------*/
unsigned char const android[6][84]=
{
/*--  调入了一幅图像：C:\Documents and Settings\homex\桌面\android.bmp  --*/
/*--  宽度x高度=80x48  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x40,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x40,
0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x40,0x40,0xB8,0xCC,0x46,0x43,0x41,0x48,0x40,0x40,0x40,0x40,0x40,0x48,0x41,
0x43,0x46,0xCC,0xB8,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x01,0x02,0x02,0x01,0x1F,0x10,0xF0,0x00,0x00,0x00,0xF0,0x10,0xF0,0x00,0x00,0x00,
0xF0,0x10,0x1F,0x01,0x02,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x20,0x20,0xC0,0x00,0xC0,
0x20,0x20,0x20,0xC0,0x00,0x20,0x21,0x22,0x22,0xC2,0x01,0x20,0x21,0x22,0x22,0xC2,
0x01,0xC0,0x20,0x20,0x20,0xC0,0x00,0xE0,0x00,0x20,0x20,0x20,0x20,0xC0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x04,0x00,0x07,0x00,0x07,
0x00,0x00,0x00,0x07,0x00,0x04,0x04,0x04,0x04,0x03,0x00,0x01,0x01,0x01,0x03,0x06,
0x00,0x03,0x04,0x04,0x04,0x03,0x00,0x07,0x00,0x04,0x04,0x04,0x04,0x03,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,};


unsigned char const nokia[6][84]={
/*--  调入了一幅图像：C:\Documents and Settings\homex\桌面\nokia.bmp  --*/
/*--  宽度x高度=80x48  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xF8,0xF8,0xF8,0xF8,0x78,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x00,
0x00,0x00,0xF8,0xF8,0xF8,0xF8,0x00,0xE0,0xF0,0xF8,0x38,0x38,0x38,0x38,0x38,0x38,
0x38,0x38,0x38,0x38,0xF8,0xF0,0xE0,0x00,0xF8,0xF8,0xF8,0xF8,0x00,0x00,0x80,0xC0,
0xE0,0xF0,0xF8,0x78,0x38,0x38,0x18,0x00,0x00,0xF8,0xF8,0xF8,0xF8,0x00,0x00,0x00,
0x00,0x00,0xC0,0xF0,0xF8,0xF8,0x78,0xF8,0xF8,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x7F,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3E,
0x7C,0x78,0x7F,0x7F,0x7F,0x7F,0x00,0x1F,0x3F,0x7F,0x70,0x70,0x70,0x70,0x70,0x70,
0x70,0x70,0x70,0x70,0x7F,0x3F,0x1F,0x00,0x7F,0x7F,0x7F,0x7F,0x00,0x03,0x07,0x0F,
0x1F,0x3F,0x7C,0x78,0x70,0x70,0x60,0x00,0x00,0x7F,0x7F,0x7F,0x7F,0x00,0x60,0x78,
0x7C,0x7F,0x3F,0x1F,0x1D,0x1C,0x1C,0x1C,0x1D,0x1F,0x3F,0x7F,0x7C,0x78,0x60,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xE0,0x10,0x08,0x08,0xC0,0x20,0x20,0x20,0xC0,0x00,0xC0,0x20,
0x20,0xC0,0x00,0xC0,0x20,0x20,0xC0,0x00,0xC0,0x20,0x20,0xC0,0x00,0x80,0x60,0x20,
0x00,0x20,0xF0,0x20,0x00,0xE8,0x00,0x00,0xC0,0x20,0x20,0xC0,0x00,0xC0,0x20,0x20,
0xC0,0x00,0x00,0x00,0xF0,0x08,0x08,0xF0,0x00,0xC0,0x20,0x20,0xC0,0x00,0xC0,0x20,
0x20,0x20,0xC0,0x00,0xE0,0x20,0x20,0xC0,0x00,0xF8,0x00,0xC0,0x20,0x20,0xC0,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x04,0x08,0x08,0x07,0x08,0x08,0x08,0x07,0x00,0x0F,0x00,
0x00,0x0F,0x00,0x0F,0x00,0x00,0x0F,0x00,0x07,0x09,0x09,0x08,0x00,0x03,0x0C,0x08,
0x00,0x00,0x0F,0x08,0x00,0x0F,0x00,0x00,0x0F,0x00,0x00,0x0F,0x00,0x27,0x28,0x28,
0x1F,0x00,0x00,0x00,0x0F,0x01,0x01,0x00,0x00,0x07,0x09,0x09,0x08,0x00,0x07,0x08,
0x08,0x08,0x07,0x00,0x3F,0x08,0x08,0x07,0x00,0x0F,0x00,0x07,0x09,0x09,0x08,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
};

/****************************************
         fang kuai 8x8
*****************************************/
unsigned char const fk[28][8]=
{
/*--  宽度x高度=8x8  --*/
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0xFC,0xFC,0xC0,0xC0,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x30,0x30,0x30,0x30,0x3C,0x3C,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x0C,0x0C,0xFC,0xFC,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x3C,0x3C,0x0C,0x0C,0x0C,0x0C,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0xC0,0xC0,0xFC,0xFC,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x0C,0x0C,0x0C,0x0C,0x3C,0x3C,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3F,0x3F,0x03,0x03,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x3C,0x3C,0x30,0x30,0x30,0x30,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3C,0x3C,0xF0,0xF0,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x30,0x30,0x3C,0x3C,0x0C,0x0C,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3C,0x3C,0xF0,0xF0,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x30,0x30,0x3C,0x3C,0x0C,0x0C,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0xF0,0xF0,0x3C,0x3C,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x0C,0x0C,0x3C,0x3C,0x30,0x30,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0xF0,0xF0,0x3C,0x3C,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x0C,0x0C,0x3C,0x3C,0x30,0x30,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x30,0x30,0x3C,0x3C,0x30,0x30,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3F,0x3F,0x0C,0x0C,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x0C,0x0C,0x3C,0x3C,0x0C,0x0C,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x0C,0x0C,0x3F,0x3F,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,
/*--  宽度x高度=8x8  --*/
0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,
};

unsigned char suijishu = 0;
unsigned char speed = 16;

unsigned char beep2 = 1;








