#include <msp430f169.h>
#include "Config.h"
#include "I2C.h"
#include "MPU6050.h"
#include "TFT.h"
#include "Touch.h"
#include "GUI.h"
#include "TA.h"

uint Device_code;                       //TFT控制IC型号，2.8寸为ILI9320

unsigned char A1,A2,A3,A4,statu = 0,keyA = 0, keyB = 0, flag = 0;
unsigned char Temp_Value[7];
int Asecond = 0, count = 0;

/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    Clock_Init();
    MPU6050_Portinit();
    MPU6050_Init();

    Device_code=0x9320;                //TFT控制IC型号
    TFT_PortInit();
    TFT_Initial();
    start_7843();

    WakeDIR  =  0xFF;
    Wake    &= ~BIT0;
    unsigned char BUF[6];
    unsigned int  Xz, Yz, Zz;
    unsigned int retry,point = 0x700;

    CLR_Screen(Black);               //用背景色清屏
    LCD_PutString24(12,40,"防止疲劳驾驶报警器",Yellow,Black);
    GUIsquare1pix(10,37,228,65,Yellow);

    while(1){

        BUF[0]=i2c_read(0x3B);
        BUF[1]=i2c_read(0x3C);
        Xz=(BUF[0]<<8)+BUF[1];
        Xz/=16.4;
        BUF[2]=i2c_read(0x3D);
        BUF[3]=i2c_read(0x3E);
        Yz=(BUF[2]<<8)+BUF[3];
        Yz/=16.4;
        BUF[4]=i2c_read(0x3F);
        BUF[5]=i2c_read(0x4D);
        Zz=(BUF[4]<<8)+BUF[5];
        Zz/=16.4;
        retry = Zz - point;

        if(retry > 1000 && retry < 3000){
            TIMERA_Init();
            if(Asecond > 3 || flag == 1){
                Wake  |=  BIT0;
                LCD_PutString(80,160,"危险驾驶中  !!",Red,Black);
                delay_ms(100);
                LCD_PutString(80,160,"                 ",Red,Black);
                Wake  &= ~BIT0;
                statu = 1;
                flag = 1;
                TimerA_end();
            }else{}
        }else{
            if(statu == 1){
                LCD_PutString(80,160,"确认你是否清醒",Red,Black);
                GUIfull(5,280,70,310,White);
                Put16x16(32,290,"是",Black,White);
                GUIfull(170,280,235,310,White);
                Put16x16(197,290,"是",Black,White);
                while(statu == 1){
                    Wake  |=  BIT0;
                    delay_ms(50);
                    Wake  &= ~BIT0;
                    Key();
                    if(keyA == 1 && keyB == 1){
                        statu = 0;
                        GUIfull(5,280,70,310,Black);
                        GUIfull(170,280,235,310,Black);
                        keyA = 0;
                        keyB = 0;
                    }
                }
            }else{
                LCD_PutString(80,160,"正常驾驶中  :)",Yellow,Black);
                P6OUT &= ~BIT0;
                Wake  &= ~BIT0;
                flag = 0;
            }
        }
    }
}
