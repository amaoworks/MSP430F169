/*
 * LCD.c
 *
 *  Created on: 2018��12��5��
 *      Author: Brown
 */
#include "LCD.h"

extern unsigned char ge,shi,bai,qian,wan;  //��ʾ����
extern int dis_data;
extern unsigned char BUF[8];

void write_com(uchar com){          //1602д����
    P5DIR|=(BIT5+BIT6+BIT7);        //��P5.5 P5.6 P5.7����Ϊ���
    dataout;
    clr_RS;                         //��RSΪ0 д������
    clr_RW;                         //��RWΪ0
    DataPort = com;
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

void write_date(uchar date){        //1602д����
    P5DIR|=(BIT5+BIT6+BIT7);
    dataout;
    set_RS;                         //д������
    clr_RW;
    DataPort = date;
    delay_ms(5);
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

void DisplayOneChar(unsigned char x, unsigned char date){
    write_com(0x80 + x);
    write_date(date);
}

void init(){
    write_com(0x38);
    delay_ms(5);
    write_com(0x0c);
    delay_ms(5);
    write_com(0x06);
    delay_ms(5);
    write_com(0x01);
}

void port_init(){           //�˿ڳ�ʼ��
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|=BIT5 + BIT6 + BIT7;
}

void display(unsigned long int num){        //������ʾ
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

void inmaindispaly()
{
    uint temp;
    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//�ϳ�����

    temp=dis_data;

    conversion(temp);         //�������ݺ���ʾ
    DisplayOneChar(0x0,'L');
    DisplayOneChar(0x01,'i');
    DisplayOneChar(0x02,'g');
    DisplayOneChar(0x03,'h');
    DisplayOneChar(0x04,'t');
    DisplayOneChar(0x05,':');

    DisplayOneChar(0x07,wan); //��ʾ����
    DisplayOneChar(0x08,qian);
    DisplayOneChar(0x09,bai);
    DisplayOneChar(0x0a,shi);
    DisplayOneChar(0x0b,ge);

    DisplayOneChar(0x0c,'l'); ////��ʾ����λ
    DisplayOneChar(0x0d,'x');
}
