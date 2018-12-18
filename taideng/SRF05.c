/*
 * SRF05.c
 *
 *  Created on: 2018年12月17日
 *      Author: hp
 */
#include"SRF05.h"

extern unsigned int TA_Overflow_Cnt;         //TA溢出次数存放变量
extern unsigned long int Period;             //脉宽存放结果变量
extern unsigned long int S;                  //计算结果单位为毫米
extern unsigned int  RiseCapVal;               //上升沿时刻捕获值存放变量
extern unsigned char Edge;                 //当前触发沿 初始值为上升沿
extern unsigned char temp,A1,A2,A3,A4,open;            //定义的变量,显示数据处理
extern char   Temp_Value[7];

/********************************************************************
    初始化定时器A函数
********************************************************************/
void init_timerA()
{
  TACTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3;//SMCLK,连续计数，中断允许，计数器清零
  TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//捕获模式，上升沿捕获，CCI1A输入，同步捕获，中断允许
}

/********************************************************************
    SRF05模块控制口初始化函数
********************************************************************/
void SRF05_IOinit()
{
  P1DIR |= BIT4;                  //P1.4输出
  P1DIR &=~ BIT2;                 //P1.2输入
  P1SEL =  BIT2;                  //P1.2第二功能，捕获输入

  P1OUT &=~BIT4;                  //清零P1.4控制端
  delay_ms(1000);
  //P1端口外部中断
//   P1DIR|=0X00;  //P1.0、P1.1、P1.2、P1.3为输入模式
//   P1IE|=0X0F;   //P1.0、P1.1、P1.2、P1.3允许中断
//   P1IES|=0x0F;  //P1.0、P1.1、P1.2、P1.3为下降沿触发
}

//*************************************************************************
//      距离值处理函数
//*************************************************************************
void Data_do(uint temp_d)
{
  uint temp_1,temp_2;
  A1=temp_d/1000;                       //分出千，百，十，和个位
  temp_1=temp_d%1000;
  A2=temp_1/100;
  temp_2=temp_1%100;
  A3=temp_2/10;
  A4=temp_2%10;

  Temp_Value[0]=A1+0x30;
  Temp_Value[1]='.';
  Temp_Value[2]=A2+0x30;
  Temp_Value[3]=A3+0x30;
  Temp_Value[4]=A3+0x30;
  Temp_Value[5]='m';
  Temp_Value[6]=' ';
}

void Auto(){
    if(S < 1000){
        open = 1;
    }else{
        open = 0;
    }
}

/********************************************************************
                      定时器A服务程序
********************************************************************/
//定时器A服务程序
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{

  switch(TAIV)
  {
    case 2 :if(Edge==RISE)
              {
                RiseCapVal = TACCR1;
                TACCTL1 |= CAP+CM_2+CCIS_0+SCS+CCIE;//改为下降沿捕获
                //TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//改为上升沿捕获
                Edge = FALL;//下降沿捕获标志
              }
             else
              {

                _DINT();

                Period = TACCR1-RiseCapVal;
                S=(Period*17)/100;
                TACCR1 = 0;
                TACCTL1|= CAP+CM_1+CCIS_0+SCS+CCIE;//改为上升沿捕获
                Edge = RISE;//上升沿捕获标志
                _EINT();
              }
             break;
    case 4 : break;
    case 10: TA_Overflow_Cnt++;
             break;
  }
}
