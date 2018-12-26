/*
 * MPU6050.h
 *
 *  Created on: 2018��12��26��
 *      Author: Brown
 */
#include "I2C.h"
#ifndef MPU6050_H_
#define MPU6050_H_

#define SMPLRT_DIV      0x19    //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define CONFIG          0x1A    //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define GYRO_CONFIG     0x1B    //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define ACCEL_CONFIG    0x1C    //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define ACCEL_XOUT_H    0x3B    //X��߰�λ
#define ACCEL_XOUT_L    0x3C    //X��Ͱ�λ
#define ACCEL_YOUT_H    0x3D    //Y��߰�λ
#define ACCEL_YOUT_L    0x3E    //Y��Ͱ�λ
#define ACCEL_ZOUT_H    0x3F    //Z��߰�λ
#define ACCEL_ZOUT_L    0x40    //Z��Ͱ�λ
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48
#define PWR_MGMT_1      0x6B    //��Դ��������ֵ��0x00(��������)
#define WHO_AM_I        0x75    //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define SlaveAddress    0xD0    //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

void MPU6050_Init();
void MPU6050_Portinit();

#endif /* MPU6050_H_ */
