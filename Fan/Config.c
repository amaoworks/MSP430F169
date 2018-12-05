/*
 * Config.c
 *
 *  Created on: 2018年12月4日
 *      Author: Brown
 */
#include "Config.h"

void Clock_Init(unsigned char model)
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //打开XT2振荡器
//  BCSCTL2|=SELM1+SELS;            //MCLK为8MHZ，SMCLK为8MHZ
  if(model == 1){
      BCSCTL2 |= SELM1 + SELS;          //MCLK为8MHZ，SMCLK为8MHZ
  }else{
      BCSCTL2 |= DIVS0 + DIVS1;     //8分频  1MHz
  }
  do{
    IFG1&=~OFIFG;                   //清楚振荡器错误标志
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //如果标志位1，则继续循环等待
  IFG1&=~OFIFG;
}
