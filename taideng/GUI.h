/*
 * GUI.h
 *
 *  Created on: 2018Äê12ÔÂ24ÈÕ
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef GUI_H_
#define GUI_H_

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

void GUIline(uint x0,uint y0,uint x1,uint y1,uint line_color);
void GUIDotline(uint x0,uint y0,uint x1,uint y1,uint line_color);
void GUIfull(uint x0,uint y0,uint x1,uint y1,uint full_colour);
void GUIsquare1pix(uint x0,uint y0,uint x1,uint y1,uint full_colour);
void GUIsquare2pix(uint x0,uint y0,uint x1,uint y1,uint full_colour);
void plotC(uint x,uint y,uint xc,int yc,uint yc_colour) ;
void GUIcircle(uint xc,uint yc,uint r,uint circle_colour) ;
void GUIDotline(uint x0,uint y0,uint x1,uint y1,uint line_color);

extern void Put_pixel(unsigned int x,unsigned int y,unsigned int color);

#endif /* GUI_H_ */
