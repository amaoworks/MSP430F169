#include <msp430.h> 
#include "Config.h"
#include "ADC.h"
#include "LCD.h"

unsigned int data, Trdata;

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Clock_Init();
	ADC12_SINGLE_init(0);
	LCD_Port_init();
	LCD_Init();

	ulong temp;
	
	while(1){
	    ADC12CTL0 |= ADC12SC;   //һֱ����

	    temp=(ulong)(data)*250;            //ת����ʽ��ADC������ת��Ϊ��ѹ��С��ע����������
	    Trdata=temp/4095;                    //12λ���ȣ�����4095

	    LCD_Display_num(0,0,data);      //ADCȡֵ
	    LCD_Display_num(0,1,Trdata);    //��ѹֵ
	}

}
