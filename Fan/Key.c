/*
 * Key.c
 *
 *  Created on: 2018��12��4��
 *      Author: Brown
 */
//#include "Key.h"

//extern unsigned char statu;
//extern unsigned char key;

//void Key_PortInit(){
//    P1DIR|=0X00;        //P1.0��P1.1��P1.2��P1.3Ϊ����ģʽ
//    P1IE |=0X0F;        //P1.0��P1.1��P1.2��P1.3�����ж�
//    P1IES|=0x0F;        //P1.0��P1.1��P1.2��P1.3Ϊ�½��ش���
//}

//void Key_PortInit()
//{
//  P1SEL = 0x00;                   //P1��ͨIO����
//  P1DIR = 0xF0;                   //P10~P13����ģʽ���ⲿ��·�ѽ���������
//  P6SEL = 0x00;                   //P6����ͨIO����
//  P6DIR = 0xFF;                   //P6�����ģʽ
//}
//
//uchar Key_Scan(void)
//{
//  uchar key_check;
//  uchar key_checkin;
//  key_checkin=KeyPort;              //��ȡIO��״̬���ж��Ƿ��м�����
//  key_checkin&= 0x0F;               //��ȡIO��״̬���ж��Ƿ��м�����
//  if(key_checkin!=0x0F)             //IO��ֵ�����仯���ʾ�м�����
//    {
//      delay_ms(20);                     //������������ʱ20MS
//      key_checkin=KeyPort;
//      if(key_checkin!=0x1F)
//        {
//          key_check=KeyPort;
//          switch (key_check & 0x0F)
//            {
//              case 0x0E:key=1;statu++;break;
//              case 0x0D:key=2;break;
//              case 0x0B:key=3;break;
//              case 0x07:key=4;break;
//            }
//
//        }
//
//   }
//  else
//   {
//     key=0xFF;
//   }
//  return key;
//}
