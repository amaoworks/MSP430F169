/*
 * LED.c
 *
 *  Created on: 2018��12��13��
 *      Author: Brown
 */
#include "LED.h"

void LED_Portinit()
{
  LED8DIR = 0xff;                    //����IO�ڷ���Ϊ���
  LED8 = 0xFF;                       //��ʼ����Ϊ00
}
