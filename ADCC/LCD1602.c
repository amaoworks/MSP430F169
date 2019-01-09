/*
 * LCD1602.c
 *
 *  Created on: 2018��11��29��
 *      Author: liu
 */



/*
 * LCD1602.c
 *
 *  Created on: 2018��11��3��
 *      Author: liu
 */
#include "LCD1602.h"
void clk_init(){
    uchar i;
    BCSCTL1&=~XT2OFF;//��XT2������
    BCSCTL2 |=SELS+SELM1 ;//SMCLK8��Ƶ
    do
    {
        IFG1 &= ~OFIFG;//����񵴴����־
        for(i=0;i<0xff;i++) _NOP();

    }
    while((IFG1 & OFIFG)!=0);
    IFG1&=~OFIFG;//����жϱ�־
}
//�˿ڳ�ʼ��
void LCD_Port_init()
{

        P4SEL = 0x00;
        P4DIR = 0xFF;                   //���ݿ����ģʽ
        P5SEL = 0x00;
        P5DIR|= BIT5 + BIT6 + BIT7;     //���ƿ�����Ϊ���ģʽ
}
//д������
void LCD_write_com(unsigned char com)
{
    RS_CLR;
    RW_CLR;
    EN_SET;
    DataPort = com;                 //����д��˿�
    delay_ms(5) ;
    EN_CLR;
}
//lcdд�����ݺ���
void LCD_write_data(unsigned char data)
{
    RS_SET;
    RW_CLR;
    EN_SET;
    DataPort = data;                //����д��˿�
    delay_ms(5);
    EN_CLR;
}
//����
void LCD_clear(void)
{
    LCD_write_com(0x01);            //����Ļ��ʾ
    delay_ms(5);
}
//�ַ�����ʾ����
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s)
{

    if (y == 0)
    {
        LCD_write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        LCD_write_com(0xC0 + x);        //�ڶ�����ʾ
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
        LCD_write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        LCD_write_com(0xC0 + x);        //�ڶ�����ʾ
    }

    LCD_write_data( data);
}
//���ַ���ʾ����
void LCD_write_num(unsigned char x,unsigned char y,unsigned int data)
{

    if (y == 0)
    {
        LCD_write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        LCD_write_com(0xC0 + x);        //�ڶ�����ʾ
    }

    LCD_write_data( data+48);
}
//��ʾ����ʼ������
void LCD_init(void)
{
    LCD_write_com(0x38);        //��ʾģʽ����
    delay_ms(5);
    LCD_write_com(0x08);        //��ʾ�ر�
    delay_ms(5);
    LCD_write_com(0x01);        //��ʾ����
    delay_ms(5);
    LCD_write_com(0x06);        //��ʾ����ƶ�����
    delay_ms(5);
    LCD_write_com(0x0C);        //��ʾ�����������
    delay_ms(5);
}


