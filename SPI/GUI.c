/*
 * GUI.c
 *
 *  Created on: 2018��12��24��
 *      Author: Brown
 */
#include "GUI.h"
#include <math.h>


/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ����
//  ��������� x��y ��Ҫ��������
//            color �����ɫ
 ****************************************************************************************************/
void GUIpoint(unsigned int x,unsigned int y,unsigned int color)
{
    Address_set(x,x,y,y);                                                //��������Ҫ��������任���������������ֱ����x0,x1,y0,y1������

    LCD_write_data(color);                                                      //��ָ����д����ɫ����
}

//***********************************************************************
//         ����GUI���ߺ�������x0,y0��Ϊ��ʼ����,��x1,y1��Ϊ�յ�����
//         line_color �ߵ���ɫ
//***********************************************************************

void GUIline(uint x0,uint y0,uint x1,uint y1,uint line_color)   //���ߺ���
{
    int temp;
    int dx,dy;                          //������㵽�յ�ĺᡢ����������ֵ
    int s1,s2,status,i;
    int Dx,Dy,sub;

    dx = x1 - x0;
    if(dx >= 0)                     //X�ķ��������ӵ�
        s1 = 1;
    else                                //X�ķ����ǽ��͵�
        s1 = -1;
    dy = y1 - y0;                   //�ж�Y�ķ��������ӻ��ǽ�����
    if(dy >= 0)
        s2 = 1;
    else
        s2 =- 1;

    Dx = abs(x1-x0);                //����ᡢ�ݱ�־����ֵ�ľ���ֵ
    Dy = abs(y1-y0);

    if(Dy > Dx)
    {                                   //��45�Ƚ�Ϊ�ֽ��ߣ�����Y����status=1,����X����status=0
        temp = Dx;
        Dx = Dy;
        Dy = temp;
        status = 1;
    }
    else
        status = 0;

    /*********Bresenham�㷨������������ֱ��********/
    sub = Dy + Dy - Dx;                 //��1���ж��¸����λ��
    for(i = 0;i < Dx;i ++)
    {
        GUIpoint(x0,y0,line_color);           //����
        if(sub >= 0)
        {
            if(status == 1)               //�ڿ���Y������xֵ��1
                x0 += s1;
            else                     //�ڿ���X������yֵ��1
                y0 += s2;
            sub -= (Dx + Dx);                 //�ж����¸����λ��
        }
        if(status == 1)
            y0 += s2;
        else
            x0 += s1;
        sub += Dy + Dy;

    }
}

//***********************************************************************
//         ����GUI�����ߺ�������x0,y0��Ϊ��ʼ����,��x1,y1��Ϊ�յ�����
//         line_color �ߵ���ɫ
//***********************************************************************

void GUIDotline(uint x0,uint y0,uint x1,uint y1,uint line_color)   //�����ߺ���
{
    int temp;
    int dx,dy;                  //������㵽�յ�ĺᡢ����������ֵ
    int s1,s2,status,i;
    int Dx,Dy,sub;

    dx = x1 - x0;
    if(dx >= 0)                 //X�ķ��������ӵ�
        s1 = 1;
    else                          //X�ķ����ǽ��͵�
        s1 = -1;
    dy = y1 - y0;               //�ж�Y�ķ��������ӻ��ǽ�����
    if(dy >= 0)
        s2 = 1;
    else
        s2 =- 1;

    Dx = abs(x1-x0);             //����ᡢ�ݱ�־����ֵ�ľ���ֵ
    Dy = abs(y1-y0);

    if(Dy > Dx)
    {                                   //��45�Ƚ�Ϊ�ֽ��ߣ�����Y����status=1,����X����status=0
        temp = Dx;
        Dx = Dy;
        Dy = temp;
        status = 1;
    }
    else
        status = 0;

    /*********Bresenham�㷨������������ֱ��********/
    sub = Dy + Dy - Dx;                                                  //��1���ж��¸����λ��
    for(i = 0;i < Dx;i ++)
    {
        if((i%10)<=4) GUIpoint(x0,y0,line_color);       //���㣬���߼���С������������ڣ����ò�ͬ���ж�����
        if(sub >= 0)
        {
            if(status == 1)                                         //�ڿ���Y������xֵ��1
                x0 += s1;
            else                                                            //�ڿ���X������yֵ��1
                y0 += s2;
            sub -= (Dx + Dx);                                   //�ж����¸����λ��
        }
        if(status == 1)
            y0 += s2;
        else
            x0 += s1;
        sub += Dy + Dy;


    }
}

