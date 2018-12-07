/*
 * ADC.c
 *
 *  Created on: 2018��12��6��
 *      Author: Brown
 */
#include "ADC.h"

extern unsigned int long temp;

void ADC12_Init(){
    ADC12CTL0 = SHT0_8 + REFON + ADC12ON;                    //�ڲ�1.5V�ο���ѹ,��ADC12ģ��,���ò������ֶ�ʱ��
    ADC12CTL1 = SHP;                                         //��ʹ�ò�����ʱ��
    ADC12MCTL0 = SREF_1 + INCH_10;                           //�ο���ѹ��ͨ��ѡ��
    ADC12IE = BIT0;                                          //ADC12MEM0
    ADC12CTL0 |= ENC;                                        //����ת��
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void) {
    temp = ADC12MEM0;                                          //����ת�����
}
