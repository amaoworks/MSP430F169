#include <msp430f169.h>
void init_spi_slave(){
      P3SEL = 0x0E;                             // 设置P3口
      U0CTL = CHAR + SYNC + SWRST;              // 8位数据 SPI模式 软件复位使能
      U0TCTL = CKPL + STC;                      // 数据在UCLK上升是锁 3线SPI
      ME1 |= USPIE0;                             // 可以用作其他模式
      U0CTL &= ~SWRST;                          // SPI使能
      IE1 |= URXIE0;                            // 接收中断使能
      _EINT();                                  // 开启总中断

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
