/*
 * PWM.h
 *
 *  Created on: 2018Äê12ÔÂ5ÈÕ
 *      Author: Brown
 */
#include "TFT.h"
#ifndef PWM_H_
#define PWM_H_

void PWM_Init(unsigned char Clk, unsigned char Output, unsigned char Model, unsigned int ccr0, unsigned int ccrX);
void Light();
extern void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);

#endif /* PWM_H_ */
