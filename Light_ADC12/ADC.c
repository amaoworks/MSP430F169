/*
 * ADC.c
 *
 *  Created on: 2018年12月20日
 *      Author: Brown
 */
#include "ADC.h"

extern unsigned int data;

/********************
 *函数功能:实现ADC12单通道单次转换初始化
 *参数说明:sref:0-选择内部电压参考源2.5v 1-选择外部电压参考源VEREF;
 *打开 ADC12CTL0 |= ADC12SC;即可开始转换，再while循环中调用即可一直保持采样；
 *AD采样口:P6.0口
 * */
void ADC12_SINGLE_init(unsigned char sref)
{
    switch(sref)
    {
    case 0:ADC12CTL0 = ADC12ON + SHT0_8 + MSC + REFON + REF2_5V;   //使用内部电压，打开ADC12内核，内部参考电压2.5V
    ADC12CTL1 =SHP;
    ADC12MCTL0 = SREF_1;break;                              //使用内部电压2.5v
    case 1:ADC12CTL0 = ADC12ON + SHT0_8+MSC;                           //使用外部电压，打开ADC12内核
    ADC12CTL1=SHP;
    ADC12MCTL0 = SREF_2;break;                            //选择外部参考电压
    }
    ADC12CTL0 |= ENC;
    P6SEL |=BIT0;
    ADC12IE |=BIT0;
    _EINT();                                                        //开总中断
}

/*单通道单次转换中断程序
 * data:接收所需变量,自定义;
 * ADC12MEM0:通道存储寄存器,存储AD转换值
 * */
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR (void)
{
    data=ADC12MEM0;
}
