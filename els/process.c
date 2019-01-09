#include "msp430x16x.h"
#include "display.h"
#include "key.h"
#include "golbal.h"
#include "process.h"
#include "beep.h"

unsigned char background[3][58];//鑳屾櫙鐭╅樀
unsigned char new[3][58];//
unsigned int step=0;

unsigned char fangkuai[8];//鏂瑰潡
unsigned char front[3][8];//娑傚眰鐭╅樀
unsigned char fronttemp[3][8];

unsigned char front_x = 66;//娑傚眰鍓嶇x鍧愭爣
unsigned char guan=1;//褰撳墠鐨勫叧鏁�
unsigned int score=0;//褰撳墠鐨勫緱鍒�
unsigned char bianhuan=1;
unsigned char moved=10;//涓婁笅绉诲姩璁板綍

unsigned char fknow;//褰撳墠浠庢柟鍧楃洅瀛愰噷鍙栫殑鏂瑰潡鐨勭紪鍙�
unsigned char fknext;//涓嬩竴涓粠鏂瑰潡鐩掑瓙閲屽彇鐨勬柟鍧楃紪鍙�


//-------------------------------------------------------------------------------------------------------------------------------------
/**********************************************                              
                娆㈣繋灞忓箷
**********************************************/
void delay(unsigned char l)
{
	unsigned char i;unsigned int j;
	for(i=0;i<l;i++)
	{
		for(j=0;j<6000;j++);
	}
}

/*-----------display head bmp--------------*/
void disandroid()
{
	unsigned char i,j;
	NOKIA5110_LED_ON;
	set_xy(0,0);
	for(i=0;i<6;i++)
	{
		for(j=0;j<84;j++)
		{											
			send(android[i][j],1);
		}
	}
}
void disnokia()
{
	unsigned char i,j;
	NOKIA5110_LED_ON;
	set_xy(0,0);
	for(i=0;i<6;i++)
	{
		for(j=0;j<84;j++)
		{											
			send(nokia[i][j],1);
		}
	}
}
void welcome()
{
	disnokia();
	delay(60);
	disandroid();
	while(scankey()==0);

	lcd_clear();
	write(0,0,0); //鍐欌�滀縿缃楁柉鏂瑰潡鈥�
	write(1,0,1);
	write(2,0,2);
	write(3,0,3);
	write(4,0,4);
//	write_string(0,2,"Designed by...");delay(6);NOKIA5110_LED_OFF;
//	write_string(0,3,"Juring--");delay(4);NOKIA5110_LED_ON;
	write_string(0,4,"press any key to start...");
	while(scankey()==0);
	lcd_clear();
}


/********************************************** 
              鍒掑垎灞忓箷鍖哄煙
**********************************************/
void ping()
{
	write(0,0,5);//绗�
	write(0,4,6);//鍏�
	write_string(18,0,"step:");
	write_string(19,4,"SCORE:");
	write_string(17,5,"pause k1+k2");
	set_xy(74,1);
	send(0xff,1);
	set_xy(74,2);
	send(0xff,1);
	set_xy(74,3);
	send(0xff,1);
}

/********************************************** 
              鑳屾櫙 new 璧嬪垵鍊�
**********************************************/
void bg_init()
{
	unsigned char i,j;
	for(j=0;j<3;j++)
	{
	for(i=0;i<58;i++)
	{
		background[j][i]=0;
	}
	}
	for(j=0;j<3;j++)
	{
		background[j][1]=0xff;
	}   
}

/********************************************** 
          浠庢柟鍧楃洅瀛恌k[][]閲屽彇鏂瑰潡鏂瑰潡
**********************************************/
void create()
{
	unsigned char i;
	fknow = suijishu;
	for(i=0;i<8;i++)
	{
		fangkuai[i]=fk[4*fknow][i];
	}
	fknext = fknow;
}

/******************************************************
              鎶婂彇鍑虹殑鏂瑰潡瑁呭叆front[1]閲岄潰
******************************************************/
void load()
{
	unsigned char i,j;
	for(i=0;i<3;i++)
	{
	  for(j=0;j<8;j++)
	  {
	    front[i][j] = 0;   //front[][]娓呴浂
	  }
	}
	for(i=0;i<8;i++)
	{
		front[1][i] = fangkuai[i];	//front[1][]瑁呭叆鐢熸垚鐨勬柟鍧�
	}
}

