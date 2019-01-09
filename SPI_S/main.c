#include <msp430f169.h>
void init_spi_slave(){
      P3SEL = 0x0E;                             // ����P3��
      U0CTL = CHAR + SYNC + SWRST;              // 8λ���� SPIģʽ �����λʹ��
      U0TCTL = CKPL + STC;                      // ������UCLK�������� 3��SPI
      ME1 |= USPIE0;                             // ������������ģʽ
      U0CTL &= ~SWRST;                          // SPIʹ��
      IE1 |= URXIE0;                            // �����ж�ʹ��
      _EINT();                                  // �������ж�

}

#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void){
    unsigned char data=0;
    data=U0RXBUF;
        P6OUT=~data;
}
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    init_spi_slave();
    P6DIR=0xff;
    P6OUT=0xff;
    while(1);
}
