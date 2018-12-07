/*
 * PWM.h
 *
 *  Created on: 2018Äê12ÔÂ4ÈÕ
 *      Author: Brown
 */
#include "Config.h"
#ifndef PWM_H_
#define PWM_H_

void PWM_init();
void start();
void stop();
void speed(unsigned char shift);
void Smart_speed();

#endif /* PWM_H_ */
