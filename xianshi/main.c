/********************************************************************
//DM430-L型最小系统板控制2.8寸TFT彩屏显示测试程序
//直接将TFT插入12864接口，需要更改一条线路，将12864接口第16脚飞线一根到P53
//注意选择液晶的电源，位于电位器附近，可选5V或3.3V，根据液晶电压进行选择，默认设置为5V
//调试环境：EW430 V5.30
//作者：阿迪 www.avrgcc.com
//时间：2013.03.09
********************************************************************/
#include <msp430f169.h>
#include "Config.h"                     //配置头文件，与硬件相关的配置在这里更改
//#include "Ascii_8x16.h"                 //8x16大小字符
//#include "GB2424.h"                     //24x24像素大小的汉字
//#include "Chinese.h"                    //16x16像素大小的汉字
//#include "TFT28.h"                      //TFT头文件
//#include "TFT28.c"                      //TFT操作初始化及函数

//******************全局变量***************************

#define White          0xFFFF           //显示颜色代码
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

unsigned int Device_code;               //TFT控制IC型号，2.8寸为ILI9328

//**************声明外部函数和变量********************

extern void delayms(unsigned int count);


/********************************************************************
            初始化IO口子程序
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;

  P3SEL=0x00;                    //设置IO口为普通I/O模式
  P3DIR = 0xff;                  //设置IO口方向为输出
  P3OUT = 0x00;                  //初始设置为00,LED灯所在IO口
}

/********************************************************************
    LED闪烁一次，可在需要查看程序执行位置时灵活设置，类似断点
********************************************************************/
void LED_Light()
{
    LED8=0x00;                    //点亮LED
    delay_ms(500);
    LED8=0xff;                    //熄灭LED
    delay_ms(500);
}

/********************************************************************
                      主函数
********************************************************************/
void main(void)
{
   uint i,y;

  WDT_Init();                        //看门狗设置
  Clock_Init();                      //系统时钟设置
  Port_Init();                       //系统初始化，设置IO口属性
  LED_Light();                       //LED点亮一次，如有现象，说明单片机初始化成功
  Device_code=0x9320;                //TFT控制IC型号
  TFT_Initial();                     //初始化LCD

  //while(1)                          //循环执行程序
  // {

    CLR_Screen(Magenta);               //用背景色清屏
    LCD_PutString24(0,20,"红外遥控变速电机系统",Yellow,Magenta);
    delay_ms(200);
    LCD_PutString24(83,170,"功能1:",Yellow,Magenta);
    delay_ms(300);
//    LCD_PutString24(107,170,"功能2:",Yellow,Magenta);
//    delay_ms(300);
//    LCD_PutString24(131,170,"功能3:",Yellow,Magenta);
//    delay_ms(300);
    /*LCD_PutString(69,300,"www.avrgcc.com",White,Magenta);  //字符显示官方网站
    delay_ms(300);

    CLR_Screen(Black);                                     //用背景色清屏

    for(y=0;y<10;y++)
    {
      LCD_PutString(52,y*32,"欣创电子,与您同行",White,Black);      //汉字显示
      delay_ms(30);
    }
    delay_ms(300);

    CLR_Screen(Black);                                             //用背景色清屏
    for(y=0;y<10;y++)
    {
      LCD_PutString(24,y*32,"宁波欣创电子科技有限公司",White,Black);      //汉字显示
      delay_ms(30);
    }
    delay_ms(300);

    Show_RGB(0,240,0,64,Blue);                              //5种颜色将屏分为5个区域
    Show_RGB(0,240,64,128,Green);
    Show_RGB(0,240,128,192,Magenta);
    Show_RGB(0,240,192,256,Red);
    Show_RGB(0,240,256,320,Yellow);

    LCD_PutString(24,16,"宁波欣创电子科技有限公司",White,Blue);//第1个区域显示16x16汉字
    LCD_PutString(24,40,"   欣创科技,与您同行",White,Blue);

    LCD_PutString(80,72,"0123456789",Black,Green);            //第2个区域显示ascii字符中的数字和符号
    LCD_PutString(16,96,",,`,./<>';:[]{}\|?-=+*&^%$",Black,Green);

    LCD_PutString(16,136,"abcdefghijklmnopqrstuvwxyz",Blue,Magenta);//第3个区域显示ascii字符中字母
    LCD_PutString(16,156,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",Blue,Magenta);

    LCD_PutString(16,200,"The Device IC Of TFT Is:",Black,Red);    //第4个区域显示TFT控制器IC型号
    LCD_PutString(96,224,"ILI",Black,Red);
    LCD_PutChar(120, 224, 0x30+(Device_code>>12), Black, Red);
    LCD_PutChar(128, 224, 0x30+((Device_code>>8)&0x000f), Black, Red);
    LCD_PutChar(136, 224, 0x30+((Device_code>>4)&0x000f), Black, Red);
    LCD_PutChar(144, 224, 0x30+(Device_code&0x000f), Black, Red);

    for(i=312;i>264;i--){ Put_pixel(68,i,Blue);}                   //第5个区域打点实现画线
    for(i=68;i<172;i++) { Put_pixel(i,264,Blue);}
    for(i=264;i<312;i++){ Put_pixel(172,i,Blue);}
    for(i=172;i>68;i--) { Put_pixel(i,312,Blue);}

    delay_ms(2000);                                              //显示一段时间
    CLR_Screen(Red); */                                             //用背景色清屏
   //}


}
