/*
 * Key.c
 *
 *  Created on: 2018年12月13日
 *      Author: Brown
 */
#include "Key.h"

unsigned long safe;

void Key_init(){
    P1DIR|=0X00;  //P1.0、P1.1、P1.2、P1.3为输入模式
    P1IE|=0X0F;   //P1.0、P1.1、P1.2、P1.3允许中断
    P1IES|=0x0F;  //P1.0、P1.1、P1.2、P1.3为下降沿触发
}

/*P1端口外部中断*/
#pragma vector = PORT1_VECTOR
__interrupt void p1init(void)   //注意：interrupt前的下划线是两条，不是一条！！
{
    if((P1IN&BIT0)==0){
        safe+=100;
    }

    if((P1IN&BIT1)==0){
        safe-=100;
        if(safe <= 100){
            safe = 100;
        }
    }

    P1IFG=0;//中断标志位清零！！！P1端口外部中断不会自动清零，所以需要手动清零
}
