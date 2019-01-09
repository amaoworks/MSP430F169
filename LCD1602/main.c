/*��Ŀ��飺��*/
#include <msp430f169.h>
#include <stdio.h>
#include <string.h>
#include "LCD1602.h"
//#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
//#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
//#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define uchar unsigned char
#define uint unsigned int

void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //��XT2����
  BCSCTL2|=SELM1+SELS;              //MCLKΪ8MHZ��SMCLKΪ8MHZ
  do{
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
  IFG1&=~OFIFG;
}

/*
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    TimeA_init();
    Clock_Init();
    port_init();                        //�˿ڳ�ʼ��
    Port_init();
    LCD_clear();
    LCD_init();
    while(1)
    {
        LCD_write_str(0,0,"hello.world");
    }

}
