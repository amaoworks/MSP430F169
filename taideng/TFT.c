/*
 * TFT.c
 *
 *  Created on: 2018年12月14日
 *      Author: With-Cappuccino
 */
#include "TFT.h"
void TFT_port_init()
{
    CS_DIR_O;
    RESET_DIR_O;
    DC_DIR_O;
}
void LCD_write_command(unsigned char com)
{
    DC_L;
    spi_sendByte(com);

}
void LCD_write_data8(unsigned char data)
{
    DC_H;
    spi_sendByte(data);
}
void LCD_write_data(unsigned int data)
{
    DC_H;
    spi_sendByte(data>>8);
    spi_sendByte(data);
}
void  LCD_write_command_DATA(int reg,int da)
{
    LCD_write_command(reg);
    LCD_write_data(da);
}
//================================================================================================
//  实现功能：   设置坐标
//  输入参数：  x0，y0 起始坐标
//              x1，y1 结束坐标
//================================================================================================

void Address_set(unsigned int x1,unsigned int x2,unsigned int y1,unsigned int y2)
{
     LCD_write_command(0x2a);
   LCD_write_data8(x1>>8);
   LCD_write_data8(x1);
   LCD_write_data8(x2>>8);
   LCD_write_data8(x2);

    LCD_write_command(0x2b);
   LCD_write_data8(y1>>8);
   LCD_write_data8(y1);
   LCD_write_data8(y2>>8);
   LCD_write_data8(y2);
    LCD_write_command(0x2C);
}


//清屏函数
//Color:要清屏的填充色
void LCD_Clear(unsigned int Color)
{
    unsigned int i,j;
    Address_set(0,LCD_W-1,0,LCD_H-1);
    for(i=0;i<LCD_W;i++)
     {
      for (j=0;j<LCD_H;j++)
        {
          LCD_write_data(Color);
        }

      }
}

void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
 Address_set(x,x+8-1,y,y+16-1);                    //设置字符显示位置
 for(i=0; i<16;i++) {                             //循环写入16字节，一个字符为16字节
        unsigned char m=Font8x16[(c-0x20)*16+i];  //提取c字符的第i个字节以,c减去0x20是由于Ascii码库中的0~1f被去掉
        for(j=0;j<8;j++) {                        //循环写入8位，一个字节为8位
            if((m&0x80)==0x80) {                  //判断最高位是否为1
                LCD_write_data(fColor);           //最高位为1，写入字符颜色
                }
            else {
                LCD_write_data(bColor);           //最高位为0，写入背景颜色
                }
            m<<=1;                                //左移1位，准备写下一位
            }
        }
}
//================================================================================================
//  实现功能：   显示16x16汉字
//  输入参数：  x 横坐标
//              y 纵坐标
//              g 需要显示的字符编码
//              fColor 字符颜色
//              bColor 字符背景颜色
//================================================================================================

void Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor)
{
    unsigned int i,j,k;
    Address_set(x,  x+16-1,y, y+16-1);                       //设置汉字显示位置
    for (k=0;k<64;k++)                                      //循环64次，查询汉字字模位置
    {
      if ((ch16[k].GBK[0]==g[0])&&(ch16[k].GBK[1]==g[1]))   //判断第k个汉字的编码是否与输入汉字g[2]相等
      {
        for(i=0;i<32;i++)                                   //如果相等，既已找到待显示字模位置，循环写入32字节
        {
          unsigned short m=ch16[k].hz16[i];                 //读取32字节中的第i字节
          for(j=0;j<8;j++)                                  //循环写入8位数据
           {
             if((m&0x80)==0x80) LCD_write_data(fColor);     //判断最高位是否为1,最高位为1，写入字符颜色
             else              LCD_write_data(bColor);      //最高位为0，写入背景颜色
             m<<=1;                                         //左移1位，准备写下一位
           }
        }
      break;}
    }
}
/**********************************************************************
函数功能: 显示汉字24x24
输入参数：x 横坐标
          y 纵坐标
          c 需要显示的汉字码
      fColor 字符颜色
          bColor 字符背景颜色
***********************************************************************/
void PutGB2424(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
{
    unsigned int i,j,k;
    Address_set(x,x+24-1,y, y+24-1);
    for (k=0;k<128;k++) { //64表示自建汉字库中的个数，循环查询内码
      if ((codeGB_24[k].Index[0]==c[0])&&(codeGB_24[k].Index[1]==c[1])){
        for(i=0;i<72;i++) {
          unsigned short m=codeGB_24[k].Msk[i];
          for(j=0;j<8;j++) {
            if((m&0x80)==0x80) {
                LCD_write_data(fColor);
                }
            else {
                LCD_write_data(bColor);
                }
            m<<=1;
            }
          }
        break;}
      }
}
//================================================================================================
//  实现功能：   显示中英文字符串
//  输入参数：  x 横坐标
//              y 纵坐标
//              *s 待显示的字符串,例如LCD_PutString(24,16,"123蓝芯",White,Blue);即把"123蓝芯"的第一个字符地址赋给指针变量s.
//              bColor 字符背景颜色
//================================================================================================
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor)
{
     unsigned char l=0;                            //显示屏位置增量
     while(*s)
     {
        if( *s < 0x80)                             //判断s指向的字符串中的某字符的编码值是否小于128,如果小于,即为ASCII字符
            {
             LCD_PutChar(x+l*8,y,*s,fColor,bColor);//显示该字符
             s++;l++;                              //指针加1,位置加1

            }
        else
            {
             Put16x16(x+l*8,y,(unsigned char*)s,fColor,bColor);//显示该汉字
             s+=2;l+=2;                                        //因为汉字为编码为2字节，指针加2,显示16x16所以位置加2
            }
     }
}
/**********************************************************************
函数功能:显示字符串,可以中英文同时显示
输入参数：x 横坐标
          y 纵坐标
         *s 需要显示的字符串
      fColor 字符颜色
          bColor 字符背景颜色
***********************************************************************/
void LCD_PutString24(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor)
{
     unsigned char l=0,pos;
     pos=x;
    while(*s) {
        if( *s < 0x80)
            {
            LCD_PutChar(x,y,*s,fColor,bColor);
            s++;l++;
            x=l*8+pos;
            }
        else
            {
            PutGB2424(x,y,(unsigned char*)s,fColor,bColor);
            s+=2;l+=3;
            x=l*8+pos;
            }

        }
    }
