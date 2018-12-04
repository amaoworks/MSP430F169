/*
 * UART.c
 *
 *  Created on: 2018��12��3��
 *      Author: Brown
 */
#include"UART.h"

void UART0_Init()
{
    U0CTL|=SWRST;               //��λSWRST
    U0CTL|=CHAR;                //8λ����ģʽ
    U0TCTL|=SSEL1;              //SMCLKΪ����ʱ��
    U0BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
    U0BR0=baud_l;               //N=UBR+(UxMCTL)/8
    U0MCTL=0x00;                //΢���Ĵ���Ϊ0��������9600bps
    ME1|=UTXE0;                 //UART0����ʹ��
    ME1|=URXE0;                 //UART0����ʹ��
    U0CTL&=~SWRST;
    IE1|=URXIE0;                //�����ж�ʹ��λ

    P3SEL|= BIT4;               //����IO��Ϊ��ͨI/Oģʽ
    P3DIR|= BIT4;               //����IO�ڷ���Ϊ���
    P3SEL|= BIT5;
    _EINT();
}


void Uart0Send_Byte(unsigned char data)
{
    while((IFG1&UTXIFG0)==0);          //���ͼĴ����յ�ʱ��������
    U0TXBUF=data;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//UART1
////////////////////////////////////////////////////////////////////////////////////////////////

void UART1_Init()
{
    U1CTL|=SWRST;               //��λSWRST
    U1CTL|=CHAR;                //8λ����ģʽ
    U1TCTL|=SSEL1;              //SMCLKΪ����ʱ��
    U1BR1=baud_h;               //BRCLK=8MHZ,Baud=BRCLK/N
    U1BR0=baud_l;               //N=UBR+(UxMCTL)/8
    U0MCTL=0x00;                //΢���Ĵ���Ϊ0��������9600bps
    ME2|=UTXE1;                 //UART0����ʹ��
    ME2|=URXE1;                 //UART0����ʹ��
    U1CTL&=~SWRST;
    IE2|=URXIE1;                //�����ж�ʹ��λ

    P3SEL|= BIT6;               //����IO��Ϊ��ͨI/Oģʽ
    P3DIR|= BIT6;               //����IO�ڷ���Ϊ���
    P3SEL|= BIT7;
    _EINT();
}


void Uart1Send_Byte(unsigned char data)
{
    while((IFG2&UTXIFG1)==0);          //���ͼĴ����յ�ʱ��������
    U1TXBUF=data;
}
