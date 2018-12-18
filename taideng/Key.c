/*
 * Key.c
 *
 *  Created on: 2018��12��18��
 *      Author: Brown
 */
#include "Key.h"

extern unsigned char key, statu, clear;

void Key_Portinit(){
    P1DIR|=0X00;  //P1.0��P1.1��P1.2��P1.3Ϊ����ģʽ
    P1IE|=0X0F;   //P1.0��P1.1��P1.2��P1.3�����ж�
    P1IES|=0x0F;  //P1.0��P1.1��P1.2��P1.3Ϊ�½��ش���
}

/*P1�˿��ⲿ�ж�*/
#pragma vector = PORT1_VECTOR
__interrupt void p1init(void)   //ע�⣺interruptǰ���»���������������һ������
{
    if((P1IN&BIT0)==0){
        clear=1;
        statu=1;
        key++;
        if(key == 4){
            key = 0;
        }
    }

    if((P1IN&BIT1)==0){
        clear=1;
        statu=2;
//        PWM_Init(1, 1, 1, 10000, 3000);
    }


    P1IFG=0;//�жϱ�־λ���㣡����P1�˿��ⲿ�жϲ����Զ����㣬������Ҫ�ֶ�����
}
