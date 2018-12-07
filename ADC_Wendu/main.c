#include <msp430f169.h>
#include <stdio.h>
#include "UART.h"
#include "LCD.h"

unsigned int long temp;
unsigned int long TemperF;                                   //�����¶�
unsigned int long TemperC;                                   //�����¶�
void main(void) {
    WDTCTL = WDTPW + WDTHOLD;                                //�ر�ϵͳ���Ź�
    ADC12CTL0 = SHT0_8 + REFON + ADC12ON;                    //�ڲ�1.5V�ο���ѹ,��ADC12ģ��,���ò������ֶ�ʱ��
    ADC12CTL1 = SHP;                                         //��ʹ�ò�����ʱ��
    ADC12MCTL0 = SREF_1 + INCH_10;                           //�ο���ѹ��ͨ��ѡ��
    ADC12IE = BIT0;                                          //ADC12MEM0
    ADC12CTL0 |= ENC;                                        //����ת��

    LCD_Port_init();            // Init the LCD1602
    LCD_Init();

    _BIS_SR(GIE);                                            //����ϵͳ�ж�

//    UART1_Init();
//    unsigned char a[10];
//    int z = 0;
//    int new = 1;
    while(1) {
        ADC12CTL0 |= ADC12SC;                                //��ʼ������ADת��

        //oF = ((x/4096)*1500mV)-923mV)*1/1.97mV = x*761/4096 - 468
        //IntDegF = (ADC12MEM0 - 2519)* 761/4096
        TemperF = (temp - 2519) * 761;
        TemperF = TemperF / 4096;                            //�򻯵Ļ����¶�ת����ʽ

        //oC = ((x/4096)*1500mV)-986mV)*1/3.55mV = x*423/4096 - 278
        //IntDegC = (ADC12MEM0 - 2692)* 423/4096
        TemperC = (temp - 2692) * 423;
        TemperC = TemperC / 4096;                            //�򻯵������¶�ת����ʽ


        LCD_Display_num(0,0,TemperC);

//        new=56;
//        sprintf(a,"%d", new);
//        for(z=0;z<10;z++)
//            Uart1Send_Byte(TemperC);
//        _NOP();                                              //����ϵ�������۲�IntDegF��IntDegC���
    }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void) {
    temp = ADC12MEM0;                                          //����ת�����
}
