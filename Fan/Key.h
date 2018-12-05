/*
 * Key.h
 *
 *  Created on: 2018Äê12ÔÂ4ÈÕ
 *      Author: Brown
 */
//#include "Config.h"
#ifndef KEY_H_
#define KEY_H_

#define KeyPort         P1IN

void Key_PortInit();
uchar Key_Scan(void);

#endif /* KEY_H_ */
