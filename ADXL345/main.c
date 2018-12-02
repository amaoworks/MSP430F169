#include <msp430x14x.h>
#include <math.h>
#include"LCD.h"

//#define uint unsigned int
//#define uchar unsigned char
#define SDA_L P3OUT&=~BIT3//EEPROM 数据线低
#define SDA_H P3OUT|=BIT3// 数据线高
#define SDA_OUT P3DIR|=BIT3// 设置数据线为输出状态
#define SDA_IN P3DIR&=~BIT3// 设置数据线为输入状态
#define SDA_DATE P3IN & BIT3// 读入SDA 线的状态
#define SCL_L P3OUT&=~BIT2// 串行时钟线低
#define SCL_H P3OUT|=BIT2// 时钟高
#define SCL_OUT P3DIR|=BIT2// 设置时钟线为输出状态
#define TRUE 1
#define FALSE 0
#define SlaveAddress 0xA6
char BUF[8];
uchar devid;
uchar err;
int dis_data;
uchar ge,shi,bai,qian,wan; //显示变量
/*******************************************
函数名称： delay
功能：延时约15us 的时间
参数：无
返回值：无
 ********************************************/
void delayus(unsigned int i)//delay 2.5us at 8M
{
    unsigned int ii;
    for(ii =i;ii > 0;ii--)
    {
        _NOP();_NOP();_NOP();_NOP();
        _NOP();_NOP();_NOP();_NOP();
        _NOP();_NOP();_NOP();_NOP();
        _NOP();_NOP();_NOP();_NOP();
    }
}
/*******************************************
函数名称： start
功能：完成IIC 的起始条件操作
参数：无
返回值：无
 ********************************************/
void start()
{
    SCL_OUT;
    SDA_OUT;
    SDA_H;
    SCL_H;
    delayus(2);
    SDA_L;
    delayus(2);
    SCL_L;
}
/*******************************************
函数名称： stop
功能：完成IIC 的终止条件操作
参数：无
返回值：无
 ********************************************/
void stop(void)
{
    SCL_OUT;
    SDA_OUT;
    SDA_L;
    SCL_H;
    delayus(2);
    SDA_H;
    delayus(2);
    SCL_L;
}
/*******************************************
函数名称： mack
功能：完成IIC 的主机应答操作
参数：无
返回值：无
 ********************************************/
void mack(void)
{
    SDA_OUT;
    SCL_OUT;
    SDA_L;
    SCL_H;
    delayus(2);
    SCL_L;
    SDA_H;
}
/*******************************************
    函数名称： mnack
    功能：完成IIC 的主机无应答操作
    参数：无
    返回值：无
 ********************************************/
void mnack(void)
{
    SDA_OUT;
    SCL_OUT;
    SDA_H;
    delayus(2);
    SCL_H;
    delayus(2);
    SCL_L;
    SDA_L;
}
/* 判断应答或非应答子程序*/
void cack()
{
    SDA_IN;
    SCL_OUT;
    SCL_L;
    delayus(1);
    SCL_H;
    err=0;
    if(SDA_DATE)err=1;
    SCL_L;
    SDA_OUT;
}
/*******************************************
    函数名称： write1byte
    功能：向IIC 总线发送一个字节的数据
    参数： wdata--发送的数据
 ********************************************/
void write1byte(uchar byte1)
{
    unsigned char i=8;
    SDA_OUT;
    SCL_OUT;
    while(i--)
    {
        delay_us(4);
        if(byte1 & 0x80)
        {SDA_H;}
        else
        {SDA_L;}
        delayus(4);
        SCL_H;
        delayus(4);
        SCL_L;
        byte1<<=1;
    }
}
/*******************************************
函数名称： read1byte
功能：从IIC 总线读取一个字节
参数：无
 ********************************************/
