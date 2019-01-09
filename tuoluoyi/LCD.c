/*
 * LCD.c
 *
 *  Created on: 2018年12月13日
 *      Author: Brown
 */
#include "LCD.h"

void Write_com(uchar com){          //1602写命令
    P5DIR|=(BIT5+BIT6+BIT7);        //将P5.5 P5.6 P5.7设置为输出
    dataout;
    clr_RS;                         //令RS为0 写入命令
    clr_RW;                         //令RW为0
    dataport = com;
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

void Write_data(uchar date){        //1602写数据
    P5DIR|=(BIT5+BIT6+BIT7);
    dataout;
    set_RS;                         //写入数据
    clr_RW;
    dataport = date;
    delay_ms(5);
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

void LCD_init(){            //这里看书上的P46~P48
    Write_com(0x38);
    delay_ms(5);
    Write_com(0x0c);
    delay_ms(5);
    Write_com(0x06);
    delay_ms(5);
    Write_com(0x01);
}

void LCD_Portinit(){           //端口初始化
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|= BIT5 + BIT6 + BIT7;
}

void Display_Num(unsigned char x,unsigned char y,unsigned long num){        //数字显示
    uchar k;
    uchar dis_flag = 0;
    uchar table[7];
    if (y == 0)
    {
        Write_com(0x80 + x);        //第一行显示
    }
    else
    {
        Write_com(0xC0 + x);        //第二行显示
    }
    if(num <= 9&num > 0){
        dis_flag = 1;
        table[0] = num % 10 + '0';
    }else if(num <= 99&num > 9){
        dis_flag = 2;
        table[0] = num/10 + '0';
        table[1] = num % 10 + '0';
    }else if(num <= 999&num > 99){
        dis_flag = 3;
        table[0] = num/100 + '0';
        table[1] = num/10 % 10 + '0';
        table[2] = num % 10 + '0';
    }else if(num <= 9999&num > 999){
        dis_flag = 4;
        table[0] = num/1000 + '0';
        table[1] = num/100 % 10 + '0';
        table[2] = num/10 % 10 + '0';
        table[3] = num % 10 + '0';
    }
    for(k = 0; k < dis_flag; k++){
        Write_data(table[k]);
        delay_ms(5);
    }
}

//显示屏清空显示
void LCD_clear(void)
{
    Write_com(0x01);            //清屏幕显示
    delay_ms(5);
}

//显示屏字符串写入函数
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s)
{

    if (y == 0)
    {
        Write_com(0x80 + x);        //第一行显示
    }
    else
    {
        Write_com(0xC0 + x);        //第二行显示
    }

    while (*s)
    {
        Write_data( *s);
        s ++;
    }
}

//显示屏单字符写入函数
void LCD_write_char(unsigned char x,unsigned char y,unsigned char data)
{

    if (y == 0)
    {
        Write_com(0x80 + x);        //第一行显示
    }
    else
    {
        Write_com(0xC0 + x);        //第二行显示
    }

    Write_data( data);
}
