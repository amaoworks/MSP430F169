/*
 * Touch.h
 *
 *  Created on: 2018��12��20��
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef TOUCH_H_
#define TOUCH_H_

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
/*
 * ���ߣ�IRQ 2.0 DO 2.1 DI 2.4 CS 2.5 CLK 2.6
 */
#define PEN_CLR         P2OUT &= ~BIT0           //PEN�õ�,����������ʱ��Penirq������δ����ʱ�ĸߵ�ƽ��Ϊ�͵�ƽ
#define PEN_SET         P2OUT |=  BIT0           //PEN�ø�
#define PEN             (P2IN & 0x01)            //P2.0�����ֵ

#define TPDO_CLR    P2OUT &= ~BIT1           //TPDO�õ�
#define TPDO_SET    P2OUT |=  BIT1           //TPDO�ø�
#define TPDOUT      ((P2IN>>1)&0x01)         //P2.1�����ֵ

#define TPDI_CLR    P2OUT &= ~BIT4            //TPDI�õ�
#define TPDI_SET    P2OUT |=  BIT4            //TPDI�ø�

#define TPCS_CLR    P2OUT &= ~BIT5            //TPCS�õ�
#define TPCS_SET    P2OUT |=  BIT5            //TPCS�ø�

#define TPCLK_CLR   P2OUT &= ~BIT6            //TPCLK�õ�
#define TPCLK_SET   P2OUT |=  BIT6            //TPCLK�ø�

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
