#include <msp430f169.h>
#include <stdio.h>
#include "UART.h"
#include "LCD.h"

unsigned int long temp;
unsigned int long TemperF;                                   //华氏温度
unsigned int long TemperC;                                   //摄氏温度
void main(void) {
    WDTCTL = WDTPW + WDTHOLD;                                //关闭系统看门狗
    ADC12CTL0 = SHT0_8 + REFON + ADC12ON;                    //内部1.5V参考电压,打开ADC12模块,设置采样保持定时器
    ADC12CTL1 = SHP;                                         //采使用采样定时器
    ADC12MCTL0 = SREF_1 + INCH_10;                           //参考电压和通道选择
    ADC12IE = BIT0;                                          //ADC12MEM0
    ADC12CTL0 |= ENC;                                        //允许转换

    LCD_Port_init();            // Init the LCD1602
    LCD_Init();

    _BIS_SR(GIE);                                            //开启系统中断

//    UART1_Init();
//    unsigned char a[10];
//    int z = 0;
//    int new = 1;
    while(1) {
        ADC12CTL0 |= ADC12SC;                                //开始采样并AD转换

        //oF = ((x/4096)*1500mV)-923mV)*1/1.97mV = x*761/4096 - 468
        //IntDegF = (ADC12MEM0 - 2519)* 761/4096
        TemperF = (temp - 2519) * 761;
        TemperF = TemperF / 4096;                            //简化的华氏温度转换公式

        //oC = ((x/4096)*1500mV)-986mV)*1/3.55mV = x*423/4096 - 278
        //IntDegC = (ADC12MEM0 - 2692)* 423/4096
        TemperC = (temp - 2692) * 423;
        TemperC = TemperC / 4096;                            //简化的摄氏温度转换公式


        LCD_Display_num(0,0,TemperC);

//        new=56;
//        sprintf(a,"%d", new);
//        for(z=0;z<10;z++)
//            Uart1Send_Byte(TemperC);
//        _NOP();                                              //加入断点可用来观察IntDegF和IntDegC结果
    }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void) {
    temp = ADC12MEM0;                                          //保存转换结果
}
