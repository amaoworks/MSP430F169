#include <msp430F169.h>
#include "LCD1602.h"
unsigned int data;
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
/**
 * main.c
 */
void main(void)
{   unsigned char a,b;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	ADC12_SINGLE_init(1);
	LCD_Port_init();
	LCD_clear();
	 LCD_init();
	while(1)
	{
	    ADC12CTL0 |= ADC12SC;
	    for(a=0;a<12;a++)
	    {
	        b=data>>(11-a);
	        if((b &BIT0)==1)
	            LCD_write_single_char(a,0,1+'0');
	        else
	            LCD_write_single_char(a,0,0+'0');

	                }
	}
}
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR (void)
{
    data=ADC12MEM0;
}