/*****************************************************
                   	鏂瑰潡鍒濆鍖�
******************************************************/
void fangkuai_init()
{
	unsigned char i;
	load();
	fknow = fknext;
	fknext = suijishu;
	for(i=0;i<8;i++)
	{
		fangkuai[i] = fk[4*fknext][i];
	}

	set_xy(75,1);// display the next fangkuai
	for(i=0;i<8;i++)
	{
		send(fangkuai[i],1);
	}
}

/*****************************************************
  鍒锋柊娓告垙鍖哄睆骞曪紙鎶婃妸front[3][8]鏀捐繘new[3][58]閲岄潰锛�
******************************************************/
void renew()
{
	unsigned char i;
	unsigned char j;
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	//////new=background then front鍚堝苟杩沶ew///////
	for(j=0;j<3;j++)
	{
		for(i=0;i<58;i++)
		{
			new[j][i] = background[j][i];
		}
	}

	for(j=0;j<3;j++)//鎶奻ront[3][8]鏀捐繘new[3][58]閲岄潰
	{
		for(i=0;i<8;i++)
		{
			new[j][front_x+i-16] |= front[j][i];
		}
	}
	  
	for(j=3;j>0;j--)//鏄剧ずnew
	{
		set_xy(16,j);
		for(i=0;i<58;i++)
		{
			send(new[j-1][i],1);
		}
	} 
	TBCTL |= MC_1; //鎭㈠涓嬮檷璁℃椂
}

/*****************************************************
                  鏄剧ず寰楀垎
******************************************************/
void disscore()
{
	unsigned char i,j,line;
	unsigned char shu[4];
	shu[0] = (score%10000)/1000;//鍗冧綅
	shu[1] = (score%1000)/100;	//鐧句綅
	shu[2] = (score%100)/10;	//鍗佷綅
	shu[3] = score%10;			//涓綅

	for(j=0;j<3;j++){
	    Uart0Send_Byte(shu[i]);
	}

	set_xy(55,4);
	for(i=0;i<4;i++)
	{
		for(line=0;line<6;line++)
		{
			send(font6x8[shu[i]+16][line],1);
		}
	}
}

/*****************************************************
                  鏄剧ず鍏虫暟
******************************************************/
void disguan()
{
	writeshuzi(0,2,guan/10);
	writeshuzi(1,2,guan%10);
}

/*****************************************************
                  鏄剧ずstep
******************************************************/
void disstep()
{
	unsigned char i,line;
	unsigned char shu[5];
	step += 1;
	shu[0] = step/10000;
	shu[1] = (step%10000)/1000;
	shu[2] =(step%1000)/100;
	shu[3] = (step%100)/10;
	shu[4] = step%10;
	set_xy(48,0);
	for(i=0;i<5;i++)
	{
		for(line=0;line<6;line++)
		{
			send(font6x8[shu[i]+16][line],1);
		}
	}
}

/*****************************************************
                  鏄剧ずGAME OVER
******************************************************/
void disover()
{
	lcd_clear();
	write_string(15,2,"GAME OVER");
	write_string(0,4,"press k3 to...start new game");
	while(scankey()!=3)
	{}
}

/*****************************************************
                  鏆傚仠
******************************************************/
void pause()
{
	unsigned char i;
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	lcd_clear();
	write_string(12,0,"PAUSE...");
	write_string(0,2,"K1 LED switch");
	write_string(0,3,"k2 BEEP switch");
	write_string(0,4,"k3 continue");
	while(1)
	{
		unsigned char keyval;
		keyval = scankey();
		if(keyval==0)
		{
			down = 0;
			other = 0;
		}
		else if(keyval==1&&down==0)
		{
			down = 1;
			beep();
			P3OUT^=BIT5;
		}
		else if(keyval==2&&down==0)
		{
			down = 1;
			beep();
			if(beep2==0) 
			{
				beep2 = 1;write_string(0,5,"   beep on  ");
			}
			else
			{
				beep2 = 0;write_string(0,5,"   beep off  ");
			}
		}
		else if(keyval==3&&down==0)
		{
			down = 1;
			beep();
			lcd_clear();
			ping();
			disguan();
			disscore();
			disstep();
			TBCTL |= MC_1;
			set_xy(75,1);
			for(i=0;i<8;i++)
			{
				send(fangkuai[i],1);
			}
			renew();
			break;
		}
	}
}

