#include "msp430x16x.h"
#include "display.h"
#include "key.h"
#include "process.h"
#include "golbal.h"
#include "led.h"
#include "UART.h"

unsigned char speedtemp;
unsigned char bt;
unsigned int bt_led;
unsigned int bt_led1;

void timer_init();

void main()
{
    WDTCTL = WDTPW + WDTHOLD;//ֹͣ���Ź�

    lcd_init(); //LCD��ʼ��
    key_init(); //������ʼ��
    led_init(); //led��ʼ��
    welcome();  //��ʾ��ӭ����(NOKIA andriod)
    ping();     //����activity
    timer_init();//��ʱ����ʼ��
    UART0_Init();
//    _EINT();
    bg_init();  //��������ֵ
    create();   //��������
    fangkuai_init();//����һ��Ҫ��ʾ�ķ�����ʾ����
    renew();
    disscore();
    disguan();
    _EINT();
    while(1)
    {
        key();
//        Uart0Send_Byte(0x30);
//        delay_ms(100);
    }
}


/**************************************************
            TA���������     TB�����½��ٶ�
***************************************************/
void timer_init()
{
    TACTL |= TASSEL_2 + ID_0 + MC_1;//SMCLK��ʱ�ӣ��޷�Ƶ��������ģʽ������TA����ж�
    TACCTL0|=CCIE;
    TACCR0 = 210 - 1;//0.2ms�ж�һ��

    TBCTL |= TBSSEL_2 + ID_0 + MC_1 ;//SMCLK��ʱ�ӣ��޷�Ƶ��������ģʽ������TB����ж�
    TBCCTL0|=CCIE;
    TBCCR0 = 10000-1;//5ms�ж�һ��
}
/**************************************************
                      �жϴ���
***************************************************/

/****************************************************************************
* ��    �ƣ�BT_ISR()
* ��    �ܣ���ʱ����CPU��
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
#pragma vector = TIMERA0_VECTOR
__interrupt void TA_ISR(void)   // 1/Div_Sec ��һ���жϣ���BasicTimer��������
{

    if(suijishu < 6)
        suijishu++;
    else
        suijishu = 0;

    if(bt_led==2500)
    {
        bt_led = 0;
        P1OUT^=BIT0;
    }
    bt_led++;
}

#pragma vector = TIMERB0_VECTOR
__interrupt void TB_ISR(void)   // 1/Div_Sec ��һ���жϣ���BasicTimer��������
{
    if(speedtemp<speed)
    {
        speedtemp++;
    }
    else
    {
        move();
        speedtemp = 0;
    }

    if(bt_led1==25)
    {
        bt_led1 = 0;
        P1OUT^=BIT3;
    }
    bt_led1++;
}
