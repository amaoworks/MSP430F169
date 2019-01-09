/*
 * Touch_operation.c
 *
 *  Created on: 2018��11��30��
 *      Author: liu
 */

/*
 * Touch_operation.c
 *
 *  Created on: 2018��11��28��
 *      Author: liu
 */
#include "Touch_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern unsigned int LCD_X,LCD_Y;
extern unsigned char button;
extern unsigned char Display_flag;  //����ѡ���־λ
extern unsigned char Display_flag1;          //���Ȼ�Ƶ�ʱ�־λ
unsigned long fre_val=200;
double num=1.0;
static char table[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
unsigned char buf[65535];
unsigned char * int2str(unsigned int num)
{
   unsigned char temp;
   static unsigned char result[1024] = {0};

   unsigned int i = 0;
   unsigned int len = 0;

   while(num != 0)
    {
       result[i] = (num  % 10) + '0' ;
         num= num / 10;

         i++;
    }

   result[i] = '\0';

   len = strlen(result);

   for(i = 0; i < len / 2; i++)
    {
       temp = result[i];
         result[i]= result[len - 1 - i];
         result[len- 1 - i] = temp;
    }
   return result;
}

/*
void int2str(unsigned char x,unsigned char y,unsigned long num,unsigned char fcolor)
{   // num/=10;
   // unsigned int num1;
    unsigned char a=0;
   // num1=num;
    while(1)
    {
        if(num>0)
        {
            a++;
            if(num>9)
            {   LCD_PutChar(x,y,'0',Red,Yellow);
                num/=10;
                x-=8;
            }
            else
                LCD_PutChar(x,y,table[num],Red,Yellow);
        }
        else
            break;
    }
}*/

/********************************
 * ��������ʾ����Ƶ�ʣ����ȿ��ư���
 **********************************/
void image1(unsigned char pos,unsigned char* string)    //��������ʾ
{

    LCD_PutString24(pos,10,string,Red,White);
    LCD_PutString24(20,100,"Ƶ��:",Red,White);
    GUIfull(77,100,200,124,Yellow);
    LCD_PutString24(184,104,"Hz",Red,Yellow);
    LCD_PutString24(20,150,"����:",Red,White);
    GUIfull(77,150,200,174,Yellow);
    LCD_PutString24(184,154,"V",Red,Yellow);
    key_show(15,200,"<");
    key_show(90,200,">");
    GUIfull(165,200,165+60,260,Cyan);
    LCD_PutString(165+14,200+22,"ȷ��",Black,Cyan);  //��ťֵ��ʾ
}

void touch_screen()    //�ڶ�����������
{
    if(Getpix()==1)
    {
        if((LCD_X>=15)&&(LCD_X<15+60))
        {
            if((LCD_Y>=200)&&(LCD_Y<200+60))
            {
                GUIsquare2pix(15,200,75,260,Red);//����ʱ��ʾ
                delay_ms(1);
                delay_ms(1);
                delay_ms(1);
                while(PEN==0);
                button=1;
                GUIsquare2pix(15,200,75,260,White);
            }
        }
        else if((LCD_X>=90)&&(LCD_X<90+60))
        {
            if((LCD_Y>=200)&&(LCD_Y<200+60))
            {
                GUIsquare2pix(90,200,150,260,Red);
                delay_ms(3);
                while(PEN==0);
                button=2;
                GUIsquare2pix(90,200,150,260,White);
            }
        }
        else if((LCD_X>=165)&&(LCD_X<165+60))
        {   if((LCD_Y>=200)&&(LCD_Y<200+60))
            {
                GUIsquare2pix(165,200,225,260,Red);
                delay_ms(3);
                while(PEN==0);
                button=3;
                GUIsquare2pix(165,200,225,260,White);
            }
        }
    }
}
/*******************
 * ���������ؽ���
 * ��Ϊ������򣺷��ȣ�Ƶ�ʴ��ؽ��棬���ӣ����٣��Լ�ȷ�ϼ�
 */
void touch_screen1()//���β������津�ز���
{
    if(Getpix()==1)
    {
        if((LCD_X>=77)&&(LCD_X<200))   //Ƶ��ѡ������
        {
            if((LCD_Y>=100)&&(LCD_Y<124))
            {
                GUIsquare2pix(76,99,201,125,Red);
                delay_ms(3);
                while(PEN==0);
                GUIsquare2pix(76,149,201,175,White);//����ѡ��ȡ��
                Display_flag1=1;
            }
        }
        if((LCD_X>=77)&&(LCD_X<200))   //����ѡ������
        {
            if((LCD_Y>=150)&&(LCD_Y<174))
            {
                GUIsquare2pix(76,149,201,175,Red);
                delay_ms(3);
                while(PEN==0);
                GUIsquare2pix(76,99,201,125,White);//Ƶ��ѡ��ȡ��
                Display_flag1=2;
            }
        }
        if((LCD_X>=15)&&(LCD_X<15+60))  //���Ӱ���
        {
            if((LCD_Y>=200)&&(LCD_Y<200+60))
            {
                GUIsquare2pix(15,200,75,260,Red);
                delay_ms(3);
                while(PEN==0);
                GUIsquare2pix(15,200,75,260,White);
                if(Display_flag1==1)
                {
                    fre_val+=100;
                    LCD_PutString24(80,102,int2str(fre_val),Red,Yellow);
                    //Display_flag1=0;
                }
                if(Display_flag1==2)
                {
                    num+=0.1;
                    num_char(85,154,num);
                }
            }
         }
        if((LCD_X>=90)&&(LCD_X<90+60)) //��С����
        {
            if((LCD_Y>=200)&&(LCD_Y<200+60))
            {
                GUIsquare2pix(90,200,150,260,Red);
                delay_ms(3);
                while(PEN==0);
                GUIsquare2pix(90,200,150,260,White);
                if(Display_flag1==1)
                {
                    fre_val-=100;
                    LCD_PutString24(80,102,int2str(fre_val),Red,Yellow);
                }
                if(Display_flag1==2)
                {   num-=0.1;
                    num_char(85,154,num);
                }
            }
        }
        if((LCD_X>=165)&&(LCD_X<165+60))   //ȷ�ϰ���
        {   if((LCD_Y>=200)&&(LCD_Y<200+60))
            {
                GUIsquare2pix(165,200,225,260,Red);
                delay_ms(3);
                while(PEN==0);
                GUIsquare2pix(165,200,225,260,White);
            }
        }
    }

}
void func_choose()
{   if(Display_flag==0)
    {
       touch_screen();
       switch(button)
       {
       case 1:
           CLR_Screen(White);               //�ñ���ɫ����
           image1(84,"���Ҳ�");
           Display_flag=1;break;
       case 2:
           button=0;
           CLR_Screen(White);               //�ñ���ɫ����
           image1(84,"���ǲ�");
           Display_flag=1;break;
       case 3:
           button=0;
           CLR_Screen(White);               //�ñ���ɫ����
           image1(96,"����");
           Display_flag=1;break;

       }
    }
    if( Display_flag==1)
    {   touch_screen1();

    }
}

void num_char(unsigned char x,unsigned char y,double num)
{
    unsigned char i,j;
    unsigned int temp;
    temp=(unsigned int)num;
    for(i=0;i<=4;i++)
    {
        if(temp/(unsigned int)pow(10,4-i)!=0)
        {

            j=5-i;
            break;
        }
    }
    for(i=j;i>0;i--)//����������ת�����ַ�����
        {
            LCD_PutChar(x,y,table[temp/(unsigned int)pow(10,i-1)],Red,Yellow);
            x+=8;
            temp %=(unsigned int)pow(10,i-1);
        }
            LCD_PutChar(x,y,'.',Red,Yellow);
            x+=8;
            num -=(int)num;
       for(i=i+2;i<5-1;i++)//��С������ת�����ַ�����
       {
           num*=10;
           LCD_PutChar(x,y,table[(unsigned int)num],Red,Yellow);
           x+=8;
           num-=(int)num;
       }
}