/*****************************************************
                  鏄剧ず杩囧叧鐢婚潰
******************************************************/
void disguoguan()
{
	unsigned char i;
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	lcd_clear();
	write_string(15,1,"GOOD GAME");
	write_string(18,3,"HAVE FUN");
	write_string(15,5,"GOOD LUCK");
	for(i=0;i<5;i++)
	{ 
		delay(2);
		beep();beep();beep();
		delay(2);
	}	  
	lcd_clear();
	ping();
	disguan();
	disscore();
	disstep();
	TBCTL |= MC_1;
	set_xy(75,1);
	for(i=0;i<8;i++)
	{
		send(fangkuai[i],1);
	}
	renew();
}

/*****************************************************
front鍜宐ackground浣滀笌杩愮畻
鍙傛暟x涓篵ackground鐨勫弬涓庤繍绠椾綅缃�
杩斿洖鍊� 1鍏佽绉诲姩 0鍒拌竟鐣�
*****************************************************/
unsigned char allow(unsigned char x)
{
	unsigned char i,j,k;
	for(j=0;j<3;j++)
	{
		for(i=0;i<8;i++)
		{
			k = fronttemp[j][i]&background[j][x+i-16];
			if(k!=0)	return 0;
		}
	}
	return 1;
}
//鐩存帴鐢╢ront
unsigned char allow2(unsigned char x)
{
	unsigned char i,j,k;
	for(j=0;j<3;j++)
	{
		for(i=0;i<8;i++)
		{
			k = front[j][i]&background[j][x+i-16];
			if(k!=0)	return 0;
		}
	}
	return 1;
}

/*****************************************************
					涓婄Щ
*****************************************************/
void up()
{
	unsigned char i,j;
	unsigned char k;
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	for(i=0;i<8;i++)
	{
		if(front[0][i]&1)//濡傛灉front[0]涓虹┖鐧斤紝鍒欏彲浠ユ妸鏂瑰潡宸︾Щ
		{
			k = 0;	break;
		}
		k = 1;
	}
	if(k==1)
	{
		for(i=0;i<2;i++)
		{
			for(j=0;j<8;j++)
			{
				fronttemp[i][j] = (front[i][j]>>2)|(front[i+1][j]<<6);
			}
		}
		for(j=0;j<8;j++)
		{
			fronttemp[2][j]=front[2][j]>>2;
		}
		if(allow(front_x))
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<8;j++)
				{
					front[i][j]=fronttemp[i][j];
				}
			}
			moved -= 1;
			disstep();
		}
	}
	TBCTL |= MC_1;
}

/*****************************************************
					涓嬬Щ
*****************************************************/
void godown()
{
	unsigned char i,j;
	unsigned char k;
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	for(i=0;i<8;i++)
	{
		if(front[2][i]&0x80)
		{
			k = 0;break;
		}
		k = 1;
	}
	if(k==1)
	{
		for(i=2;i>0;i--)
		{
			for(j=0;j<8;j++)
			{
				fronttemp[i][j]=(front[i][j]<<2)|(front[i-1][j]>>6);
			}
		}
		for(j=0;j<8;j++)
		{
			fronttemp[0][j]=front[0][j]<<2;
		}
		if(allow(front_x))
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<8;j++)
				{
					front[i][j]=fronttemp[i][j];
				}
			}
		moved += 1;
		disstep();
		}
	}
	TBCTL |= MC_1;
}
//////////////////////////////////////////////////
//move up 鍜屼笂绉讳竴鏍� 鍙皯浜� moved-=1;
///////////////////////////////////////////////////
void move_up()
{
	unsigned char i,j;
	unsigned char k;
	for(i=0;i<8;i++)
	{
		if(front[0][i]&1)
		{
			k=0;break;
		}
	k=1;
	}
	if(k==1)
	{
		for(i=0;i<2;i++)
		{
			for(j=0;j<8;j++)
			{
				fronttemp[i][j]=(front[i][j]>>2)|(front[i+1][j]<<6);
			}
		}
		for(j=0;j<8;j++)
		{
			fronttemp[2][j]=front[2][j]>>2;
		}
		for(i=0;i<3;i++)
		{
			for(j=0;j<8;j++)
			{
				front[i][j]=fronttemp[i][j];
			}
		}
	}
}
///////////////////////////////////////////////////
//move down 鍜屼笅绉讳竴鏍� 鍙皯浜� moved+=1;
///////////////////////////////////////////////////
void move_down()
{
	unsigned char i,j;
	unsigned char k;
	for(i=0;i<8;i++)
	{
		if(front[2][i]&0x80)
		{
			k=0;break;
		}
		k=1;
	}
	if(k==1)
	{
		for(i=2;i>0;i--)
		{
			for(j=0;j<8;j++)
			{
				fronttemp[i][j]=(front[i][j]<<2)|(front[i-1][j]>>6);
			}
		}
		for(j=0;j<8;j++)
		{
			fronttemp[0][j]=front[0][j]<<2;
		}
		for(i=0;i<3;i++)
		{
			for(j=0;j<8;j++)
			{
				front[i][j]=fronttemp[i][j];
			}
		}
	}
}

