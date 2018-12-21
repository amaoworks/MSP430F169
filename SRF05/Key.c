/*
 * Key.c
 *
 *  Created on: 2018��12��13��
 *      Author: Brown
 */
#include "Key.h"

unsigned long safe;

void Key_init(){
    P1DIR|=0X00;  //P1.0��P1.1��P1.2��P1.3Ϊ����ģʽ
    P1IE|=0X0F;   //P1.0��P1.1��P1.2��P1.3�����ж�
    P1IES|=0x0F;  //P1.0��P1.1��P1.2��P1.3Ϊ�½��ش���
}

/*P1�˿��ⲿ�ж�*/
#pragma vector = PORT1_VECTOR
__interrupt void p1init(void)   //ע�⣺interruptǰ���»���������������һ������
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

    P1IFG=0;//�жϱ�־λ���㣡����P1�˿��ⲿ�жϲ����Զ����㣬������Ҫ�ֶ�����
}
