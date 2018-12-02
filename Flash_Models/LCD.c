/*
 * LCD.c
 *
 *  Created on: 2018年11月18日
 *      Author: myy12
 */
#include "LCD.h"

void write_com(uchar com){          //1602写命令
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

void write_date(uchar date){        //1602写数据
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

void init(){            //这里看书上的P46~P48
    write_com(0x38);
    delay_ms(5);
    write_com(0x0c);
    delay_ms(5);
    write_com(0x06);
    delay_ms(5);
    write_com(0x01);
}

void port_init(){           //端口初始化
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|=BIT5 + BIT6 + BIT7;
}

void display(unsigned long int num){        //数字显示
    uchar k;
    uchar dis_flag = 0;
    uchar table[7];
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
        write_date(table[k]);
        delay_ms(5);
    }
}


//键盘测试

//*************************************************************************
//  初始化IO口子程序
//*************************************************************************
void Port_In()
{

    P1SEL = 0x00;                   //P1普通IO功能
    P1DIR = 0xF0;                   //P10~P13输入模式，外部电路已接上拉电阻
    P6SEL = 0x00;                   //P6口普通IO功能
    P6DIR = 0xFF;                   //P6口输出模式
}

//**********************************************************************
//  键盘扫描子程序，采用逐键扫描的方式
//**********************************************************************

uchar Key_Scan(void)
{
    uchar key_check;
    uchar key_checkin;
    key_checkin=KeyPort;              //读取IO口状态，判断是否有键按下
    key_checkin&= 0x0F;               //读取IO口状态，判断是否有键按下
    if(key_checkin!=0x0F)             //IO口值发生变化则表示有键按下
    {
        delay_ms(20);                     //键盘消抖，延时20MS
        key_checkin=KeyPort;
        if(key_checkin!=0x1F)
        {
            key_check=KeyPort;
            switch (key_check & 0x0F)
            {
            case 0x0E:key=1;break;
            case 0x0D:key=2;break;
            case 0x0B:key=3;break;
            case 0x07:key=4;break;
            }

        }

    }
    else
    {
        key=0xFF;
    }
    return key;
}

//写入

/*显示
void Watch(){
    write_com(0x80);
    display(b);
    write_com(0x80 + 0x40);
    write_date(c);
}*/