/*****************************************************
						鎹㈠悜
*****************************************************/
void change()
{
	unsigned char i,j,temp[8];
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	for(i=0;i<8;i++)
	{
		temp[i] = fk[4*fknow+bianhuan][i];
	}
	bianhuan++;
	if(bianhuan==4){bianhuan=0;}
	//load temp as fangkuai
	for(i=0;i<3;i++)
	{
		for(j=0;j<8;j++)
		{
			front[i][j] = 0;
		}
	}
	for(i=0;i<8;i++)
	{
		front[1][i] = temp[i];
	}
	//move to where it is before  
	if(moved<10)
	{
		for(i=0;i<(10-moved);i++)
		{
			move_up();
		}
	}
	else if (moved>10)
	{
		for(i=0;i<(moved-10);i++)
		{
			move_down();
		}
	}
	renew();
	TBCTL |= MC_1;
}

/*****************************************************
				鐢卞畾鏃跺櫒鎺у埗娑傚眰涓嬮檷
*****************************************************/
void move()
{
	if(allow2(front_x-2))
	{
		front_x -= 2;
		disstep();
		renew();
	}
	else
	{
		win();
	}
}

/*****************************************************
				娑堝眰
*****************************************************/
void cut1(unsigned char i,unsigned char j)
{
	unsigned char k;
	for(k=j;k<(56-j);k++)
	{
		background[i][k] = background[i][k+2];
	}
}
void cut(unsigned char j)
{
	unsigned char i;
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	for(i=0;i<3;i++)
	{
		cut1(i,j);
	}
	for(i=0;i<3;i++)
	{
		background[i][56] = 0;
		background[i][57] = 0;
	}
	TBCTL |= MC_1;
}

/*****************************************************
				    GAME OVER                   
*****************************************************/
void game_over()
{
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	disover();
	lcd_clear();
	ping();
	bg_init(); 
	create();
	fangkuai_init();
	renew();
	score = 0;
	guan = 1;
	step = 0;
	speed = 16;
	disscore();
	disguan();
	TBCTL |= MC_1;
}

/*****************************************************
				    寰楀垎鍒ゆ柇
*****************************************************/
//娑堝眰鐨勬椂鍊欏姞鍒嗭紝榛樿涓�琛�20锛�
//榛樿100鍒嗚繃鍏�
void xiao()
{
	unsigned char i,j,k,l;
	for(i=2;i<58;i++)
	{
		l = 0;
		for(j=0;j<3;j++)
		{
			k = background[j][i]&0xff;
			if(k==0xff) l+=1;
		}
		if(l==3) 
		{
			cut(i);
			score+=20;
			disscore();
			if(score%100==0)
			{
				guan+=1;
				disguoguan();
				if((speed-2)>1)
				{
					speed -= 2;
				}
				disguan();
			}
		}
	}
}
void win()
{
	//////////front鍚堝苟杩沚ackground///////////
	unsigned char i,j;
	TBCTL &= ~(MC0 + MC1);    //鏆傚仠涓嬮檷
	for(j=0;j<3;j++)
	{
		for(i=0;i<8;i++)
		{
			background[j][front_x+i-16] |= front[j][i];
		}
	}
	xiao();
	xiao();
	if(front_x==66)
	{
		game_over();
	}
	front_x = 66;
	ping();
	fangkuai_init();
	moved = 10;
	TBCTL |= MC_1;
	renew();
}

