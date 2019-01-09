/*
 * NRF.h
 *
 *  Created on: 2018��11��3��
 *      Author: liu
 */
#ifndef NRF_H_
#define NRF_H_
#define RF24L01_CE_0 P1OUT &=~BIT5
#define RF24L01_CE_1 P1OUT |=BIT5
//RF24L01_CSN�˿�
#define RF24L01_CSN_0 P2OUT &=~BIT7
#define RF24L01_CSN_1 P2OUT |=BIT7
//IRQ״̬
#define RF24L01_IRQ_0 P1OUT &=~BIT4
#define RF24L01_IRQ_1 P1OUT |=BIT4

/*#define RF24L01_SCK_0 P3OUT &=~BIT3
#define RF24L01_SCK_1 P3OUT |=BIT3
#define RF24L01_MISO_0 P3OUT &=~BIT2
#define RF24L01_MISO_1 P3OUT |=BIT2
#define RF24L01_MOSI_0 P3OUT &=~BIT1
#define RF24L01_MOSI_1 P3OUT |=BIT1*/

#define TX_ADR_WIDTH    5
#define RX_ADR_WIDTH    5
#define TX_PLOAD_WIDTH  32
#define RX_PLOAD_WIDTH  32
//NRF24L01�Ĵ���ָ��
#define READ_REG        0x00 //���Ĵ���ָ��
#define WRITE_REG       0x20 //д�Ĵ���ָ��
#define RD_RX_PLOAD     0x61 //��ȡ��������ָ��
#define WR_TX_PLOAD     0xa0 //д�ȴ���������ָ��
#define FLUSH_TX        0xe1 //���·���FIFOָ��
#define FLUSH_RX        0xe2 //���½���FIFOָ��
#define REUSE_TX_PL     0xe3 //�����ظ�װ������ָ��
#define NOP1            0xff //����
//NRF24L01�Ĵ�����ַ
#define CONFIG          0x00 //�����շ�״̬
#define EN_AA           0x01 //�Զ�Ӧ��������
#define EN_RXADDR       0x02 //�����ŵ�����
#define SETUP_AW        0x03 //�շ���ַ�������
#define SETUP_RETR      0x04 //�Զ��ط���������
#define RF_CH           0x05 //����Ƶ������
#define RF_SETUP        0x06 //�������ʣ����Ĺ�������
#define STATUS          0x07 //״̬�Ĵ���
#define OBSERVE_TX      0x08 //���ͼ�⹦��
#define CD              0x09 //��ַ���
//Ƶ��0-Ƶ��5���յ�ַ
#define RX_ADDR_P0      0x0a
#define RX_ADDR_P1      0x0b
#define RX_ADDR_P2      0x0c
#define RX_ADDR_P3      0x0d
#define RX_ADDR_P4      0x0e
#define RX_ADDR_P5      0x0f
//���͵�ַ�Ĵ���
#define TX_ADDR         0x10
//����Ƶ��0-5���ݳ���
#define RX_PW_P0        0x11
#define RX_PW_P1        0x12
#define RX_PW_P2        0x13
#define RX_PW_P3        0x14
#define RX_PW_P4        0x15
#define RX_PW_P5        0x16
//FIFOջ��ջ��״̬�Ĵ�������
#define FIFO_STATUS     0x17

#endif /* NRF_H_ */
