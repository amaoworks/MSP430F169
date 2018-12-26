/*
 * I2C.c
 *
 *  Created on: 2018��12��26��
 *      Author: Brown
 */
#include "I2C.h"

void i2c_write(unsigned char naddr,unsigned char data)
{
    I2CNDAT =0x02;
    U0CTL |=MST;
    I2CTCTL |=I2CSTT +I2CSTP + I2CTRX;
    while((I2CIFG &TXRDYIFG)==0);   //�ȴ�����׼����
    I2CDRB =naddr;                  //���͵�ַ
    while((I2CIFG &TXRDYIFG)==0);
    delay_ms(9);
    I2CDRB =data;                   // ��������
    while((I2CTCTL &I2CSTP)==0x02); //�ȴ�ֹͣ�ź�
}

unsigned char i2c_read(unsigned char naddr){
    I2CNDAT =0x01;
    unsigned char return_data;
    U0CTL |=MST;                        //����ģʽ
    I2CTCTL |= I2CSTT +I2CSTP +I2CTRX;  //���ͳ�ʼ����������ʼ�źţ�ֹͣ�źţ���ֹ�ź�
    while((I2CIFG&TXRDYIFG)==0);        //�ȴ�����׼����
    I2CDRB =naddr;
    delay_ms(9);
    U0CTL |=MST;                        //����ģʽ
    I2CIFG &=~ARDYIFG ;
    I2CTCTL &=~I2CTRX;                  //����ģʽ
    I2CTCTL =I2CSTT +I2CSTP;            //��ʼ�źź�ֹͣ�ź�
    while((I2CIFG&RXRDYIFG)==0);        //�ȴ�����׼����
    return_data =I2CDRB;
    delay_ms(9);
    while((I2CTCTL &I2CSTP)==0x02);     //�ȴ�ֹͣ�ź�
    return return_data;
}
