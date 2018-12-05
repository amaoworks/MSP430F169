/*
 * SG90.c
 *
 *  Created on: 2018��10��15��
 *      Author: Jack
 */
#include<msp430f169.h>
#include"lcd_1602.h"
extern unsigned int a;
extern unsigned char STATUS;

void Init_PWM()
{
      BCSCTL2 |= SELS ;                 //SMCLK = XT2
      BCSCTL2 = DIVS0 + DIVS1;
      P1DIR = 0xff;               // P1���
      P1OUT &= ~BIT2;
      CCR0 = 20000;                // PWM ����
      CCTL1 = OUTMOD_7;            // CCR1��λ/��λ
      CCR1 = a;                // CCR1 PWM ռ�ձ�50%
      TACTL = TASSEL_2 + MC_1;     // ��ʱ��Aʱ��ԴΪSMCLK,������ģʽ
}
void start()    //����
{
    P1SEL |= 0x04;  //P1.2�ڶ����� TA1 ���PWM
    TACTL= TASSEL_2 + MC_1; //��ʱ��Aʱ��ԴΪSMCLK��������ģʽ
    STATUS = 1;
    a=12000;
    CCR1 = a;

    return;
}

void stop()    //ֹͣ
{
    P1SEL = 0x00;    //P1.2�ڶ����� TA1 ���PWM
    TACTL= MC_0;
    P1OUT &=  ~BIT2;
    STATUS = 0;
    a = 0;
    CCR1 = a;

    return;
}

void speed_add()    //����
{
    a+=1000;
    CCR1 = a;
    if(a >= 19000)
        a = 19000;



    return;
}

void speed_sub()    //����
{
    a -= 1000;
    CCR1 = a;
    if(a <= 12000)
        a = 12000;

    return;
}
void show_status(unsigned char status, unsigned int speed)
{
    if(STATUS == 1){
        dis_str(0x80+8, "RUN ");
    }
    else
        dis_str(0x80+8, "STOP");
    write_cmd(0x80+0x40+8);
    switch(speed)
    {
    case 0:     write_data('0');  break;
    case 12000: write_data('1');  break;
    case 13000: write_data('2');  break;
    case 14000: write_data('3');  break;
    case 15000: write_data('4');  break;
    case 16000: write_data('5');  break;
    case 17000: write_data('6');  break;
    case 18000: write_data('7');  break;
    case 19000: write_data('8');  break;
    default: break;
    }
}
