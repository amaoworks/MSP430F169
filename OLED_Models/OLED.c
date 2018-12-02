/*
 * OLED.c
 *
 *  Created on: 2018年11月16日
 *      Author: myy12
 */

#include"OLED.h"
//#include "OLED_Font.h"
void writeOLED_D(unsigned char dat){
    IICWrite(0x40,dat);
}

void writeOLED_C(unsigned char com){
    IICWrite(0x00,com);
}



void OLED_init(){
    IIC_init(0x78);

    writeOLED_C(0x40);//---set low column address
    writeOLED_C(0xB0);//---set high column address

    writeOLED_C(0xC8);//-not offset

    writeOLED_C(0x81);//设置对比度
    writeOLED_C(0xff);

    writeOLED_C(0xa1);//段重定向设置

    writeOLED_C(0xa6);//

    writeOLED_C(0xa8);//设置驱动路数
    writeOLED_C(0x1f);

    writeOLED_C(0xd3);
    writeOLED_C(0x00);

    writeOLED_C(0xd5);
    writeOLED_C(0xf0);

    writeOLED_C(0xd9);
    writeOLED_C(0x22);

    writeOLED_C(0xda);
    writeOLED_C(0x02);

    writeOLED_C(0xdb);
    writeOLED_C(0x49);

    writeOLED_C(0x8d);
    writeOLED_C(0x14);

    writeOLED_C(0xaf);

}

void clearOLED(){
    unsigned char i,j;
    for(i=0;i<8;i++){
        writeOLED_C(0xb0+i);
        writeOLED_C(0x00);
        writeOLED_C(0x10);
        for(j=0;j<128;j++){
            writeOLED_D(0);
        }
    }
}

void OLED_SetPos(unsigned char x,unsigned char y){
    writeOLED_C(0xb0+y);
    writeOLED_C(((x&0xf0)>>4)|0x10);
    writeOLED_C((x&0x0f));
}

void fill_picture(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        writeOLED_C(0xb0+m);     //page0-page1
        writeOLED_C(0x00);       //low column start address
        writeOLED_C(0x10);       //high column start address
        for(n=0;n<128;n++)
            {
                writeOLED_D(fill_Data++);
            }
    }
}
// 定向清理
void NewClear(unsigned char x){
    unsigned char i,j,y,z;
    switch(x){
    case 1:{i=y=0; j=z=0;}break;
    case 2:{i=y=0; j=z=64;}break;
    case 3:{i=y=4; j=z=0;}break;
    case 4:{i=y=4; j=z=64;}break;
    }
    for(;i<(y+4);i++){
        writeOLED_C(0xb0+i);
        writeOLED_C(0x00);
        writeOLED_C(0x10);
        for(j=z;j<(z+64);j++){
            writeOLED_D(0);
        }
    }
}
// 显示汉字
void OLED_DisplayF(unsigned char x, unsigned char y, unsigned char no){
    unsigned char t,adder;
    OLED_SetPos(x,y);
    for(t=0;t<16;t++)
        {
            writeOLED_D(Font[2*no][t]);
            //adder+=1;
        }
    OLED_SetPos(x,y+1);
    for(t=0;t<16;t++)
        {
            writeOLED_D(Font[2*no+1][t]);
            //adder+=1;
        }
}
//显示8x8
void OLED_DisplayF8(unsigned char x, unsigned char y, unsigned char no){
    unsigned char t;
    OLED_SetPos(x,y);
    for(t=0;t<8;t++)
        {
            writeOLED_D(F8x8[no][t]);
            //adder+=1;
        }
/*    OLED_SetPos(x,y+1);
    for(t=0;t<16;t++)
        {
            writeOLED_D(Font[2*no+1][t]);
            //adder+=1;
        }*/
}
//显示字符
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char chr){
    unsigned char c=0, i=0;
    c = chr - ' ';//得到偏移后的值
    if(x>127){x=0;y=y+2;}
    OLED_SetPos(x,y);
    for(i=0;i<8;i++)
    writeOLED_D(NumF[c*16+i]);
    OLED_SetPos(x,y+1);
    for(i=0;i<8;i++)
    writeOLED_D(NumF[c*16+i+8]);
/*        else {
            OLED_SetPos(x,y);
            for(i=0;i<6;i++)
            writeOLED_D(NumF[c][i]);
        }*/
}
//m^n函数
unsigned int oled_pow(unsigned char m,unsigned char n)
{
    unsigned int result=1;
    while(n--)result*=m;
    return result;
}
//显示数字
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len)
{
    unsigned char t,temp;
    unsigned char enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+8*t,y,' ');
                continue;
            }else enshow=1;

        }
        OLED_ShowChar(x+8*t,y,temp+'0');
    }
}
