#include <msp430f169.h>
#include "LCD1602.h"
#define uchar unsigned char
#define uint unsigned int
#define KEYDIR P2DIR
#define KEYOUT P2OUT
#define KEYIN P2IN
#define KEYIE P2IE
#define KEYIES P2IES
#define KEYIFG P2IFG
uchar keyval;

void keyboard_init(){
   KEYDIR =0x0f;//高四位输入，低四位输出
   KEYOUT =0xf0;
   KEYIE=0xf0;//高4位中断允许位
   KEYIES=0xf0;//下降沿触发
   KEYIFG =0x00;//清除中断标志位
}

void main(void)
{
 	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	keyboard_init();
	LCD_clear();
	LCD_init();
	Port_init();
	P6DIR=0xff;
	_EINT();
	while(1){
	    LCD_write_single_char(0,0, keyval/10+'0');
	    LCD_write_single_char(1,0, keyval/10+'0');
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void key_cal(void)
{
    if(KEYIFG !=0x00)
    {
        uchar line,row,cmp1,cmp2;
        cmp1=0x07;
        for(line=0;line<4;line++)
        {
            KEYOUT=cmp1;
            cmp1>>=1;
            if((KEYIN & 0xf0)<0xf0)
            {   cmp2=0x10;
                for(row=0;row<4;row++)
            {
               if((KEYIN &cmp2)==0)
               {
                   keyval= line*4+row;
                   P6OUT=~keyval;
                   return;
               }
               cmp2<<=1;
           }
       }
   }
   }
   KEYIFG=0;
}
