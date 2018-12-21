/*
 * ADC.c
 *
 *  Created on: 2018��12��20��
 *      Author: Brown
 */
#include "ADC.h"

extern unsigned int data;

/********************
 *��������:ʵ��ADC12��ͨ������ת����ʼ��
 *����˵��:sref:0-ѡ���ڲ���ѹ�ο�Դ2.5v 1-ѡ���ⲿ��ѹ�ο�ԴVEREF;
 *�� ADC12CTL0 |= ADC12SC;���ɿ�ʼת������whileѭ���е��ü���һֱ���ֲ�����
 *AD������:P6.0��
 * */
void ADC12_SINGLE_init(unsigned char sref)
{
    switch(sref)
    {
    case 0:ADC12CTL0 = ADC12ON + SHT0_8 + MSC + REFON + REF2_5V;   //ʹ���ڲ���ѹ����ADC12�ںˣ��ڲ��ο���ѹ2.5V
    ADC12CTL1 =SHP;
    ADC12MCTL0 = SREF_1;break;                              //ʹ���ڲ���ѹ2.5v
    case 1:ADC12CTL0 = ADC12ON + SHT0_8+MSC;                           //ʹ���ⲿ��ѹ����ADC12�ں�
    ADC12CTL1=SHP;
    ADC12MCTL0 = SREF_2;break;                            //ѡ���ⲿ�ο���ѹ
    }
    ADC12CTL0 |= ENC;
    P6SEL |=BIT0;
    ADC12IE |=BIT0;
    _EINT();                                                        //�����ж�
}

/*��ͨ������ת���жϳ���
 * data:�����������,�Զ���;
 * ADC12MEM0:ͨ���洢�Ĵ���,�洢ADת��ֵ
 * */
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR (void)
{
    data=ADC12MEM0;
}
