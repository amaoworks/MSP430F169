/*
 * Touch.h
 *
 *  Created on: 2018��12��6��
 *      Author: Brown
 */
#include "Config.h"
#ifndef TOUCH_H_
#define TOUCH_H_

struct struct1                          //����һ��������Ϊstruct1�Ľṹ,����������Աx��y
{
    uint x;                         //��Աx
    uint y;                         //��Աy
};

extern struct struct1 coordinate;      //����һ����ΪTp_pix�Ľṹ����,���ڴ�Ŵ����Ĵ����������
extern uint  lx,ly;

void start_7843();
void Write_7843(uchar temp);          //SPIд8λ�����������IC
uint Read_7843();                     //SPI ������
struct struct1 AD7843() ;
uchar pix_filter(struct struct1 pix1,struct struct1 pix2);
uchar Getpix();

#endif /* TOUCH_H_ */
