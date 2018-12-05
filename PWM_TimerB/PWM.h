/*
 * PWM.h
 *
 *  Created on: 2018Äê12ÔÂ5ÈÕ
 *      Author: Brown
 */
#include "Config.h"
#ifndef PWM_H_
#define PWM_H_

void PWM_Init(unsigned char Clk, unsigned char Output, unsigned char Model, unsigned int ccr0, unsigned int ccrX);

#endif /* PWM_H_ */
