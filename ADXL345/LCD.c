/*
 * LCD.c
 *
 *  Created on: 2018年12月2日
 *      Author: Brown
 */
#include "LCD.h"

void init_LCD1602_IO(void) // 设置P3.1,P3.2,P3.3 端口为输出模式
{
    P3DIR|=BIT1+BIT2+BIT3;
}
void write_data(uchar data)//RS_H,RW_L,D0~D7 数据， E 高脉冲
{
    RS_L;
    RW_H;
    E_L;
    RS_H;
    RW_L;
    Data_DIR|=0xff;
    Data_OUT=data;
    delay_us(1);
    E_H;
    delay_us(1);
    E_L;
    delay_us(1);
    RW_H;
    RS_L;
}
void write_commond(uchar commond)//RS_L,RW_L,D0~D7 指令， E 高脉冲
{
    RS_H;
    RW_H;
    E_L;
    RS_L;
    RW_L;
    Data_DIR|=0xff;
    Data_OUT=commond;
    delay_us(1);
    E_H;
    delay_us(1);
    E_L;
    delay_us(1);
    RW_H;
    RS_H;
}
uchar read_sta(void)//RS_L,RW_H,E_H;
{
    uchar sta;
    RS_H;
    RW_L;
    E_L;
    RS_L;
    RW_H;
    delay_us(1);
    E_H;
    Data_DIR&=~0xff;
    sta=Data_IN;
    delay_us(1);
    E_L;
    delay_us(1);
    RW_L;
    RS_H;
    return(sta);
}
void read_busy(void)
{
    L1: busy=read_sta();
    if(busy&0x80)
    {
        goto L1;
    }
    else;
}
void init_LCD1602(void)
{
    delay_ms(15);
    write_commond(0x38);
    delay_ms(5);
    write_commond(0x38);
    delay_ms(5);
    write_commond(0x38);
    write_commond(0x38);
    read_busy();
    write_commond(0x08);
    read_busy();
    write_commond(0x01);
    read_busy();
    write_commond(0x06);
    read_busy();
    write_commond(0x0c);
    read_busy();
}
void disp(uchar location,uchar data)
{
    write_commond(0x80+location);
    read_busy();
    write_data(data);
    read_busy();
}
void DisplayOneChar(uchar X,uchar Y ,uchar DData)
{
    Y&=1;
    X&=15;
    if(Y)X|=0x40;
    X|=0x80;
    write_commond(X);
    write_data(DData);
}