uchar read1byte(void)
{
    unsigned char i;
    unsigned char ddata=0;
    signed char temp;
    SCL_OUT;
    SDA_IN;
    for(i=0;i<8;i++)
    {
        ddata<<=1;
        delayus(4);
        SCL_H;
        temp=SDA_DATE;
        if(temp) ddata++;
        delayus(4);
        SCL_L;
    }
    return ddata;
}
//****** 单字节写入*******************************************
void Single_Write_ADXL345(uchar REG_Address,uchar REG_data)
{
    start(); //起始信号
    write1byte(SlaveAddress); //发送设备地址+写信号
    cack();
    write1byte(REG_Address); //内部寄存器地址，请参考中文pdf22 页
    cack();
    write1byte(REG_data); //内部寄存器数据，请参考中文pdf22 页
    cack();
    stop(); //发送停止信号
}
//******** 单字节读取*****************************************
uchar Single_Read_ADXL345(uchar REG_Address)
{
    uchar REG_data;
    start(); //起始信号
    write1byte(SlaveAddress); //发送设备地址+写信号
    cack();
    write1byte(REG_Address); //发送存储单元地址，从0 开始
    cack();
    start(); //起始信号
    write1byte(SlaveAddress+1); //发送设备地址+读信号
    cack();
    REG_data=read1byte(); //读出寄存器数据
    mnack();
    stop(); //停止信号
    return REG_data;
}
//*********************************************************
//
//连续读出ADXL345 内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_read_ADXL345(void)
{
    uchar i;
    start(); //起始信号
    write1byte(SlaveAddress); //发送设备地址+写信号
    cack();
    write1byte(0x32); //发送存储单元地址，从0x32 开始
    cack();
    start(); //起始信号
    write1byte(SlaveAddress+1); //发送设备地址+读信号
    cack();
    for (i=0; i<6; i++) //连续读取6 个地址数据，存储中BUF
    {
        BUF[i] = read1byte(); //BUF[0] 存储0x32 地址中的数据
        if (i == 5)
        {
            mnack(); //最后一个数据需要回NOACK
        }
        else
        {
            mack(); //回应ACK
        }
    }
    stop(); //停止信号
    delayus(100);
}
//初始化ADXL345 ，根据需要请参考pdf 进行修改************************
void Init_ADXL345()
{
    Single_Write_ADXL345(0x31,0x0B); //测量范围,正负16g，13 位模式
    Single_Write_ADXL345(0x2C,0x08); //速率设定为12.5 参考pdf13 页
    Single_Write_ADXL345(0x2D,0x08); //选择电源模式参考pdf24 页
    Single_Write_ADXL345(0x2E,0x80); //使能DATA_READY 中断
    Single_Write_ADXL345(0x1E,0x00); //X 偏移量根据测试传感器的状态写入pdf29 页
    Single_Write_ADXL345(0x1F,0x00); //Y 偏移量根据测试传感器的状态写入pdf29 页
    Single_Write_ADXL345(0x20,0x05); //Z 偏移量根据测试传感器的状态写入pdf29 页
}
void conversion(int temp_data)
{
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000; //取余运算
    qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000; //取余运算
    bai=temp_data/100+0x30 ;
    temp_data=temp_data%100; //取余运算
    shi=temp_data/10+0x30 ;
    temp_data=temp_data%10; //取余运算
    ge=temp_data+0x30;
}
//***********************************************************************
//显示x 轴
void display_x()
{
    int temp;
    dis_data=(BUF[1]<<8)+BUF[0]; //合成数据
    if(dis_data<0){
        dis_data=-dis_data;
        DisplayOneChar(2,0,'-'); //显示正负符号位
    }
    else
        DisplayOneChar(2,0,' '); // 显示空格
    temp=(int)(dis_data*3.9); //计算数据和显示,查考ADXL345 快速入门第4 页
    conversion(temp); //转换出显示需要的数据
    DisplayOneChar(0,0,'X'); //第0 行，第0 列显示X
    DisplayOneChar(1,0,':');
    DisplayOneChar(3,0,qian);
    DisplayOneChar(4,0,'.');
    DisplayOneChar(5,0,bai);
    DisplayOneChar(6,0,shi);
    DisplayOneChar(7,0,'g');
}
//***********************************************************************
//显示y 轴
void display_y()
{
    int temp;
    dis_data=(BUF[3]<<8)+BUF[2]; //合成数据
    if(dis_data<0){
        dis_data=-dis_data;
        DisplayOneChar(2,1,'-'); //显示正负符号位
    }
    else
        DisplayOneChar(2,1,' '); // 显示空格
    temp=(int)(dis_data*3.9); //计算数据和显示,查考ADXL345 快速入门第4 页
    conversion(temp); //转换出显示需要的数据
    DisplayOneChar(0,1,'Y'); //第1 行，第0 列显示y
    DisplayOneChar(1,1,':');
    DisplayOneChar(3,1,qian);
    DisplayOneChar(4,1,'.');
    DisplayOneChar(5,1,bai);
    DisplayOneChar(6,1,shi);
    DisplayOneChar(7,1,'g');
}
//***********************************************************************
//显示z 轴
void display_z()
{
    int temp;
    dis_data=(BUF[5]<<8)+BUF[4]; //合成数据
    if(dis_data<0){
        dis_data=-dis_data;
        DisplayOneChar(10,1,'-'); //显示负符号位
    }
    else
        DisplayOneChar(10,1,' '); //显示空格
    temp=(int)(dis_data*3.9); //计算数据和显示,查考ADXL345 快速入门第4 页
    conversion(temp); //转换出显示需要的数据
    DisplayOneChar(9,1,'Z'); //第0 行，第10 列显示Z
    DisplayOneChar(10,1,':');
    DisplayOneChar(11,1,qian);
    DisplayOneChar(12,1,'.');
    DisplayOneChar(13,1,bai);
    DisplayOneChar(14,1,shi);
    DisplayOneChar(15,1,'g');
}
void display_Angle(void)
{
    int x,y,z;
    int angle;
    x=(BUF[1]<<8)+BUF[0]; //合成数据
    if(x<0)
    { x=-x;}
    y=(BUF[3]<<8)+BUF[2]; //合成数据
    if(y<0)
    {y=-y;}
    z=(BUF[5]<<8)+BUF[4]; //合成数据
    if(z<0)
    {z=-z;}
    angle= (int)(atan2((double)x,(double)z) * (180 / 3.14159265)); // angle in degrees
    angle*=10;
    conversion(angle); //计算数据和显示
    DisplayOneChar(9,0,'A');
    DisplayOneChar(10,0,':');
    DisplayOneChar(11,0,qian);
    DisplayOneChar(12,0,bai);
    DisplayOneChar(13,0,shi);
    DisplayOneChar(14,0,'.');
    DisplayOneChar(15,0,ge);
}
void main(void)
{
    WDTCTL=WDTHOLD+WDTPW;
    init_LCD1602_IO();
    init_LCD1602();
    Init_ADXL345();
    devid=Single_Read_ADXL345(0X00);// 读出的数据为0XE5, 表示正确
    while(1)
    {
        Multiple_read_ADXL345();
        display_x(); //--------- 显示X 轴
        display_y(); //--------- 显示Y 轴
        display_z(); //--------- 显示Z 轴
        display_Angle();
    }
}
