/*
 * Config.c
 *
 *  Created on: 2018��11��18��
 *      Author: myy12
 */
#include "Config.h"
//����Flash��ʱ�ӣ���ʼ��Flash������
void FlashInit(){
    FCTL2 = FWKEY + FSSEL_2 + FN1;          //Ĭ�� SMCLK/3 = 333KHz
}
//��������
void FlashErase(unsigned int Addr){
    char *FlashPtr;
    FlashPtr = (char *)Addr;
    FCTL1 = FWKEY + ERASE;                      // Set Erase bit
    FCTL3 = FWKEY;                              // Clear Lock bit
//    DINT;
    *FlashPtr = 0;                              // Dummy write to erase Flash segment B
    WaitForEnable();                            //Busy
//    EINT;
    FCTL1 = FWKEY;                              // Lock
    FCTL3 = FWKEY + LOCK;                       // Set Lock bit
}
//�ȴ�
void WaitForEnable()
{
    while((FCTL3 & BUSY) == BUSY);      //Busy
}
//д���ֽ�
void FlashWriteChar(unsigned int addr,char Data)
{
    char *FlashPtr = (char *)addr;              // Segment A pointer
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
//    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
//   EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
}
//д����
void FlashWriteWord(unsigned long addr,unsigned long Data)
{
    unsigned long *FlashPtr = (unsigned long *)addr;
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
//    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
//    EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
}
//��ȡ�� �� �ֽ�
unsigned char FlashReadChar(unsigned int Addr)
{
    unsigned char Data;
    unsigned char *FlashPtr = (unsigned char *) Addr;
    Data = *FlashPtr;
    return(Data);
}

unsigned int FlashReadWord(unsigned int Addr)
{
    unsigned int Data;
    unsigned int *FlashPtr = (unsigned int *)Addr;
    Data = *FlashPtr;
    return(Data);
}

void Clock_Init(){
    unsigned char i;
    BCSCTL1&=~XT2OFF;                  //��XT2����
    BCSCTL2|=SELM1+SELS;              //MCLKΪ8MHZ��SMCLKΪ8MHZ
    do{
      IFG1&=~OFIFG;                   //������������־
      for(i=0;i<100;i++)
         _NOP();
      }
    while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
    IFG1&=~OFIFG;
}
/*
void Write(){
    FlashWriteChar(InfoB,0x61);
    FlashWriteWord(InfoB+2,123);
}
//��ȡ
void Read(){
    c=FlashReadChar(InfoB);
    b = FlashReadWord(InfoB+2);
}
*/
