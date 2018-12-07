#include <msp430f169.h>
#include "Config.h"
#include "Touch.h"
#include "qqpic.h"
//#include "TFT.h"
//#include "GUI.h"

uint Device_code;      //TFT����IC�ͺţ��°�2.8��ΪILI9320

static uchar Flag=0;                    //��־����
uint TEMP=0;                            //ADCֵ�ݴ����
static uint Precent=0;                  //����Ϊ��̬����Ҫ��Ϊ�˱�����һ�β���ֵ
uint count;
uint yback=0;                           //���ڴ��ǰһ�εĵ�ѹ��ʾ���Y����
//**************�����ⲿ�����ͱ���********************
extern void delayms(uint count);

/********************************************************************
            ��ʼ��IO���ӳ���
 ********************************************************************/
void Port_Init()
{
    P4SEL = 0x00;
    P4DIR = 0xFF;                                     //TFT���ݿ�
    P5SEL = 0x00;
    P5DIR|= BIT0 + BIT1 + BIT3 + BIT5 + BIT6 + BIT7;  //TFT��ʾ������
}

//*************************************************************************
//  ADC��ʼ��������������ADC��ؼĴ���
//*************************************************************************
void ADC_Init()
{
    P6SEL|=0x01;                                    //ѡ��ADCͨ�������ö�ӦIO�ڵĹ���ģʽ
    ADC12CTL0|= ADC12ON + SHT0_2 + REF2_5V + REFON; //ADC��Դ���ƿ���16��CLK���ڲ���׼2.5V
    ADC12CTL1|= ADC12SSEL1 + ADC12SSEL0;            //SMCLK��ʱ��Դ
    ADC12MCTL0= SREF0 + INCH_0;                     //�ο�����λ��ͨ��ѡ��
    ADC12IE|= 0x01;                                 //�ж�����
    ADC12CTL0|= ENC;                                //ʹ��ת����
}
//*************************************************************************
//      ��ѹ���ݴ�����
//*************************************************************************
void Data_do(uint temp_d)
{
    ulong temp_3;
    temp_3=(ulong)(temp_d)*100;            //ת����ʽ��ADC������ת��Ϊ��ѹ��С��ע����������
    Precent = temp_3/0xFFF;                //����ٷֱ�

}
//*************************************************************************
//  ADC�жϷ������
//*************************************************************************
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
//    uchar j;
    yback=190-(1.50*Precent);             //Ϊ�˲���ƽ����Ҫ����ǰһ�β���ֵ��Ӧ�������
    while((ADC12CTL1&0x01)==1);           //���ADCæ����ȴ��������ȡADCת����ֵ
    Flag = 1 ;
    TEMP = ADC12MEM0;                     //��ȡADCת��ֵ
    count++;
    Data_do(TEMP);                        //����ADCֵ��������ʾ
    if(count<235)                         //������ʾ��X���ʲôλ�ã���ʾ����λ�ú�Ҫ������ݣ�else���ִ�����
    {
        GUIpoint(30+count,190-(1.50*Precent),Red);     //�ѵ�ѹֵ������������򣬲��ðٷֱ��㷨

        GUIline(30+count-1,yback,30+count,190-(1.50*Precent),Red);  //��ÿ����֮����ֱ�����ӣ��γɲ���
        delay_ms(50);
    }
    else
    {
        count=1;
        Show_RGB(31,265,40,189,Black);     //����ʾ������ʱ���ñ���ɫ�����ʾ��
    }
}

/********************************************************************
                      ������
 ********************************************************************/
main()
{
    WDT_Init();                        //���Ź�����
    Clock_Init();                      //ϵͳʱ������
    Port_Init();                       //ϵͳ��ʼ��������IO������

    Device_code=0x9320;                //TFT����IC�ͺ�
    TFT_Initial();                     //��ʼ��LCD

    CLR_Screen(Black);                                        //�ñ���ɫ����
    CLR_Screen(Black);               //�ñ���ɫ����
    LCD_PutString24(75,85,"�����͵��ӿƼ�",Yellow,Black); //��ӭ���棬24x24��С���֣���ģ�������С����

    LCD_PutString24(115,119,"��",Yellow,Black);

    LCD_PutString24(145,119,"ӭ",Yellow,Black);

    LCD_PutString24(175,119,"��",Yellow,Black);

    LCD_PutString(102,222,"www.avrgcc.com",White,Black);      //�ַ���ʾ�ٷ���վ
    delay_ms(800);
    delay_ms(300);
    CLR_Screen(Black);                                          //�ñ���ɫ����

    GUICoordinate(30,190,280,180,2,Yellow,Black);   //���������ᣬ������Ҫ��ȫ����Ե���ƣ���������ش�ϸ����
    LCD_PutString(104,220,"ADC Input Wave",White,Black);      //��ʾԭ��0
    count = 1;                          //����ֵ��ʼ��Ϊ0
    ADC_Init();                         //��ʼ��ADC����
    _EINT();                            //ʹ���ж�
    Flag=1;                             //��־λ����1

    while(1)
    {
        while(Flag==1)
        {
            ADC12CTL0 |= ADC12SC;           //����ת��
            ADC12CTL0 &= ~ADC12SC;          //����
            Flag=0;                         //�����־λ
        }
    }
}
