/*
 * BH1750.c
 *
 *  Created on: 2018年12月5日
 *      Author: Brown
 */
#include "BH1750.h"

extern unsigned char ge,shi,bai,qian,wan;  //显示变量
extern int dis_data;
extern unsigned char BUF[8];

void LED_init(){
    LEDDIR = 0xff;
    LED = 0xFF;
}

void I2C_init(){
    SDA_OUT;
    SDA_H;
    SCL_OUT;
    SCL_H;
}

void Delay5us(void)
{
    uchar i;

    for(i = 0;i < 15;i++);
    _NOP();
}
void Delay5ms(void)
{
    uint i=40000;
    while (i != 0)
    {
        i--;
    }
}

void delay(uint x)
{
    uchar i;
    while(x--)for(i=0;i<125;i++);
}

void BH1750_Start()
{
    SDA_H;                    //拉高数据线
    SCL_H;                    //拉高时钟线
    Delay5us();               //延时
    SDA_L;                    //产生下降沿
    Delay5us();               //延时
    SCL_L;                    //拉低时钟线
}
void BH1750_Stop()
{
    SDA_L;                    //拉低数据线
    SCL_H;                    //拉高时钟线
    Delay5us();                 //延时
    SDA_H;                    //产生上升沿
    Delay5us();                 //延时
}

void BH1750_SendACK(void)
{
    SDA_L;                  //写应答信号
    _NOP();_NOP();
    SCL_H;                    //拉高时钟线
    Delay5us();                  //延时
    SCL_L;                    //拉低时钟线
    _NOP();_NOP();
    SDA_H;
    Delay5us();                 //延时
}

void mnack(void)
{
    SDA_H;
    _NOP(); _NOP();
    SCL_H;
    Delay5us();
    SCL_L;
    _NOP(); _NOP();
    SDA_L;
    Delay5us();
}

uchar BH1750_RecvACK()
{
    uchar ack;

    SDA_H;
    _NOP(); _NOP();
    SCL_H;
    _NOP(); _NOP();
    SDA_IN;
    _NOP(); _NOP();
    ack = SDA_VAL;   //读入SDA数值
    SCL_L;
    Delay5us();
    SDA_OUT;
    if(ack)    return 0;
    else            return  1;
}

void write1(void)
{
    SDA_H;
    //Delay5us();
    SCL_H;
    Delay5us();
    SCL_L;
    Delay5us();
}

void write0(void)
{
    SDA_L;
    SCL_H;
    Delay5us();
    SCL_L;
    Delay5us();
}
void BH1750_SendByte(unsigned char dat)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {        //8位计数器
        if(dat&0x80)
            write1();
        else
            write0();
        dat <<= 1;              //移出数据的最高位
    }
    BH1750_RecvACK();
}

unsigned char BH1750_RecvByte()
{
    unsigned char i;
    unsigned char dat = 0,flag;

    SDA_H;                     //使能内部上拉,准备读取数据,
    for (i = 0; i < 8; i++)
    {       //8位计数器
        //SDA_H;
        //Delay5us();
        SCL_H;
        SDA_IN;
        Delay5us();
        flag=SDA_VAL;
        dat <<= 1;
        if(flag)
            dat|=0x01;
        SDA_OUT;
        SCL_L;
        Delay5us();
    }
    return dat;
}

void Single_Write_BH1750(unsigned char REG_Address)
{
    BH1750_Start();                  //起始信号
    BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
    BH1750_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页
    //  BH1750_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页
    BH1750_Stop();                   //发送停止信号
}
void Init_BH1750()
{
    Single_Write_BH1750(0x01);
}

void Multiple_Read_BH1750(void)
{
    unsigned char i;
    BH1750_Start();                          //起始信号
    BH1750_SendByte(0x47);         //发送设备地址+读信号

    for (i = 0; i < 3; i++) {                      //连续读取6个地址数据，存储中BUF
        BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 3) {


            mnack();                //最后一个数据需要回NOACK
        }
        else {

            BH1750_SendACK();                //回应ACK
        }
    }
    BH1750_Stop();                          //停止信号
    Delay5ms();
}

void conversion(unsigned int temp_data)   //数据转换出 个，十，百，千，万
{
    wan = temp_data / 10000 + 0x30;
    temp_data = temp_data % 10000;  //取余运算

    qian = temp_data / 1000 + 0x30;
    temp_data = temp_data % 1000;  //取余运算

    bai = temp_data / 100 + 0x30;
    temp_data = temp_data % 100;  //取余运算

    shi = temp_data / 10 + 0x30;
    temp_data = temp_data % 10;   //取余运算

    ge = temp_data + 0x30;
}
