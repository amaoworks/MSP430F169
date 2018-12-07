/*
 * BH1750.c
 *
 *  Created on: 2018��12��5��
 *      Author: Brown
 */
#include "BH1750.h"

extern unsigned char ge,shi,bai,qian,wan;  //��ʾ����
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
    SDA_H;                    //����������
    SCL_H;                    //����ʱ����
    Delay5us();               //��ʱ
    SDA_L;                    //�����½���
    Delay5us();               //��ʱ
    SCL_L;                    //����ʱ����
}
void BH1750_Stop()
{
    SDA_L;                    //����������
    SCL_H;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA_H;                    //����������
    Delay5us();                 //��ʱ
}

void BH1750_SendACK(void)
{
    SDA_L;                  //дӦ���ź�
    _NOP();_NOP();
    SCL_H;                    //����ʱ����
    Delay5us();                  //��ʱ
    SCL_L;                    //����ʱ����
    _NOP();_NOP();
    SDA_H;
    Delay5us();                 //��ʱ
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
    ack = SDA_VAL;   //����SDA��ֵ
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
    {        //8λ������
        if(dat&0x80)
            write1();
        else
            write0();
        dat <<= 1;              //�Ƴ����ݵ����λ
    }
    BH1750_RecvACK();
}

unsigned char BH1750_RecvByte()
{
    unsigned char i;
    unsigned char dat = 0,flag;

    SDA_H;                     //ʹ���ڲ�����,׼����ȡ����,
    for (i = 0; i < 8; i++)
    {       //8λ������
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
    BH1750_Start();                  //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ
    //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ
    BH1750_Stop();                   //����ֹͣ�ź�
}
void Init_BH1750()
{
    Single_Write_BH1750(0x01);
}

void Multiple_Read_BH1750(void)
{
    unsigned char i;
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(0x47);         //�����豸��ַ+���ź�

    for (i = 0; i < 3; i++) {                      //������ȡ6����ַ���ݣ��洢��BUF
        BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 3) {


            mnack();                //���һ��������Ҫ��NOACK
        }
        else {

            BH1750_SendACK();                //��ӦACK
        }
    }
    BH1750_Stop();                          //ֹͣ�ź�
    Delay5ms();
}

void conversion(unsigned int temp_data)   //����ת���� ����ʮ���٣�ǧ����
{
    wan = temp_data / 10000 + 0x30;
    temp_data = temp_data % 10000;  //ȡ������

    qian = temp_data / 1000 + 0x30;
    temp_data = temp_data % 1000;  //ȡ������

    bai = temp_data / 100 + 0x30;
    temp_data = temp_data % 100;  //ȡ������

    shi = temp_data / 10 + 0x30;
    temp_data = temp_data % 10;   //ȡ������

    ge = temp_data + 0x30;
}
