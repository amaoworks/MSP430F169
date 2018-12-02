#include <msp430x14x.h>
#include <math.h>
#include"LCD.h"

//#define uint unsigned int
//#define uchar unsigned char
#define SDA_L P3OUT&=~BIT3//EEPROM �����ߵ�
#define SDA_H P3OUT|=BIT3// �����߸�
#define SDA_OUT P3DIR|=BIT3// ����������Ϊ���״̬
#define SDA_IN P3DIR&=~BIT3// ����������Ϊ����״̬
#define SDA_DATE P3IN & BIT3// ����SDA �ߵ�״̬
#define SCL_L P3OUT&=~BIT2// ����ʱ���ߵ�
#define SCL_H P3OUT|=BIT2// ʱ�Ӹ�
#define SCL_OUT P3DIR|=BIT2// ����ʱ����Ϊ���״̬
#define TRUE 1
#define FALSE 0
#define SlaveAddress 0xA6
char BUF[8];
uchar devid;
uchar err;
int dis_data;
uchar ge,shi,bai,qian,wan; //��ʾ����
/*******************************************
�������ƣ� delay
���ܣ���ʱԼ15us ��ʱ��
��������
����ֵ����
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
�������ƣ� start
���ܣ����IIC ����ʼ��������
��������
����ֵ����
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
�������ƣ� stop
���ܣ����IIC ����ֹ��������
��������
����ֵ����
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
�������ƣ� mack
���ܣ����IIC ������Ӧ�����
��������
����ֵ����
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
    �������ƣ� mnack
    ���ܣ����IIC ��������Ӧ�����
    ��������
    ����ֵ����
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
/* �ж�Ӧ����Ӧ���ӳ���*/
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
    �������ƣ� write1byte
    ���ܣ���IIC ���߷���һ���ֽڵ�����
    ������ wdata--���͵�����
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
�������ƣ� read1byte
���ܣ���IIC ���߶�ȡһ���ֽ�
��������
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
//****** ���ֽ�д��*******************************************
void Single_Write_ADXL345(uchar REG_Address,uchar REG_data)
{
    start(); //��ʼ�ź�
    write1byte(SlaveAddress); //�����豸��ַ+д�ź�
    cack();
    write1byte(REG_Address); //�ڲ��Ĵ�����ַ����ο�����pdf22 ҳ
    cack();
    write1byte(REG_data); //�ڲ��Ĵ������ݣ���ο�����pdf22 ҳ
    cack();
    stop(); //����ֹͣ�ź�
}
//******** ���ֽڶ�ȡ*****************************************
uchar Single_Read_ADXL345(uchar REG_Address)
{
    uchar REG_data;
    start(); //��ʼ�ź�
    write1byte(SlaveAddress); //�����豸��ַ+д�ź�
    cack();
    write1byte(REG_Address); //���ʹ洢��Ԫ��ַ����0 ��ʼ
    cack();
    start(); //��ʼ�ź�
    write1byte(SlaveAddress+1); //�����豸��ַ+���ź�
    cack();
    REG_data=read1byte(); //�����Ĵ�������
    mnack();
    stop(); //ֹͣ�ź�
    return REG_data;
}
//*********************************************************
//
//��������ADXL345 �ڲ����ٶ����ݣ���ַ��Χ0x32~0x37
//
//*********************************************************
void Multiple_read_ADXL345(void)
{
    uchar i;
    start(); //��ʼ�ź�
    write1byte(SlaveAddress); //�����豸��ַ+д�ź�
    cack();
    write1byte(0x32); //���ʹ洢��Ԫ��ַ����0x32 ��ʼ
    cack();
    start(); //��ʼ�ź�
    write1byte(SlaveAddress+1); //�����豸��ַ+���ź�
    cack();
    for (i=0; i<6; i++) //������ȡ6 ����ַ���ݣ��洢��BUF
    {
        BUF[i] = read1byte(); //BUF[0] �洢0x32 ��ַ�е�����
        if (i == 5)
        {
            mnack(); //���һ��������Ҫ��NOACK
        }
        else
        {
            mack(); //��ӦACK
        }
    }
    stop(); //ֹͣ�ź�
    delayus(100);
}
//��ʼ��ADXL345 ��������Ҫ��ο�pdf �����޸�************************
void Init_ADXL345()
{
    Single_Write_ADXL345(0x31,0x0B); //������Χ,����16g��13 λģʽ
    Single_Write_ADXL345(0x2C,0x08); //�����趨Ϊ12.5 �ο�pdf13 ҳ
    Single_Write_ADXL345(0x2D,0x08); //ѡ���Դģʽ�ο�pdf24 ҳ
    Single_Write_ADXL345(0x2E,0x80); //ʹ��DATA_READY �ж�
    Single_Write_ADXL345(0x1E,0x00); //X ƫ�������ݲ��Դ�������״̬д��pdf29 ҳ
    Single_Write_ADXL345(0x1F,0x00); //Y ƫ�������ݲ��Դ�������״̬д��pdf29 ҳ
    Single_Write_ADXL345(0x20,0x05); //Z ƫ�������ݲ��Դ�������״̬д��pdf29 ҳ
}
void conversion(int temp_data)
{
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000; //ȡ������
    qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000; //ȡ������
    bai=temp_data/100+0x30 ;
    temp_data=temp_data%100; //ȡ������
    shi=temp_data/10+0x30 ;
    temp_data=temp_data%10; //ȡ������
    ge=temp_data+0x30;
}
//***********************************************************************
//��ʾx ��
void display_x()
{
    int temp;
    dis_data=(BUF[1]<<8)+BUF[0]; //�ϳ�����
    if(dis_data<0){
        dis_data=-dis_data;
        DisplayOneChar(2,0,'-'); //��ʾ��������λ
    }
    else
        DisplayOneChar(2,0,' '); // ��ʾ�ո�
    temp=(int)(dis_data*3.9); //�������ݺ���ʾ,�鿼ADXL345 �������ŵ�4 ҳ
    conversion(temp); //ת������ʾ��Ҫ������
    DisplayOneChar(0,0,'X'); //��0 �У���0 ����ʾX
    DisplayOneChar(1,0,':');
    DisplayOneChar(3,0,qian);
    DisplayOneChar(4,0,'.');
    DisplayOneChar(5,0,bai);
    DisplayOneChar(6,0,shi);
    DisplayOneChar(7,0,'g');
}
//***********************************************************************
//��ʾy ��
void display_y()
{
    int temp;
    dis_data=(BUF[3]<<8)+BUF[2]; //�ϳ�����
    if(dis_data<0){
        dis_data=-dis_data;
        DisplayOneChar(2,1,'-'); //��ʾ��������λ
    }
    else
        DisplayOneChar(2,1,' '); // ��ʾ�ո�
    temp=(int)(dis_data*3.9); //�������ݺ���ʾ,�鿼ADXL345 �������ŵ�4 ҳ
    conversion(temp); //ת������ʾ��Ҫ������
    DisplayOneChar(0,1,'Y'); //��1 �У���0 ����ʾy
    DisplayOneChar(1,1,':');
    DisplayOneChar(3,1,qian);
    DisplayOneChar(4,1,'.');
    DisplayOneChar(5,1,bai);
    DisplayOneChar(6,1,shi);
    DisplayOneChar(7,1,'g');
}
//***********************************************************************
//��ʾz ��
void display_z()
{
    int temp;
    dis_data=(BUF[5]<<8)+BUF[4]; //�ϳ�����
    if(dis_data<0){
        dis_data=-dis_data;
        DisplayOneChar(10,1,'-'); //��ʾ������λ
    }
    else
        DisplayOneChar(10,1,' '); //��ʾ�ո�
    temp=(int)(dis_data*3.9); //�������ݺ���ʾ,�鿼ADXL345 �������ŵ�4 ҳ
    conversion(temp); //ת������ʾ��Ҫ������
    DisplayOneChar(9,1,'Z'); //��0 �У���10 ����ʾZ
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
    x=(BUF[1]<<8)+BUF[0]; //�ϳ�����
    if(x<0)
    { x=-x;}
    y=(BUF[3]<<8)+BUF[2]; //�ϳ�����
    if(y<0)
    {y=-y;}
    z=(BUF[5]<<8)+BUF[4]; //�ϳ�����
    if(z<0)
    {z=-z;}
    angle= (int)(atan2((double)x,(double)z) * (180 / 3.14159265)); // angle in degrees
    angle*=10;
    conversion(angle); //�������ݺ���ʾ
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
    devid=Single_Read_ADXL345(0X00);// ����������Ϊ0XE5, ��ʾ��ȷ
    while(1)
    {
        Multiple_read_ADXL345();
        display_x(); //--------- ��ʾX ��
        display_y(); //--------- ��ʾY ��
        display_z(); //--------- ��ʾZ ��
        display_Angle();
    }
}
