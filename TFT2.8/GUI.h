/*
 * GUI.h
 *
 *  Created on: 2018��11��27��
 *      Author: liu
 */

#ifndef GUI_H_
#define GUI_H_
#include "TFT2.8.h"
#include "math.h"
void start_show();
void main_menu();
void GUIline(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int line_color);   //���ߺ���
void GUIfull(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour) ;
void plotC(unsigned int x,unsigned int y,unsigned int xc,int yc,unsigned int yc_colour) ;
void GUIcircle(unsigned int xc,unsigned int yc,unsigned int r,unsigned int circle_colour) ;
void GUIDotline(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int line_color);   //�����ߺ���
void key_show(unsigned char x1,unsigned char y1,unsigned char * str);
void GUIsquare2pix(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour);
#endif /* GUI_H_ */
