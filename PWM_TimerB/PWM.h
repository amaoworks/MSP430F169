/*
 * PWM.h
 *
 *  Created on: 2018��12��5��
 *      Author: Brown
 */
#include "Config.h"
#ifndef PWM_H_
#define PWM_H_

void PWM_Init(unsigned char Clk, unsigned char Output, unsigned char Model, unsigned int ccr0, unsigned int ccrX);

#endif /* PWM_H_ */
