extern unsigned index;
#include "UART.h"
#include "config.h"
extern unsigned char index1;
//*************************************************************************
//               MSP430���ڳ�ʼ��
//*************************************************************************
void UART_Init()
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
}

//*************************************************************************
//              ����0�������ݺ���
//*************************************************************************

void Send_Byte(uchar data)
{
    while((IFG1&UTXIFG0)==0);          //���ͼĴ����յ�ʱ��������
    U0TXBUF=data;

    if(data == 'a')
    {
        keyvalue=0;
    }
    if(data == 'b')
    {
        keyvalue=1;
    }
    if(data == 'c')
    {
        keyvalue=2;
    }
    if(data == 'd')
    {
        keyvalue=3;
    }
    if(data == 'e')
    {
        keyvalue=4;
    }
    if(data == 'f')
    {
        keyvalue=5;
    }
    if(data == 'k')
    {
        keyvalue=10;
    }
    if(data == 'l')
    {
        keyvalue=11;
    }
    if(data == 'm')
    {
        keyvalue=12;
    }
    if(data == 'n')
    {
        keyvalue=13;
    }
    if(data == 'o')
    {
        keyvalue=14;
    }
    if(data == 'p')
    {
        keyvalue=15;
    }
    if(data == 'q')
    {
        keyvalue=16;
    }
    return;
}
//*************************************************************************
//               �������Դ��� 0 �Ľ����ж�
//*************************************************************************

#pragma vector=USART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
    uchar data;
    data=U0RXBUF;                       //���յ������ݴ�����
    Send_Byte(data);                    //�����յ��������ٷ��ͳ�ȥ
}

//*************************************************************************
//            �������Դ��� 0 �ķ����жϣ�Ԥ��
//*************************************************************************

#pragma vector=USART0TX_VECTOR
__interrupt void UART0_TX_ISR(void)
{

}

