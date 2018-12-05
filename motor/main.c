#include<msp430f169.h>
#include"delay.h"
#include"type.h"
#include"Port.h"
#include"lcd_1602.h"
#include"DC_motor.h"
#include"inf.h"
#include"clock.h"


unsigned int count;              //TIMERB�ж��б���
unsigned char infrared_a;                 //TIMERB�ж��б���
unsigned char BIT;               //��������λ��
unsigned char RECV_FLAG;         //���յ����ݵı�־λ
unsigned char data[33];          //һλ������+32λ���ݵ�����
unsigned char ircode[4];         //�洢�����û��롢һ�������롢һ��������ķ���
unsigned char VALUE;             //ȫ�ּ�ֵ

uint a = 0;         //��ʼΪ50%ռ�ձ�
uchar STATUS=0;


void main()
{
    WDTCTL = WDTPW + WDTHOLD;
    init_clk_1M();
    Init_PWM();

    init_1602_port();
    lcd1602_init();

    init_port2();                //��ʼ���ⲿ�ж�P2.0
    init_device();               //��ʼ����������豸��TIMERB

    while(1){
//        CCR1 = a;
        //P1SEL |= 0x04;  //P1.2�ڶ����� TA1 ���PWM
        //TACTL= TASSEL_2 + MC_1;  //��ʱ��Aʱ��ԴΪSMCLK��������ģʽ
        infrared_decode();       //�������
        set_value(ircode[2]);    //���ø��������ļ�ֵ
        switch(VALUE){  //�Լ�ֵ���д���
            case 1: start();        break;     //����
            case 2: stop();         break;     //ֹͣ
            case 3: speed_add();    break;     //���٣�ÿ������1000����ʱ������ֵ
            case 4: speed_sub();    break;     //���٣�ÿ�μ���1000����ʱ������ֵ
            default: break;
        }
        VALUE = 0;         //��ֵ���
        ircode[2]=0;       //ircode[2]ȫ��������Ҫ���㣬�����´ν�����Ȼ���õ�����ֵ��
        show_status(STATUS, a);
        P6DIR = 0xff;       //���Գ���
        P6OUT = 0x0f;

    }
}

#pragma vector=PORT2_VECTOR      //�˿�P2�ж�
__interrupt void Port2_ISR(void)
{
    if(count>32)                 //��һ�ν���ʱ�ж�count������>32Ϊ�����룬
    {
        BIT=0;
    }
    data[BIT] = count;           //ÿ�δ洢ÿλ���ݳ�����count������һ��countΪ8*33=264us����ӻ���½���ʱ����
    count = 0;                   //��������count����
    BIT++;
    if(BIT==33)                  //����33�κ󣨼�33���½��ش����󣩣���������BIT������start��־��λ
    {
        BIT=0;
        RECV_FLAG=1;
    }
    P2IFG = 0;                   //����жϱ�־λ
}

#pragma vector=TIMERB0_VECTOR     //TIMERA�жϣ��ڴﵽ��ʱҪ��ʱ�Ż�����ж�
__interrupt void Timer_B(void)    //�˴�����CCR0Ϊ33����1MHz�£�ԼΪ33us����һ���ж�
{
    infrared_a++;                          //һ���жϣ�a����һ��
    if(infrared_a == 8)                    //a����8�Σ�������Լ33*8=264us�����㣬count++
    {
        infrared_a = 0;
        count++;
    }
}

