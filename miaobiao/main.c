#include <msp430f169.h>
#include "LCD1602.h"
#define uchar unsigned char
#define uint unsigned int

uint num=0,second=0,cpp=0,second1,num1;

void Port_init()
{
    P6DIR =0xff;
    P6OUT=0xff;
    P1IFG=0;
    P1IE|=(BIT0+BIT1+BIT2+BIT3);
    P1IES|=(BIT0+BIT1+BIT2+BIT3);
}

void TIMERA_init()
{
    TACTL|=(TASSEL_2+ID_3+MC_1+TAIE);
    TACCR0=10000;
}

void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //打开XT2振荡器
  BCSCTL2|=SELM1+SELS;              //MCLK为8MHZ，SMCLK为8MHZ
  do{
    IFG1&=~OFIFG;                   //清楚振荡器错误标志
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //如果标志位1，则继续循环等待
  IFG1&=~OFIFG;
}

/*
 * main.c
 */

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	 // stop watchdog timer
	TIMERA_init();
	LCD_Port_init();
	LCD_clear();
	LCD_init();
	Clock_Init();
	Port_init();
	_EINT();
	uchar i;
	while(1){
	  /*  for(i=0;i<10;i++){
	    LCD_write_com(0x01);
	    delay_ms(100);}*/
	  if(num>99)
	        num=0;
	  	LCD_write_str(0,0,"time:");
	    LCD_write_single_char(5,0,':');
	    LCD_write_single_char(6,0,' ');
	    LCD_write_num(7,0,second/10);
	    LCD_write_num(8,0,second%10);
	    LCD_write_single_char(9,0,':');
	    LCD_write_num(10,0,num/10);
	    LCD_write_num(11,0,num%10);
	    LCD_write_single_char(0,1,'A');
	    LCD_write_single_char(1,1,':');
	    LCD_write_single_char(2,1,' ');
	    LCD_write_num(3,1,second1/10);
	    LCD_write_num(4,1,second1%10);
	    LCD_write_single_char(5,1,':');
	    LCD_write_num(6,1,num1/10);
	    LCD_write_num(7,1,num1%10);
	}
}

#pragma vector =PORT1_VECTOR
__interrupt void keys_operate(void)
{
    if(P1IFG&BIT0)
    {   cpp++;
        if(cpp%2==0)
        TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;
        else
            TACTL &= 0xfffd;
    }
    if(P1IFG&BIT1)
    {
        second1=second;
        num1=num;
    }
    P1IFG=0;
}
#pragma vector=TIMERA1_VECTOR
__interrupt void cal_time(void)
{
    switch(TAIV)
    {
    case 0x02:break;
    case 0x08:break;
    case 0x0A:num++;break;
    }
    if(num==100)
    {    second++;
         num=0;
        }
}
