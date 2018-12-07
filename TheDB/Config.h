/*
 * Config.h
 *
 *  Created on: 2018��12��6��
 *      Author: Brown
 */
#include <msp430f169.h>
#ifndef CONFIG_H_
#define CONFIG_H_

//��ʱ������IAR�Դ�������ʹ�õ�
#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//�Զ������ݽṹ������ʹ��
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//8��LED�ƣ�������P6�ڣ���ͨ���Ͽ���Դֹͣʹ�ã�ADCʹ��ʱ�Ͽ���Դ
#define LED8DIR         P6DIR
#define LED8            P6OUT                             //P6�ڽ�LED�ƣ�8��

//2.8��TFT������ʾ�������Ӳ������
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�

#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�

#define RD_CLR          P5OUT &= ~BIT7           //E�õ�
#define RD_SET          P5OUT |=  BIT7           //E�ø�

#define CS_CLR          P5OUT &= ~BIT0            //CS�õ�
#define CS_SET          P5OUT |=  BIT0            //CS�ø�

#define RST_CLR         P5OUT &= ~BIT3            //RST�õ�
#define RST_SET         P5OUT |=  BIT3            //RST�ø�

#define LE_CLR          P5OUT &= ~BIT1            //LE�õ�
#define LE_SET          P5OUT |=  BIT1            //LE�ø�

//2.8��TFT�����������������Ӳ������
#define PEN_CLR         P2OUT &= ~BIT0           //PEN�õ�,����������ʱ��Penirq������δ����ʱ�ĸߵ�ƽ��Ϊ�͵�ƽ
#define PEN_SET         P2OUT |=  BIT0           //PEN�ø�
#define PEN             (P2IN & 0x01)            //P2.0�����ֵ

#define TPDO_CLR    P2OUT &= ~BIT1           //TPDO�õ�
#define TPDO_SET    P2OUT |=  BIT1           //TPDO�ø�
#define TPDOUT          ((P2IN>>1)&0x01)         //P2.1�����ֵ

#define BUSY_CLR    P2OUT &= ~BIT3           //BUSY�õ�
#define BUSY_SET    P2OUT |=  BIT3           //BUSY�ø�

#define TPDI_CLR    P2OUT &= ~BIT4            //TPDI�õ�
#define TPDI_SET    P2OUT |=  BIT4            //TPDI�ø�

#define TPCS_CLR    P2OUT &= ~BIT5            //TPCS�õ�
#define TPCS_SET    P2OUT |=  BIT5            //TPCS�ø�

#define TPCLK_CLR   P2OUT &= ~BIT6            //TPCLK�õ�
#define TPCLK_SET   P2OUT |=  BIT6            //TPCLK�ø�

//����/12864Һ��/1602Һ�������ݿڣ���Һ������
#define DataDIR         P4DIR                     //���ݿڷ���
#define DataPort        P4OUT                     //P4��Ϊ���ݿ�

//��ɫ���룬TFT��ʾ��
#define White          0xFFFF                                                               //��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

void Clock_Init();
void WDT_Init();

#endif /* CONFIG_H_ */
