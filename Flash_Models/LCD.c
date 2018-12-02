/*
 * LCD.c
 *
 *  Created on: 2018��11��18��
 *      Author: myy12
 */
#include "LCD.h"

void write_com(uchar com){          //1602д����
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

void write_date(uchar date){        //1602д����
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

void init(){            //���￴���ϵ�P46~P48
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


//���̲���

//*************************************************************************
//  ��ʼ��IO���ӳ���
//*************************************************************************
void Port_In()
{

    P1SEL = 0x00;                   //P1��ͨIO����
    P1DIR = 0xF0;                   //P10~P13����ģʽ���ⲿ��·�ѽ���������
    P6SEL = 0x00;                   //P6����ͨIO����
    P6DIR = 0xFF;                   //P6�����ģʽ
}

//**********************************************************************
//  ����ɨ���ӳ��򣬲������ɨ��ķ�ʽ
//**********************************************************************

uchar Key_Scan(void)
{
    uchar key_check;
    uchar key_checkin;
    key_checkin=KeyPort;              //��ȡIO��״̬���ж��Ƿ��м�����
    key_checkin&= 0x0F;               //��ȡIO��״̬���ж��Ƿ��м�����
    if(key_checkin!=0x0F)             //IO��ֵ�����仯���ʾ�м�����
    {
        delay_ms(20);                     //������������ʱ20MS
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

//д��

/*��ʾ
void Watch(){
    write_com(0x80);
    display(b);
    write_com(0x80 + 0x40);
    write_date(c);
}*/