//================================================================================================
//  实现功能：   指定位置显示RGB颜色
//  输入参数：  x0，y0 起始坐标
//              x1，y1 结束坐标
//              Color  背景颜色
//================================================================================================

void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
    unsigned int i,j;
    Address_set(x0,x1,y0,y1);      //设置显示位置
    for (i=y0;i<=y1;i++)
    {
       for (j=x0;j<=x1;j++)
           LCD_write_data(Color);
    }
}

//================================================================================================
//  实现功能：   画点
//  输入参数：  x，y 需要画点坐标
//              color 点的颜色
//================================================================================================
void Put_pixel(unsigned int x,unsigned int y,unsigned int color)
{
    Address_set(x,x,y,y);        //设置待画点坐标
    LCD_write_data(color);      //在指定点写入颜色数据
}


void Show_Image(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,const unsigned char *gImage)
{
    unsigned int i,j;
    Address_set(x0,x1-1,y0,y1-1);      //设置显示位置
    for (i=y0-y0;i<y1-y0;i++)         //起始位置应该从0开始，便于提取数据
    {
       for (j=x0-x0;j<x1-x0;j++)      //起始位置应该从0开始，便于提取数据
        //小端数据格式，用pgm_read_byte函数从FLASH中读取图像数据，图像数据用Image2LCD软件提取，16位彩色
       {   LCD_write_data8(gImage[i*(x1-x0)*2+j*2+1]);
           LCD_write_data8(gImage[i*(x1-x0)*2+j*2]);//注意算法
       }
    }
}

void TFT_init()
{
    CS_H;
    RESET_L ;
    delay_ms(20);
    RESET_H;
    delay_ms(20);
    CS_L; //打开片选使能
    LCD_write_command(0xCF);
    LCD_write_data8(0x00);
    LCD_write_data8(0xD9);
    LCD_write_data8(0X30);
    LCD_write_command(0xED);
    LCD_write_data8(0x64);
    LCD_write_data8(0x03);
    LCD_write_data8(0X12);
    LCD_write_data8(0X81);

    LCD_write_command(0xE8);
    LCD_write_data8(0x85);
    LCD_write_data8(0x10);
    LCD_write_data8(0x78);

    LCD_write_command(0xCB);
    LCD_write_data8(0x39);
    LCD_write_data8(0x2C);
    LCD_write_data8(0x00);
    LCD_write_data8(0x34);
    LCD_write_data8(0x02);

    LCD_write_command(0xF7);
    LCD_write_data8(0x20);

    LCD_write_command(0xEA);
    LCD_write_data8(0x00);
    LCD_write_data8(0x00);

    LCD_write_command(0xC0);    //Power control
    LCD_write_data8(0x21);   //VRH[5:0]

    LCD_write_command(0xC1);    //Power control
    LCD_write_data8(0x12);   //SAP[2:0];BT[3:0]

    LCD_write_command(0xC5);    //VCM control
    LCD_write_data8(0x32);
    LCD_write_data8(0x3C);

    LCD_write_command(0xC7);    //VCM control2
    LCD_write_data8(0XC1);

    LCD_write_command(0x36);    // Memory Access Control
    LCD_write_data8(0x08);

    LCD_write_command(0x3A);
    LCD_write_data8(0x55);

    LCD_write_command(0xB1);
    LCD_write_data8(0x00);
    LCD_write_data8(0x18);

    LCD_write_command(0xB6);    // Display Function Control
    LCD_write_data8(0x0A);
    LCD_write_data8(0xA2);



    LCD_write_command(0xF2);    // 3Gamma Function Disable
    LCD_write_data8(0x00);

    LCD_write_command(0x26);    //Gamma curve selected
    LCD_write_data8(0x01);

    LCD_write_command(0xE0);    //Set Gamma
    LCD_write_data8(0x0F);
    LCD_write_data8(0x20);
    LCD_write_data8(0x1E);
    LCD_write_data8(0x09);
    LCD_write_data8(0x12);
    LCD_write_data8(0x0B);
    LCD_write_data8(0x50);
    LCD_write_data8(0XBA);
    LCD_write_data8(0x44);
    LCD_write_data8(0x09);
    LCD_write_data8(0x14);
    LCD_write_data8(0x05);
    LCD_write_data8(0x23);
    LCD_write_data8(0x21);
    LCD_write_data8(0x00);

    LCD_write_command(0XE1);    //Set Gamma
    LCD_write_data8(0x00);
    LCD_write_data8(0x19);
    LCD_write_data8(0x19);
    LCD_write_data8(0x00);
    LCD_write_data8(0x12);
    LCD_write_data8(0x07);
    LCD_write_data8(0x2D);
    LCD_write_data8(0x28);
    LCD_write_data8(0x3F);
    LCD_write_data8(0x02);
    LCD_write_data8(0x0A);
    LCD_write_data8(0x08);
    LCD_write_data8(0x25);
    LCD_write_data8(0x2D);
    LCD_write_data8(0x0F);

    LCD_write_command(0x11);    //Exit Sleep
    delay_ms(120);
    LCD_write_command(0x29);    //Display on
}
