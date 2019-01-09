#include "msp430x16x.h"
#include "beep.h"
#include "golbal.h"
/**********************************************                              
                蜂鸣器    
**********************************************/
void beep()
{
	P1DIR |= BIT4;//蜂鸣器IO方向设置为输出
	if(beep2)
	{
		unsigned char i = 0,j;
		while(i<50)
		{ 
			beep1_ON;
			for(j=0;j<10;j++);
			beep1_OFF;
			for(j=0;j<5;j++);
			i++;
		}
	}
}
