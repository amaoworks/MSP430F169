/*
 * GUI.h
 *
 *  Created on: 2018Äê12ÔÂ6ÈÕ
 *      Author: Brown
 */
#include "Config.h"
#ifndef GUI_H_
#define GUI_H_

void GUIline(uint x0,uint y0,uint x1,uint y1,uint line_color);
void GUIfull(uint x0,uint y0,uint x1,uint y1,uint full_colour) ;
void plotC(uint x,uint y,uint xc,int yc,uint yc_colour) ;
void GUIcircle(uint xc,uint yc,uint r,uint circle_colour) ;
void GUIDotline(uint x0,uint y0,uint x1,uint y1,uint line_color);

#endif /* GUI_H_ */
