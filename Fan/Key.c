/*
 * Key.c
 *
 *  Created on: 2018年12月4日
 *      Author: Brown
 */
//#include "Key.h"

//extern unsigned char statu;
//extern unsigned char key;

//void Key_PortInit(){
//    P1DIR|=0X00;        //P1.0、P1.1、P1.2、P1.3为输入模式
//    P1IE |=0X0F;        //P1.0、P1.1、P1.2、P1.3允许中断
//    P1IES|=0x0F;        //P1.0、P1.1、P1.2、P1.3为下降沿触发
//}

//void Key_PortInit()
//{
//  P1SEL = 0x00;                   //P1普通IO功能
//  P1DIR = 0xF0;                   //P10~P13输入模式，外部电路已接上拉电阻
//  P6SEL = 0x00;                   //P6口普通IO功能
//  P6DIR = 0xFF;                   //P6口输出模式
//}
//
//uchar Key_Scan(void)
//{
//  uchar key_check;
//  uchar key_checkin;
//  key_checkin=KeyPort;              //读取IO口状态，判断是否有键按下
//  key_checkin&= 0x0F;               //读取IO口状态，判断是否有键按下
//  if(key_checkin!=0x0F)             //IO口值发生变化则表示有键按下
//    {
//      delay_ms(20);                     //键盘消抖，延时20MS
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
