/*
 * LCD.c
 *
 *  Created on: 2018��12��13��
 *      Author: Brown
 */
#include "LCD.h"

extern unsigned int  TA_Overflow_Cnt;
extern unsigned long Period;
extern unsigned long S;
extern unsigned int  distance;
extern unsigned int  RiseCapVal;
extern unsigned char Edge;
extern unsigned char disbuff[4];
extern unsigned char temp,A1,A2,A3,A4,A5,A6,A7,A8;

void Write_com(uchar com){          //1602д����
    P5DIR|=(BIT5+BIT6+BIT7);        //��P5.5 P5.6 P5.7����Ϊ���
    dataout;
    clr_RS;                         //��RSΪ0 д������
    clr_RW;                         //��RWΪ0
    dataport = com;
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

void Write_data(uchar date){        //1602д����
    P5DIR|=(BIT5+BIT6+BIT7);
    dataout;
    set_RS;                         //д������
    clr_RW;
    dataport = date;
    delay_ms(5);
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

void LCD_init(){            //���￴���ϵ�P46~P48
    Write_com(0x38);
    delay_ms(5);
    Write_com(0x0c);
    delay_ms(5);
    Write_com(0x06);
    delay_ms(5);
    Write_com(0x01);
}

void LCD_Portinit(){           //�˿ڳ�ʼ��
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|=BIT5 + BIT6 + BIT7;
}

void Display_Num(unsigned char x,unsigned char y,unsigned long num){        //������ʾ
    uchar k;
    uchar dis_flag = 0;
    uchar table[7];
    if (y == 0)
    {
        Write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        Write_com(0xC0 + x);        //�ڶ�����ʾ
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

//��ʾ�������ʾ
void LCD_clear(void)
{
    Write_com(0x01);            //����Ļ��ʾ
    delay_ms(5);
}

//��ʾ���ַ���д�뺯��
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s)
{

    if (y == 0)
    {
        Write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        Write_com(0xC0 + x);        //�ڶ�����ʾ
    }

    while (*s)
    {
        Write_data( *s);
        s ++;
    }
}

//��ʾ�����ַ�д�뺯��
void LCD_write_char(unsigned char x,unsigned char y,unsigned char data)
{

    if (y == 0)
    {
        Write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        Write_com(0xC0 + x);        //�ڶ�����ʾ
    }

    Write_data( data);
}

void LCD_Desk(){
    LCD_write_str(0x00,0,"JuLi:");
    LCD_write_str(0x00,1,"Safe:");
}

void Data_do(uint temp_d)
{
  uint temp_1,temp_2;
  A1=temp_d/1000;                       //�ֳ�ǧ���٣�ʮ���͸�λ
  temp_1=temp_d%1000;
  A2=temp_1/100;
  temp_2=temp_1%100;
  A3=temp_2/10;
  A4=temp_2%10;
}

void LCD_DisplayDistance(long distance)
{
  Data_do(distance);        //��ʾλ����ȡ
  LCD_write_char(0x09,0,0x30+A1);
  LCD_write_char(0x0a,0,0x30+A2);
  LCD_write_char(0x0b,0,0x30+A3);
  LCD_write_char(0x0c,0,'.');
  LCD_write_char(0x0d,0,0X30+A4);
  LCD_write_char(0x0e,0,'c');
  LCD_write_char(0x0f,0,'m');
}

void DataS_do(uint temp_d)
{
  uint temp_1,temp_2;
  A5=temp_d/1000;                       //�ֳ�ǧ���٣�ʮ���͸�λ
  temp_1=temp_d%1000;
  A6=temp_1/100;
  temp_2=temp_1%100;
  A7=temp_2/10;
  A8=temp_2%10;
}

void LCD_DisplaySafe(long distance)
{
  DataS_do(distance);        //��ʾλ����ȡ
  LCD_write_char(0x09,1,0x30+A5);
  LCD_write_char(0x0a,1,0x30+A6);
  LCD_write_char(0x0b,1,0x30+A7);
  LCD_write_char(0x0c,1,'.');
  LCD_write_char(0x0d,1,0X30+A8);
  LCD_write_char(0x0e,1,'c');
  LCD_write_char(0x0f,1,'m');
}
