/*
 * GUI.c
 *
 *  Created on: 2018年11月27日
 *      Author: liu
 */

#include "GUI.h"
#include "TFT2.8.h"

void key_show(unsigned char x1,unsigned char y1,unsigned char * str)
{
    GUIfull(x1,y1,x1+60,y1+60,Cyan);
    LCD_PutString(x1+26,y1+22,str,Black,Cyan);  //按钮值显示
}
void GUIpoint(unsigned int x,unsigned int y,unsigned int color)
{
    LCD_SetPos(x,x,y,y);                                                //横屏这里要进行坐标变换，如果是竖屏，则直接是x0,x1,y0,y1做参数

    Write_Data_U16(color);                                                      //在指定点写入颜色数据
}

//***********************************************************************
//         大屏GUI画线函数，（x0,y0）为起始坐标,（x1,y1）为终点坐标
//         line_color 线的颜色
//***********************************************************************

void GUIline(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int line_color)   //画线函数
{
    int temp;
    int dx,dy;                          //定义起点到终点的横、纵坐标增加值
    int s1,s2,status,i;
    int Dx,Dy,sub;

      dx = x1 - x0;
    if(dx >= 0)                     //X的方向是增加的
        s1 = 1;
    else                                //X的方向是降低的
        s1 = -1;
    dy = y1 - y0;                   //判断Y的方向是增加还是降到的
    if(dy >= 0)
        s2 = 1;
    else
        s2 =- 1;

    Dx = abs(x1-x0);                //计算横、纵标志增加值的绝对值
    Dy = abs(y1-y0);

    if(Dy > Dx)
    {                                   //以45度角为分界线，靠进Y轴是status=1,靠近X轴是status=0
        temp = Dx;
        Dx = Dy;
        Dy = temp;
    status = 1;
    }
    else
        status = 0;

/*********Bresenham算法画任意两点间的直线********/
    sub = Dy + Dy - Dx;                 //第1次判断下个点的位置
    for(i = 0;i < Dx;i ++)
    {
        GUIpoint(x0,y0,line_color);           //画点
        if(sub >= 0)
        {
            if(status == 1)               //在靠近Y轴区，x值加1
                x0 += s1;
            else                     //在靠近X轴区，y值加1
                y0 += s2;
            sub -= (Dx + Dx);                 //判断下下个点的位置
        }
        if(status == 1)
            y0 += s2;
        else
            x0 += s1;
        sub += Dy + Dy;

    }
}

//***********************************************************************
//         大屏GUI画虚线函数，（x0,y0）为起始坐标,（x1,y1）为终点坐标
//         line_color 线的颜色
//***********************************************************************

void GUIDotline(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int line_color)   //画虚线函数
{
    int temp;
    int dx,dy;                  //定义起点到终点的横、纵坐标增加值
    int s1,s2,status,i;
    int Dx,Dy,sub;

      dx = x1 - x0;
    if(dx >= 0)                 //X的方向是增加的
        s1 = 1;
    else                          //X的方向是降低的
        s1 = -1;
    dy = y1 - y0;               //判断Y的方向是增加还是降到的
    if(dy >= 0)
        s2 = 1;
    else
        s2 =- 1;

    Dx = abs(x1-x0);             //计算横、纵标志增加值的绝对值
    Dy = abs(y1-y0);

    if(Dy > Dx)
    {                                   //以45度角为分界线，靠进Y轴是status=1,靠近X轴是status=0
        temp = Dx;
        Dx = Dy;
        Dy = temp;
    status = 1;
    }
    else
        status = 0;

/*********Bresenham算法画任意两点间的直线********/
    sub = Dy + Dy - Dx;                                                  //第1次判断下个点的位置
    for(i = 0;i < Dx;i ++)
    {
        if((i%10)<=4) GUIpoint(x0,y0,line_color);       //画点，虚线间距大小可以在这里调节，设置不同的判断条件
        if(sub >= 0)
        {
            if(status == 1)                                         //在靠近Y轴区，x值加1
                x0 += s1;
            else                                                            //在靠近X轴区，y值加1
                y0 += s2;
            sub -= (Dx + Dx);                                   //判断下下个点的位置
        }
        if(status == 1)
            y0 += s2;
        else
            x0 += s1;
        sub += Dy + Dy;


    }
}

/****************************************************************************
* 名称：GUI_Full(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour)
* 功能：用绘图的方法填充一个矩形
* 入口参数：x0           起始点横坐标
*          y0           起始点纵坐标
*          x1           终止点横坐标
*          y1       终止点纵坐标
*          full_color       显示颜色
* 出口参数：无
****************************************************************************/
void GUIfull(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour)
{
    unsigned int i,j;
for(j = y0;j <= y1;j ++)
    for(i = x0;i <= x1;i ++)
    GUIpoint(i,j,full_colour);
}

/****************************************************************************
* 名称：GUIsquare1pix(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour)
* 功能：用绘图的方法绘制一个矩形边框,1个像素点粗
* 入口参数：x0           起始点横坐标
*          y0           起始点纵坐标
*          x1           终止点横坐标
*          y1       终止点纵坐标
*          full_color       显示颜色
* 出口参数：无
****************************************************************************/
void GUIsquare1pix(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour)
{
    unsigned int i;

    GUIline(x0,y0,x0,y1,full_colour);
        GUIline(x0,y0,x1,y0,full_colour);
        GUIline(x0,y1,x1,y1,full_colour);
        GUIline(x1,y0,x1,y1,full_colour);
}

/****************************************************************************
* 名称：GUIsquare2pix(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour)
* 功能：用绘图的方法绘制一个矩形边框,2个像素点粗
* 入口参数：x0           起始点横坐标
*          y0           起始点纵坐标
*          x1           终止点横坐标
*          y1       终止点纵坐标
*          full_color       显示颜色
* 出口参数：无
****************************************************************************/
void GUIsquare2pix(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour)
{
    unsigned int i=0;
    for(i=0;i<2;i++)
            {
                GUIline(x0+i,y0,x0+i,y1,full_colour);
                GUIline(x0,y0+i,x1,y0+i,full_colour);
                GUIline(x0,y1-i,x1,y1-i,full_colour);
                GUIline(x1-i,y0,x1-i,y1,full_colour);
            }
}
/****************************************************************************
* 名称：plotC(int x,int y,int xc,int yc,unsigned char yc_colour)
* 功能：八分点画圆函数
* 入口参数：x            指定线起点所在行的位置
*           y           指定线起点所在列的位置
*          yc_color     显示颜色,根据彩色代码设定
* 出口参数：无
****************************************************************************/
void plotC(unsigned int x,unsigned int y,unsigned int xc,int yc,unsigned int yc_colour)
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
* 名称：GUI_Circle(int xc,int yc,int r,unsigned char circle_colour)
* 功能：画圆
* 入口参数：xc               圆心的行坐标
*           yc          圆心的列坐标
*           r               半径
*          circle_color     显示颜色
* 出口参数：无
****************************************************************************/
void GUIcircle(unsigned int xc,unsigned int yc,unsigned int r,unsigned int circle_colour)
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



