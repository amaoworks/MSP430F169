/*
 * LCD1602.c
 *
 *  Created on: 2018年11月29日
 *      Author: liu
 */



/*
 * LCD1602.c
 *
 *  Created on: 2018年11月3日
 *      Author: liu
 */
#include "LCD1602.h"
void clk_init(){
    uchar i;
    BCSCTL1&=~XT2OFF;//打开XT2振荡器；
    BCSCTL2 |=SELS+SELM1 ;//SMCLK8分频
    do
    {
        IFG1 &= ~OFIFG;//清除振荡错误标志
        for(i=0;i<0xff;i++) _NOP();

    }
    while((IFG1 & OFIFG)!=0);
    IFG1&=~OFIFG;//清除中断标志
}
//端口初始化
void LCD_Port_init()
{

        P4SEL = 0x00;
        P4DIR = 0xFF;                   //数据口输出模式
        P5SEL = 0x00;
        P5DIR|= BIT5 + BIT6 + BIT7;     //控制口设置为输出模式
}
//写入命令
void LCD_write_com(unsigned char com)
{
    RS_CLR;
    RW_CLR;
    EN_SET;
    DataPort = com;                 //命令写入端口
    delay_ms(5) ;
    EN_CLR;
}
//lcd写入数据函数
void LCD_write_data(unsigned char data)
{
    RS_SET;
    RW_CLR;
    EN_SET;
    DataPort = data;                //数据写入端口
    delay_ms(5);
    EN_CLR;
}
//清屏
void LCD_clear(void)
{
    LCD_write_com(0x01);            //清屏幕显示
    delay_ms(5);
}
//字符串显示函数
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s)
{

    if (y == 0)
    {
        LCD_write_com(0x80 + x);        //第一行显示
    }
    else
    {
        LCD_write_com(0xC0 + x);        //第二行显示
    }

    while (*s)
    {
        LCD_write_data( *s);
        s ++;
    }
}
void LCD_write_single_char(unsigned char x,unsigned char y,unsigned char data)
{

    if (y == 0)
    {
        LCD_write_com(0x80 + x);        //第一行显示
    }
    else
    {
        LCD_write_com(0xC0 + x);        //第二行显示
    }

    LCD_write_data( data);
}
//单字符显示函数
void LCD_write_num(unsigned char x,unsigned char y,unsigned int data)
{

    if (y == 0)
    {
        LCD_write_com(0x80 + x);        //第一行显示
    }
    else
    {
        LCD_write_com(0xC0 + x);        //第二行显示
    }

    LCD_write_data( data+48);
}
//显示屏初始化函数
void LCD_init(void)
{
    LCD_write_com(0x38);        //显示模式设置
    delay_ms(5);
    LCD_write_com(0x08);        //显示关闭
    delay_ms(5);
    LCD_write_com(0x01);        //显示清屏
    delay_ms(5);
    LCD_write_com(0x06);        //显示光标移动设置
    delay_ms(5);
    LCD_write_com(0x0C);        //显示开及光标设置
    delay_ms(5);
}


