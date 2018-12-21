#include <msp430f169.h>
#include "Config.h"
#include "LCD.h"

unsigned long b = 0;
unsigned char c;

//unsigned int InfoB = 1000;
void main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    Clock_Init();
    FlashInit();
    port_init();
    Port_In();
    dataout;
    init();
    /*
    FlashWriteChar(InfoB,a);
    c=FlashReadChar (InfoB);        //InfoB在H文件中有宏定义
    FlashWriteWord(InfoB+2,123);
    b = FlashReadWord(InfoB+2);*/
    while(1){
        Key_Scan();                       //键盘扫描，看是否有按键按下
        if(key!=0xff)                     //如果有按键按下，则显示该按键键值1～4
        {
            {
                switch(key)
                {
                case 1:{
                    FlashWriteChar(InfoB,0x61);
                    FlashWriteWord(InfoB+2,123);
                };break;
                case 2:{
                    c=FlashReadChar(InfoB);
                    b = FlashReadWord(InfoB+2);
                };break;
                case 3:{
                    write_com(0x80);
                    display(b);
                    write_com(0x80 + 0x40);
                    write_date(c);
                };break;
                case 4:FlashErase(InfoB);break;
                }

            }

        }
        /*
        write_com(0x80);
        display(b);
        write_com(0x80 + 0x40);
        write_date(c);*/
    }
    //    FlashErase(1000);
    //    LPM0;
}
