/*
 * ADC.c
 *
 *  Created on: 2018年12月6日
 *      Author: Brown
 */
#include "ADC.h"

extern unsigned int long temp;

void ADC12_Init(){
    ADC12CTL0 = SHT0_8 + REFON + ADC12ON;                    //内部1.5V参考电压,打开ADC12模块,设置采样保持定时器
    ADC12CTL1 = SHP;                                         //采使用采样定时器
    ADC12MCTL0 = SREF_1 + INCH_10;                           //参考电压和通道选择
    ADC12IE = BIT0;                                          //ADC12MEM0
    ADC12CTL0 |= ENC;                                        //允许转换
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void) {
    temp = ADC12MEM0;                                          //保存转换结果
}
