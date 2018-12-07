/********************************************************************
//DM430-L����Сϵͳ�����2.8��TFT������ʾ���Գ���
//ֱ�ӽ�TFT����12864�ӿڣ���Ҫ����һ����·����12864�ӿڵ�16�ŷ���һ����P53
//ע��ѡ��Һ���ĵ�Դ��λ�ڵ�λ����������ѡ5V��3.3V������Һ����ѹ����ѡ��Ĭ������Ϊ5V
//���Ի�����EW430 V5.30
//���ߣ����� www.avrgcc.com
//ʱ�䣺2013.03.09
********************************************************************/
#include <msp430f169.h>
#include "Config.h"                     //����ͷ�ļ�����Ӳ����ص��������������
//#include "Ascii_8x16.h"                 //8x16��С�ַ�
//#include "GB2424.h"                     //24x24���ش�С�ĺ���
//#include "Chinese.h"                    //16x16���ش�С�ĺ���
//#include "TFT28.h"                      //TFTͷ�ļ�
//#include "TFT28.c"                      //TFT������ʼ��������

//******************ȫ�ֱ���***************************

#define White          0xFFFF           //��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

unsigned int Device_code;               //TFT����IC�ͺţ�2.8��ΪILI9328

//**************�����ⲿ�����ͱ���********************

extern void delayms(unsigned int count);


/********************************************************************
            ��ʼ��IO���ӳ���
********************************************************************/
void Port_Init()
{
  P4SEL = 0x00;
  P4DIR = 0xFF;
  P5SEL = 0x00;
  P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;

  P3SEL=0x00;                    //����IO��Ϊ��ͨI/Oģʽ
  P3DIR = 0xff;                  //����IO�ڷ���Ϊ���
  P3OUT = 0x00;                  //��ʼ����Ϊ00,LED������IO��
}

/********************************************************************
    LED��˸һ�Σ�������Ҫ�鿴����ִ��λ��ʱ������ã����ƶϵ�
********************************************************************/
void LED_Light()
{
    LED8=0x00;                    //����LED
    delay_ms(500);
    LED8=0xff;                    //Ϩ��LED
    delay_ms(500);
}

/********************************************************************
                      ������
********************************************************************/
void main(void)
{
   uint i,y;

  WDT_Init();                        //���Ź�����
  Clock_Init();                      //ϵͳʱ������
  Port_Init();                       //ϵͳ��ʼ��������IO������
  LED_Light();                       //LED����һ�Σ���������˵����Ƭ����ʼ���ɹ�
  Device_code=0x9320;                //TFT����IC�ͺ�
  TFT_Initial();                     //��ʼ��LCD

  //while(1)                          //ѭ��ִ�г���
  // {

    CLR_Screen(Magenta);               //�ñ���ɫ����
    LCD_PutString24(0,20,"����ң�ر��ٵ��ϵͳ",Yellow,Magenta);
    delay_ms(200);
    LCD_PutString24(83,170,"����1:",Yellow,Magenta);
    delay_ms(300);
//    LCD_PutString24(107,170,"����2:",Yellow,Magenta);
//    delay_ms(300);
//    LCD_PutString24(131,170,"����3:",Yellow,Magenta);
//    delay_ms(300);
    /*LCD_PutString(69,300,"www.avrgcc.com",White,Magenta);  //�ַ���ʾ�ٷ���վ
    delay_ms(300);

    CLR_Screen(Black);                                     //�ñ���ɫ����

    for(y=0;y<10;y++)
    {
      LCD_PutString(52,y*32,"��������,����ͬ��",White,Black);      //������ʾ
      delay_ms(30);
    }
    delay_ms(300);

    CLR_Screen(Black);                                             //�ñ���ɫ����
    for(y=0;y<10;y++)
    {
      LCD_PutString(24,y*32,"�����������ӿƼ����޹�˾",White,Black);      //������ʾ
      delay_ms(30);
    }
    delay_ms(300);

    Show_RGB(0,240,0,64,Blue);                              //5����ɫ������Ϊ5������
    Show_RGB(0,240,64,128,Green);
    Show_RGB(0,240,128,192,Magenta);
    Show_RGB(0,240,192,256,Red);
    Show_RGB(0,240,256,320,Yellow);

    LCD_PutString(24,16,"�����������ӿƼ����޹�˾",White,Blue);//��1��������ʾ16x16����
    LCD_PutString(24,40,"   �����Ƽ�,����ͬ��",White,Blue);

    LCD_PutString(80,72,"0123456789",Black,Green);            //��2��������ʾascii�ַ��е����ֺͷ���
    LCD_PutString(16,96,",,`,./<>';:[]{}\|?-=+*&^%$",Black,Green);

    LCD_PutString(16,136,"abcdefghijklmnopqrstuvwxyz",Blue,Magenta);//��3��������ʾascii�ַ�����ĸ
    LCD_PutString(16,156,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",Blue,Magenta);

    LCD_PutString(16,200,"The Device IC Of TFT Is:",Black,Red);    //��4��������ʾTFT������IC�ͺ�
    LCD_PutString(96,224,"ILI",Black,Red);
    LCD_PutChar(120, 224, 0x30+(Device_code>>12), Black, Red);
    LCD_PutChar(128, 224, 0x30+((Device_code>>8)&0x000f), Black, Red);
    LCD_PutChar(136, 224, 0x30+((Device_code>>4)&0x000f), Black, Red);
    LCD_PutChar(144, 224, 0x30+(Device_code&0x000f), Black, Red);

    for(i=312;i>264;i--){ Put_pixel(68,i,Blue);}                   //��5��������ʵ�ֻ���
    for(i=68;i<172;i++) { Put_pixel(i,264,Blue);}
    for(i=264;i<312;i++){ Put_pixel(172,i,Blue);}
    for(i=172;i>68;i--) { Put_pixel(i,312,Blue);}

    delay_ms(2000);                                              //��ʾһ��ʱ��
    CLR_Screen(Red); */                                             //�ñ���ɫ����
   //}


}
