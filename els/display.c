#include "golbal.h"
#include "display.h"

//-------------------------------------------------------------------------------------------------------------------------------------
/*************************************                              
       use SPI send byte
**************************************/
void send(unsigned char dat,unsigned char command)
{
	unsigned char i;
	NOKIA5110_CE_L;
	if(command==0)
		NOKIA5110_DC_L;//浼犻�佸懡浠�
	else
		NOKIA5110_DC_H;	//浼犻�佹暟鎹�
	for(i=0;i<8;i++)
	{
		if(dat&0x80)
			NOKIA5110_DIN_H;
		else
			NOKIA5110_DIN_L;
		NOKIA5110_CLK_L;
		dat=dat<<1;
		NOKIA5110_CLK_H;
	}
	NOKIA5110_CE_H;
	
/*	unsigned char i;
	CE_L;
	dc = command;
	sclk = 0;
	for(i=0;i<8;i++)
	{
		if(dat&(0x80>>i))	{sdin=1;}
		else				{sdin=0;}
		sclk=1;
		sclk=0;
	}
	sce=1;// free the SPI
*/
}

/*******************************************
        lcd clear
********************************************/
void lcd_clear()
{
	unsigned char i,j;
	send(0x0c,0);//璁惧畾鏄剧ず妯″紡锛屾甯告樉绀�	
	send(0x80,0);//璁剧疆RAM璧峰鍦板潃
	for(j=0;j<6;j++)
	{
		for(i=0;i<84;i++)
		{
			send(0,1);
		}
	}
}

/*******************************************
                lcd鍒濆鍖�
********************************************/
void lcd_init()
{
	unsigned char i;
	P5DIR |= BIT0+BIT1+BIT2+BIT3+BIT4+BIT5;
	NOKIA5110_RST_L;//浜х敓涓�涓LCD澶嶄綅鐨勪綆鐢靛钩鑴夊啿
	for(i=0;i<50;i++)
	{
		_NOP();
		_NOP();
		_NOP();
	}
	NOKIA5110_RST_H;

	send(0x21,0);//浣跨敤鎵╁睍鍛戒护璁剧疆LCD妯″紡chip is active & horizontal addressing (H=1)
	send(0xc0,0);//璁剧疆VOP鍊碱柌lcd 鐢靛帇
	send(0x20,0);//浣跨敤鍩烘湰鍛戒护,姘村钩瀵诲潃                                       (H=0)
	send(0x0c,0);//璁惧畾鏄剧ず妯″紡锛屾甯告樉绀篸isplay in normal mode
	lcd_clear();
	NOKIA5110_LED_ON;
}
/********************************************
           set_XY
*********************************************/
void set_xy(unsigned char x,unsigned char y)
{
	send(0x20,0);//H=0
	send(0x80|x,0);//x-0 to 83
	send(0x40|y,0);//y-0 to 5
}

/*********************************************
       display a font6*8
*********************************************/
void write_char(unsigned char c)
{
	unsigned char line;
	c-=32;
	for(line=0;line<6;line++)
	send(font6x8[c][line],1);
}
/********************************************
    display a chinese (cut into two parts)
**********************************************/
void write(unsigned char a,unsigned char b,unsigned char add)//a=01234,b=012345,add=0123456
{
	unsigned char c; 
	set_xy(a*16,b); 
	for(c=0;c<16;c++) 
	{ 			
		send(han[add*32+c],1); 
	} 
	set_xy(a*16, b+1);
	for(c=16;c<32;c++) 
	{ 			
		send(han[add*32+c],1); 
	}
}
/*********************************************
             display shuzi_8x16
**********************************************/
void writeshuzi(unsigned char a,unsigned char b,unsigned char add)
{
	unsigned char c; 
	set_xy(a*8,b); 
	for(c=0;c<8;c++) 
	{ 			
		send(shuzi[add*16+c],1); 
	} 
    set_xy(a*8, b+1);
	for(c=8;c<16;c++) 
	{ 			
		send(shuzi[add*16+c],1); 
	}  
}
/*********************************************
        鑻辨枃瀛楃涓叉樉绀哄嚱鏁�
**********************************************/
void write_string(unsigned char x,unsigned char y,unsigned char *p)
{
	set_xy(x,y);
	while(*p)
	{
		write_char(*p);
		p++;
	}
}
