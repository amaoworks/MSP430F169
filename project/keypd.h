#ifndef KEYPD_H_
#define KEYPD_H_

#include <msp430f169.h>
#include "type.h"
//#include "delay.h"

/***************ȫ�ֱ���***************/
uchar key_Pressed;      //�����Ƿ񱻰���:1--�ǣ�0--��
uchar key_val;          //��ż�ֵ
uchar key_Flag;         //�����Ƿ��ѷſ���1--�ǣ�0--��
//���ü����߼���ֵ���������ֵ��ӳ��
//uchar key_Map[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

void Check_Key(void);
void delay15ms();
void Key_Event(void);

#endif /* KEYPD_H_ */
