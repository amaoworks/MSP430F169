/*
 * HX711.c
 *
 *  Created on: 2018��12��3��
 *      Author: Brown
 */
#include "HX711.h"
/*
int HX711_Read(void)                           //����128
{
    unsigned long count = 0;
    //    count = count&0x0000000;                   //��25�������½�����ʱ��ת������
    count = count&0x0800000;
    P4DIR|=0xef;
    HX=HX711_DOUT1;                            //���ݿ�
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
    count=count&0x007FFFFF;                    //��25�������½�����ʱ��ת������
    delay_us(840);
    HX=HX711_SCK0;
    delay_us(4);
    return(count/405);                         //У��
}
 */
int HX711_Read(void)
{
    unsigned long Count;
    unsigned char i;

    P4DIR|=0xef;
    HX=HX711_DOUT1;                            //���ݿ�
    delay_us(4);
    HX=HX711_SCK0;      //ʹ��AD��PD_SCL �õͣ�
    Count=0;
    while((P4IN&0x10)==0x10); //ADת��δ������ȴ�������ʼ��ȡ
    delay_us(40);
    for (i = 0; i < 24; i++)
    {
        HX=HX711_SCK1;        //PD_SCL �øߣ��������壩
        Count=Count<<1; //�½�����ʱ����Count����һλ���Ҳಹ��
        HX=HX711_SCK0;          //PD_SCL �õ�
        if((P4IN&0x10)==0x10) Count++;
    }
    HX=HX711_SCK1;
    Count=Count^0x800000;//��25�������½�����ʱ��ת������
    delay_us(840);
    HX=HX711_SCK0;
    return(Count/405);
}
