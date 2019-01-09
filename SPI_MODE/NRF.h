/*
 * NRF.h
 *
 *  Created on: 2018年11月3日
 *      Author: liu
 */
#ifndef NRF_H_
#define NRF_H_
#define RF24L01_CE_0 P1OUT &=~BIT5
#define RF24L01_CE_1 P1OUT |=BIT5
//RF24L01_CSN端口
#define RF24L01_CSN_0 P2OUT &=~BIT7
#define RF24L01_CSN_1 P2OUT |=BIT7
//IRQ状态
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
//NRF24L01寄存器指令
#define READ_REG        0x00 //读寄存器指令
#define WRITE_REG       0x20 //写寄存器指令
#define RD_RX_PLOAD     0x61 //读取接收数据指令
#define WR_TX_PLOAD     0xa0 //写等待发送数据指令
#define FLUSH_TX        0xe1 //重新发送FIFO指令
#define FLUSH_RX        0xe2 //重新接收FIFO指令
#define REUSE_TX_PL     0xe3 //定义重复装载数据指令
#define NOP1            0xff //保留
//NRF24L01寄存器地址
#define CONFIG          0x00 //配置收发状态
#define EN_AA           0x01 //自动应答功能设置
#define EN_RXADDR       0x02 //可用信道设置
#define SETUP_AW        0x03 //收发地址宽度设置
#define SETUP_RETR      0x04 //自动重发功能设置
#define RF_CH           0x05 //工作频率设置
#define RF_SETUP        0x06 //发射速率，功耗功能设置
#define STATUS          0x07 //状态寄存器
#define OBSERVE_TX      0x08 //发送监测功能
#define CD              0x09 //地址检测
//频道0-频道5接收地址
#define RX_ADDR_P0      0x0a
#define RX_ADDR_P1      0x0b
#define RX_ADDR_P2      0x0c
#define RX_ADDR_P3      0x0d
#define RX_ADDR_P4      0x0e
#define RX_ADDR_P5      0x0f
//发送地址寄存器
#define TX_ADDR         0x10
//接收频道0-5数据长度
#define RX_PW_P0        0x11
#define RX_PW_P1        0x12
#define RX_PW_P2        0x13
#define RX_PW_P3        0x14
#define RX_PW_P4        0x15
#define RX_PW_P5        0x16
//FIFO栈入栈出状态寄存器设置
#define FIFO_STATUS     0x17

#endif /* NRF_H_ */
