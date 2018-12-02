/*
 * Config.c
 *
 *  Created on: 2018年11月18日
 *      Author: myy12
 */
#include "Config.h"
//设置Flash的时钟，初始化Flash控制器
void FlashInit(){
    FCTL2 = FWKEY + FSSEL_2 + FN1;          //默认 SMCLK/3 = 333KHz
}
//擦除函数
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
//等待
void WaitForEnable()
{
    while((FCTL3 & BUSY) == BUSY);      //Busy
}
//写入字节
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
//写入字
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
//读取字 或 字节
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
    BCSCTL1&=~XT2OFF;                  //打开XT2振荡器
    BCSCTL2|=SELM1+SELS;              //MCLK为8MHZ，SMCLK为8MHZ
    do{
      IFG1&=~OFIFG;                   //清楚振荡器错误标志
      for(i=0;i<100;i++)
         _NOP();
      }
    while((IFG1&OFIFG)!=0);           //如果标志位1，则继续循环等待
    IFG1&=~OFIFG;
}
/*
void Write(){
    FlashWriteChar(InfoB,0x61);
    FlashWriteWord(InfoB+2,123);
}
//读取
void Read(){
    c=FlashReadChar(InfoB);
    b = FlashReadWord(InfoB+2);
}
*/
