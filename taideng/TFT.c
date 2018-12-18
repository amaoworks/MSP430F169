/*
 * TFT.c
 *
 *  Created on: 2018��12��14��
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
//  ʵ�ֹ��ܣ�   ��������
//  ���������  x0��y0 ��ʼ����
//              x1��y1 ��������
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


//��������
//Color:Ҫ���������ɫ
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
 Address_set(x,x+8-1,y,y+16-1);                    //�����ַ���ʾλ��
 for(i=0; i<16;i++) {                             //ѭ��д��16�ֽڣ�һ���ַ�Ϊ16�ֽ�
        unsigned char m=Font8x16[(c-0x20)*16+i];  //��ȡc�ַ��ĵ�i���ֽ���,c��ȥ0x20������Ascii����е�0~1f��ȥ��
        for(j=0;j<8;j++) {                        //ѭ��д��8λ��һ���ֽ�Ϊ8λ
            if((m&0x80)==0x80) {                  //�ж����λ�Ƿ�Ϊ1
                LCD_write_data(fColor);           //���λΪ1��д���ַ���ɫ
                }
            else {
                LCD_write_data(bColor);           //���λΪ0��д�뱳����ɫ
                }
            m<<=1;                                //����1λ��׼��д��һλ
            }
        }
}
//================================================================================================
//  ʵ�ֹ��ܣ�   ��ʾ16x16����
//  ���������  x ������
//              y ������
//              g ��Ҫ��ʾ���ַ�����
//              fColor �ַ���ɫ
//              bColor �ַ�������ɫ
//================================================================================================

void Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor)
{
    unsigned int i,j,k;
    Address_set(x,  x+16-1,y, y+16-1);                       //���ú�����ʾλ��
    for (k=0;k<64;k++)                                      //ѭ��64�Σ���ѯ������ģλ��
    {
      if ((ch16[k].GBK[0]==g[0])&&(ch16[k].GBK[1]==g[1]))   //�жϵ�k�����ֵı����Ƿ������뺺��g[2]���
      {
        for(i=0;i<32;i++)                                   //�����ȣ������ҵ�����ʾ��ģλ�ã�ѭ��д��32�ֽ�
        {
          unsigned short m=ch16[k].hz16[i];                 //��ȡ32�ֽ��еĵ�i�ֽ�
          for(j=0;j<8;j++)                                  //ѭ��д��8λ����
           {
             if((m&0x80)==0x80) LCD_write_data(fColor);     //�ж����λ�Ƿ�Ϊ1,���λΪ1��д���ַ���ɫ
             else              LCD_write_data(bColor);      //���λΪ0��д�뱳����ɫ
             m<<=1;                                         //����1λ��׼��д��һλ
           }
        }
      break;}
    }
}
/**********************************************************************
��������: ��ʾ����24x24
���������x ������
          y ������
          c ��Ҫ��ʾ�ĺ�����
      fColor �ַ���ɫ
          bColor �ַ�������ɫ
***********************************************************************/
void PutGB2424(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
{
    unsigned int i,j,k;
    Address_set(x,x+24-1,y, y+24-1);
    for (k=0;k<128;k++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
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
//  ʵ�ֹ��ܣ�   ��ʾ��Ӣ���ַ���
//  ���������  x ������
//              y ������
//              *s ����ʾ���ַ���,����LCD_PutString(24,16,"123��о",White,Blue);����"123��о"�ĵ�һ���ַ���ַ����ָ�����s.
//              bColor �ַ�������ɫ
//================================================================================================
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor)
{
     unsigned char l=0;                            //��ʾ��λ������
     while(*s)
     {
        if( *s < 0x80)                             //�ж�sָ����ַ����е�ĳ�ַ��ı���ֵ�Ƿ�С��128,���С��,��ΪASCII�ַ�
            {
             LCD_PutChar(x+l*8,y,*s,fColor,bColor);//��ʾ���ַ�
             s++;l++;                              //ָ���1,λ�ü�1

            }
        else
            {
             Put16x16(x+l*8,y,(unsigned char*)s,fColor,bColor);//��ʾ�ú���
             s+=2;l+=2;                                        //��Ϊ����Ϊ����Ϊ2�ֽڣ�ָ���2,��ʾ16x16����λ�ü�2
            }
     }
}
/**********************************************************************
��������:��ʾ�ַ���,������Ӣ��ͬʱ��ʾ
���������x ������
          y ������
         *s ��Ҫ��ʾ���ַ���
      fColor �ַ���ɫ
          bColor �ַ�������ɫ
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
//  ʵ�ֹ��ܣ�   ָ��λ����ʾRGB��ɫ
//  ���������  x0��y0 ��ʼ����
//              x1��y1 ��������
//              Color  ������ɫ
//================================================================================================

void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
    unsigned int i,j;
    Address_set(x0,x1,y0,y1);      //������ʾλ��
    for (i=y0;i<=y1;i++)
    {
       for (j=x0;j<=x1;j++)
           LCD_write_data(Color);
    }
}

//================================================================================================
//  ʵ�ֹ��ܣ�   ����
//  ���������  x��y ��Ҫ��������
//              color �����ɫ
//================================================================================================
void Put_pixel(unsigned int x,unsigned int y,unsigned int color)
{
    Address_set(x,x,y,y);        //���ô���������
    LCD_write_data(color);      //��ָ����д����ɫ����
}


void Show_Image(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,const unsigned char *gImage)
{
    unsigned int i,j;
    Address_set(x0,x1-1,y0,y1-1);      //������ʾλ��
    for (i=y0-y0;i<y1-y0;i++)         //��ʼλ��Ӧ�ô�0��ʼ��������ȡ����
    {
       for (j=x0-x0;j<x1-x0;j++)      //��ʼλ��Ӧ�ô�0��ʼ��������ȡ����
        //С�����ݸ�ʽ����pgm_read_byte������FLASH�ж�ȡͼ�����ݣ�ͼ��������Image2LCD�����ȡ��16λ��ɫ
       {   LCD_write_data8(gImage[i*(x1-x0)*2+j*2+1]);
           LCD_write_data8(gImage[i*(x1-x0)*2+j*2]);//ע���㷨
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
    CS_L; //��Ƭѡʹ��
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
