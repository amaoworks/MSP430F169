/*
 * MPU6050.c
 *
 *  Created on: 2018��12��26��
 *      Author: Brown
 */
#include "MPU6050.h"

void MPU6050_Init(){
    i2c_write(0x6b, 0x00);  //�������״̬
    i2c_write(0x19, 0x07);
    i2c_write(0x1a, 0x06);
    i2c_write(0x1b, 0x18);
    i2c_write(0x1c, 0x01);
}

void MPU6050_Portinit(){
    P3SEL |= 0x0A;
    U0CTL |=I2C +SYNC; //ѡ��I2cģʽ
    U0CTL &=~I2CEN;//��λ
    I2CTCTL =I2CSSEL1; //SMCLkʱ��
    I2CSA =(0xd0>>1);        //�ӻ���ַ
    U0CTL |=I2CEN;      //i2cʹ��
    P3DIR &=~0x0a;
}
