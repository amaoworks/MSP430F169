/*
 * Config.c
 *
 *  Created on: 2018��12��26��
 *      Author: Brown
 */
#include "Config.h"

void Clock_Init()                       //8M
{
    uchar i;
    BCSCTL1&=~XT2OFF;                   //��XT2����
    BCSCTL2|=SELM1+SELS;                //MCLKΪ8MHZ��SMCLKΪ8MHZ
    do{
        IFG1&=~OFIFG;                   //������������־
        for(i=0;i<100;i++)
            _NOP();
    }
    while((IFG1&OFIFG)!=0);             //�����־λ1�������ѭ���ȴ�
    IFG1&=~OFIFG;
}