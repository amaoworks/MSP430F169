#include "msp430x16x.h"
#include "key.h"
#include "golbal.h"
#include "beep.h"
#include "led.h"
#include "process.h"

unsigned char down;   //one key is down
unsigned char other;  //not only one key down

#define NOKEY 0xFF
#define KEY_WOBBLE_TIME 500
#define KEY_OVER_TIME 1500
#define KEY_QUICK_TIME 1000

void key_init()
{
	P1DIR &= ~(BIT0+BIT1+BIT2+BIT3);
}

void key_delay(unsigned int i)
{
	while(i--);
}

/*****************************************
              按键扫描
******************************************/
unsigned char scankey()
{
	unsigned key,keytemp;
	keytemp = Key;
	key_delay(1000);
	key = Key;
	if(key==keytemp)
	{
		if(key==0x0e){return 1;} 
		else if(key==0x0d){return 2;} 
		else if(key==0x0b){return 3;} 
		else if(key==0x07){return 4;}
		else return 0; 
	}
	else 
	{
		return 0;
	}
	
/*	if(k1==0&&k2==0)		{return 12;}
	else if(k2==0&&k3==0)	{return 23;}
	else if(k1==0&&k3==0)	{return 13;}
	else if(k1==0)			{return 1;}
	else if(k2==0)			{return 2;}
	else if(k3==0)			{return 3;}
	else if(k4==0)			{return 4;}
	else return 0;
*/
}


void test_key()
{
	unsigned char keyval;
	keyval = scankey();
	switch(keyval)
	{
	case 1: {led1_ON;led2_OFF;led3_OFF;led4_OFF;beep();}break;
	case 2: {led1_OFF;led2_ON;led3_OFF;led4_OFF;beep();}break;
	case 3: {led1_OFF;led2_OFF;led3_ON;led4_OFF;beep();}break;
	case 4: {led1_OFF;led2_OFF;led3_OFF;led4_ON;beep();}break;
	}
}


//////////////////////////////////////
//键盘处理
//////////////////////////////////////
void key()
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
		up();
		renew();
	}
	else if(keyval==2&&down==0)
	{
		down = 1;
		beep();
		change();
	}
	else if(keyval==3&&down==0)
	{
		down = 1;
		beep();
		godown();
		renew();
	}
	else if(keyval==4&&other==0)
	{
		down = 1;other = 1;
		beep();
		pause();
	}
}


