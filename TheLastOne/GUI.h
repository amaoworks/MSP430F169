/*
 * GUI.h
 *
 *  Created on: 2018Äê12ÔÂ28ÈÕ
 *      Author: Brown
 */
#include "TFT.h"
#ifndef GUI_H_
#define GUI_H_

void GUIpoint(unsigned int x,unsigned int y,unsigned int color);
void GUIline(uint x0,uint y0,uint x1,uint y1,uint line_color);
void GUIDotline(uint x0,uint y0,uint x1,uint y1,uint line_color);
void GUIfull(uint x0,uint y0,uint x1,uint y1,uint full_colour);
void GUIsquare1pix(uint x0,uint y0,uint x1,uint y1,uint full_colour);
void GUIsquare2pix(uint x0,uint y0,uint x1,uint y1,uint full_colour);
void plotC(uint x,uint y,uint xc,int yc,uint yc_colour) ;
void GUIcircle(uint xc,uint yc,uint r,uint circle_colour) ;

extern void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
extern void  Write_Data_U16(unsigned int y);

#endif /* GUI_H_ */
