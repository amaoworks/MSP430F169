#include<msp430f169.h>
#include"delay.h"
#include"type.h"
#include"Port.h"
#include"lcd_1602.h"
#include"DC_motor.h"
#include"inf.h"
#include"clock.h"


unsigned int count;              //TIMERB中断中变量
unsigned char infrared_a;                 //TIMERB中断中变量
unsigned char BIT;               //接收数据位数
unsigned char RECV_FLAG;         //接收到数据的标志位
unsigned char data[33];          //一位引导码+32位数据的数组
unsigned char ircode[4];         //存储两个用户码、一个数据码、一个数据码的反码
unsigned char VALUE;             //全局键值

uint a = 0;         //初始为50%占空比
uchar STATUS=0;


void main()
{
    WDTCTL = WDTPW + WDTHOLD;
    init_clk_1M();
    Init_PWM();

    init_1602_port();
    lcd1602_init();

    init_port2();                //初始化外部中断P2.0
    init_device();               //初始化红外接收设备和TIMERB

    while(1){
//        CCR1 = a;
        //P1SEL |= 0x04;  //P1.2第二功能 TA1 输出PWM
        //TACTL= TASSEL_2 + MC_1;  //定时器A时钟源为SMCLK，增计数模式
        infrared_decode();       //红外解码
        set_value(ircode[2]);    //配置各个按键的键值
        switch(VALUE){  //对键值进行处理
            case 1: start();        break;     //启动
            case 2: stop();         break;     //停止
            case 3: speed_add();    break;     //加速，每次增加1000个定时器计数值
            case 4: speed_sub();    break;     //减速，每次减少1000个定时器计数值
            default: break;
        }
        VALUE = 0;         //键值清除
        ircode[2]=0;       //ircode[2]全局数据码要清零，否则下次解码仍然会用到它的值。
        show_status(STATUS, a);
        P6DIR = 0xff;       //调试程序
        P6OUT = 0x0f;

    }
}

#pragma vector=PORT2_VECTOR      //端口P2中断
__interrupt void Port2_ISR(void)
{
    if(count>32)                 //第一次接收时判断count数量，>32为引导码，
    {
        BIT=0;
    }
    data[BIT] = count;           //每次存储每位数据持续的count个数，一个count为8*33=264us，间接获得下降沿时间间隔
    count = 0;                   //存完清零count个数
    BIT++;
    if(BIT==33)                  //接收33次后（即33个下降沿触发后），清零索引BIT，并将start标志置位
    {
        BIT=0;
        RECV_FLAG=1;
    }
    P2IFG = 0;                   //清除中断标志位
}

#pragma vector=TIMERB0_VECTOR     //TIMERA中断，在达到定时要求时才会产生中断
__interrupt void Timer_B(void)    //此次设置CCR0为33，在1MHz下，约为33us产生一次中断
{
    infrared_a++;                          //一次中断，a自增一次
    if(infrared_a == 8)                    //a自增8次，即经过约33*8=264us，清零，count++
    {
        infrared_a = 0;
        count++;
    }
}

