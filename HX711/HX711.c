/*
 * HX711.c
 *
 *  Created on: 2018年12月3日
 *      Author: Brown
 */
#include "HX711.h"
/*
int HX711_Read(void)                           //增益128
{
    unsigned long count = 0;
    //    count = count&0x0000000;                   //第25个脉冲下降沿来时，转换数据
    count = count&0x0800000;
    P4DIR|=0xef;
    HX=HX711_DOUT1;                            //数据口
    delay_us(4);
    HX=HX711_SCK0;
    while((P4IN&0x10)==0x10);
    delay_us(40);
    for(j=0;j<24;j++)
    {
        HX=HX711_SCK1;
        count=count<<1;
        HX=HX711_SCK0;
        if((P4IN&0x10)==0X10)
            count++;
    }
    HX=HX711_SCK1;
    count=count&0x007FFFFF;                    //第25个脉冲下降沿来时，转换数据
    delay_us(840);
    HX=HX711_SCK0;
    delay_us(4);
    return(count/405);                         //校正
}
 */
int HX711_Read(void)
{
    unsigned long Count;
    unsigned char i;

    P4DIR|=0xef;
    HX=HX711_DOUT1;                            //数据口
    delay_us(4);
    HX=HX711_SCK0;      //使能AD（PD_SCL 置低）
    Count=0;
    while((P4IN&0x10)==0x10); //AD转换未结束则等待，否则开始读取
    delay_us(40);
    for (i = 0; i < 24; i++)
    {
        HX=HX711_SCK1;        //PD_SCL 置高（发送脉冲）
        Count=Count<<1; //下降沿来时变量Count左移一位，右侧补零
        HX=HX711_SCK0;          //PD_SCL 置低
        if((P4IN&0x10)==0x10) Count++;
    }
    HX=HX711_SCK1;
    Count=Count^0x800000;//第25个脉冲下降沿来时，转换数据
    delay_us(840);
    HX=HX711_SCK0;
    return(Count/405);
}