/****************************************************************************
 * ���ƣ�GUI_Full(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour)
 * ���ܣ��û�ͼ�ķ������һ������
 * ��ڲ�����x0           ��ʼ�������
 *          y0           ��ʼ��������
 *          x1           ��ֹ�������
 *          y1       ��ֹ��������
 *          full_color       ��ʾ��ɫ
 * ���ڲ�������
 ****************************************************************************/
void GUIfull(uint x0,uint y0,uint x1,uint y1,uint full_colour)
{
    uint i,j;
    for(j = y0;j <= y1;j ++)
        for(i = x0;i <= x1;i ++)
            GUIpoint(i,j,full_colour);
}

/****************************************************************************
 * ���ƣ�GUIsquare1pix(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour)
 * ���ܣ��û�ͼ�ķ�������һ�����α߿�,1�����ص��
 * ��ڲ�����x0           ��ʼ�������
 *          y0           ��ʼ��������
 *          x1           ��ֹ�������
 *          y1       ��ֹ��������
 *          full_color       ��ʾ��ɫ
 * ���ڲ�������
 ****************************************************************************/
void GUIsquare1pix(uint x0,uint y0,uint x1,uint y1,uint full_colour)
{
//    uint i,j;

    GUIline(x0,y0,x0,y1,full_colour);
    GUIline(x0,y0,x1,y0,full_colour);
    GUIline(x0,y1,x1,y1,full_colour);
    GUIline(x1,y0,x1,y1,full_colour);
}

/****************************************************************************
 * ���ƣ�GUIsquare2pix(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour)
 * ���ܣ��û�ͼ�ķ�������һ�����α߿�,2�����ص��
 * ��ڲ�����x0           ��ʼ�������
 *          y0           ��ʼ��������
 *          x1           ��ֹ�������
 *          y1       ��ֹ��������
 *          full_color       ��ʾ��ɫ
 * ���ڲ�������
 ****************************************************************************/
void GUIsquare2pix(uint x0,uint y0,uint x1,uint y1,uint full_colour)
{
    uint i;

    for(i=0;i<2;i++)
    {
        GUIline(x0+i,y0,x0+i,y1,full_colour);
        GUIline(x0,y0+i,x1,y0+i,full_colour);
        GUIline(x0,y1-i,x1,y1-i,full_colour);
        GUIline(x1-i,y0,x1-i,y1,full_colour);
    }
}
/****************************************************************************
 * ���ƣ�plotC(int x,int y,int xc,int yc,unsigned char yc_colour)
 * ���ܣ��˷ֵ㻭Բ����
 * ��ڲ�����x            ָ������������е�λ��
 *           y           ָ������������е�λ��
 *          yc_color     ��ʾ��ɫ,���ݲ�ɫ�����趨
 * ���ڲ�������
 ****************************************************************************/
void plotC(uint x,uint y,uint xc,int yc,uint yc_colour)
{
    GUIpoint(xc+x,yc+y,yc_colour);
    GUIpoint(xc+x,yc-y,yc_colour);
    GUIpoint(xc-x,yc+y,yc_colour);
    GUIpoint(xc-x,yc-y,yc_colour);
    GUIpoint(xc+y,yc+x,yc_colour);
    GUIpoint(xc+y,yc-x,yc_colour);
    GUIpoint(xc-y,yc+x,yc_colour);
    GUIpoint(xc-y,yc-x,yc_colour);
}

/****************************************************************************
 * ���ƣ�GUI_Circle(int xc,int yc,int r,unsigned char circle_colour)
 * ���ܣ���Բ
 * ��ڲ�����xc               Բ�ĵ�������
 *           yc          Բ�ĵ�������
 *           r               �뾶
 *          circle_color     ��ʾ��ɫ
 * ���ڲ�������
 ****************************************************************************/
void GUIcircle(uint xc,uint yc,uint r,uint circle_colour)
{
    int x,y,d;
    y = r;
    d = 3 - (r + r);
    x = 0;
    while(x <= y)
    {
        plotC(x,y,xc,yc,circle_colour);
        if(d < 0)
            d += (x + x + x + x) + 6;
        else
        {
            d+=((x - y) + (x - y) + (x - y) + (x - y)) + 10;
            y = y - 1;
        }
        x = x + 1;
    }
}
