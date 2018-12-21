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
	    ADC12CTL0 |= ADC12SC;   //一直采样

	    temp=(ulong)(data)*250;            //转换公式，ADC数字量转换为电压大小，注意数据类型
	    Trdata=temp/4095;                    //12位精度，除以4095

	    LCD_Display_num(0,0,data);      //ADC取值
	    LCD_Display_num(0,1,Trdata);    //电压值
	}

}
