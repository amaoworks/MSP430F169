#include <msp430x16x.h>
#include "Config.h"
#define CPU_F ((double)8000000) //按键
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

#define KeyPort         P1IN                              //独立键盘接在P10~P13
#define LED             P3OUT                             //LED灯接在P34、P35上

#define   Num_of_Results   8

static unsigned int A0results[Num_of_Results];  // These need to be global in
static unsigned int A1results[Num_of_Results];  // this example. Otherwise, the
uchar key=0;

static uchar Flag;                          //标志变量
uint temp1,temp2;                           //ADC值暂存变量
float temp3,temp4;
unsigned char bank[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39}; //十个数字的ASCII码

//*************************************************************************
//  初始化IO口子程序
//*************************************************************************
void Port_init()
{
    P1SEL = 0x00;                   //P1普通IO功能
    P1DIR = 0xF0;                   //P10~P13输入模式，外部电路已接上拉电阻
    P3SEL = 0x00;                   //P3口普通IO功能
    P3DIR = 0xFF;                   //P3口输出模式
}

//**********************************************************************
//  键盘扫描子程序，采用逐键扫描的方式
//**********************************************************************

uchar Key_Scan()
{ // uchar key=0;
    if((P1IN&0x0f)!=0x0f)
    {
        delay_ms(100);
        if((P1IN&0x0f)!=0x0f)
            switch(P1IN&0x0f)
            {
            case 0x0e:  key=1; while((P1IN&0x0f)==0x0e); break;
            case 0x0d:  key=2; while((P1IN&0x0f)==0x0d); break;
            case 0x0b:  key=3; while((P1IN&0x0f)==0x0b); break;
            case 0x07:  key=4; while((P1IN&0x0f)==0x07); break;
            }

    }
    return key;

}



//***********************************************************************
//               LCD端口初始化
//***********************************************************************
void LCD_Port_Init(void)
{
    P4SEL=0x00;             //普通IO口
    P4DIR=0xFF;             //输出方向
    P5SEL=0x00;             //普通IO口
    P5DIR|=0xE3;            //P5.0,P5.1,P5.5,P5.6,P5.7为输出方向
    P5OUT|=BIT0;        //PSB置1，液晶并口方式
    P5OUT|=BIT1;            //复位脚RST置高
}
//***********************************************************************
//  显示屏命令写入函数
//***********************************************************************
void LCD_write_com(unsigned char com)
{
    RS_CLR;                 //P5OUT &= ~BIT5  RS置低
    RW_CLR;                 //P5OUT &= ~BIT6  RW置低
    EN_SET;                 //P5OUT |=  BIT7  E置高
    DataPort=com;           //P4OUT    P4口为数据口
    delay_ms(5);
    EN_CLR;}                //P5OUT &= ~BIT7 E置低
//***********************************************************************
//  显示屏数据写入函数
//***********************************************************************
void LCD_write_data(unsigned char data)
{
    RS_SET;                  //P5OUT |=  BIT5  RS置高
    RW_CLR;                  //P5OUT &= ~BIT6  RW置低
    EN_SET;                  //P5OUT |=  BIT7  E置高
    DataPort=data;
    delay_ms(5);
    EN_CLR;}                 //P5OUT &= ~BIT7  E置低
//***********************************************************************
//  显示屏初始化函数
//***********************************************************************
void LCD_Screan_Init(void)
{
    LCD_write_com(FUN_MODE);            //显示模式设置(0x30)工作模式：8位基本指令集
    delay_ms(5);
    LCD_write_com(FUN_MODE);            //显示模式设置
    delay_ms(5);
    LCD_write_com(DISPLAY_ON);          //显示开(0x0c)显示游标，且游标位置反白
    delay_ms(5);
    LCD_write_com(CLEAR_SCREEN);        //清屏(0x01)清屏指令：清屏且AC值为00H
    delay_ms(5);}
//***********************************************************************
//  显示屏清空显示
//***********************************************************************
void LCD_clear(void)
{
    LCD_write_com(0x01);
    delay_ms(5);}
//***********************************************************************
//               显示CGROM里的汉字
//***********************************************************************
void DisplayCgrom(uchar addr,uchar *hz)
{
    LCD_write_com(addr);
    delay_ms(5);
    while(*hz != '\0')
    {
        LCD_write_data(*hz);
        hz++;
        delay_ms(5);}
}
//****************************************************************
//函数名称：Display()显示汉字
//****************************************************************
void Display(void)
{
    LCD_clear();
    DisplayCgrom(0x80,"通道2(A):");
    DisplayCgrom(0x90,"                ");
    DisplayCgrom(0x88,"通道1(A):");
    DisplayCgrom(0x98,"按S5返回主菜单  ");

}

void Display_main(void)
{
    LCD_clear();
    DisplayCgrom(0x80,"主界面          ");
    DisplayCgrom(0x90,"欢迎使用        ");
    DisplayCgrom(0x88,"并联供电电源系统");
    DisplayCgrom(0x98,"按S4查看使用说明");
}
void Display_explain(void)
{
    LCD_clear();
    DisplayCgrom(0x80,"按S2设电流比为1 ");
    DisplayCgrom(0x90,"按S3设电流比为2 ");
    DisplayCgrom(0x88,"                ");
    DisplayCgrom(0x98,"按S5返回主界面  ");
}
//***********************************************************************
//  显示电压值
//***********************************************************************
static void Lcd_Show(char adress,float data)
{
    int idata;
    float fdata;                           //将浮点数分拆成整数部分和小数部分
    idata=(int)data;                       //整数部分
    fdata=data-idata;                      //小数部分
    LCD_write_com(adress);                 //设定显示地址
    LCD_write_data(bank[idata%10]);
    delay_ms(5);                           //不加延时的时候，小数点前一位一直闪
    LCD_write_data(0x2E);                  //小数点
    LCD_write_data(bank[(int)(fdata*10)]);
    LCD_write_data(bank[(int)(fdata*100)%10]);
    LCD_write_data(bank[(int)(fdata*1000)%10]);
}
//*************************************************************************
//  ADC初始化程序，用于配置ADC相关寄存器
//*************************************************************************
void ADC_Init(void)
{
    P6SEL = 0x03;                             // Enable A/D channel inputs？？？？？？？？？？？？？？？？？？
    ADC12CTL0 = ADC12ON+MSC+SHT0_8;//+REF2_5V;           // Turn on ADC12, extend sampling time
    // to avoid overflow of results
    ADC12CTL1 = SHP+CONSEQ_3;                 // Use sampling timer, repeated sequence
    ADC12MCTL0 = INCH_0;                      // ref+=AVcc, channel = A0
    ADC12MCTL1 = INCH_1+EOS;                      // ref+=AVcc, channel = A1
    ADC12IE = 0x08;                           // Enable ADC12IFG.3
    ADC12CTL0 |= ENC;                         // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    //ADC12CTL0&=~ADC12SC;          //清零 //////////////////
    _BIS_SR(GIE);                 // Enter LPM0, Enable interrupts}                               //使能转换器

}
/***********************************************************
    启动ADC12
 ************************************************************/
void start_ADC12(void)
{
    while(Flag==1)
    {
        ADC12CTL0|=ADC12SC;
        ADC12CTL0&=~ADC12SC;          //清零
        Flag=0;
    }
}
//*************************************************************************
//  ADC中断服务程序
//*************************************************************************
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
    //_BIS_SR_IRQ(LPM0_bits);
    LCD_write_com(0x99);
    LCD_write_data('c');

    while((ADC12CTL0&0x01)==1);    //如果ADC忙，则等待，否则读取ADC转换数值
    //Flag=1;
    // temp1=ADC12MEM0;              //读取ADC转换值
    // temp=(temp1)*2.45/4095;       //转换公式，ADC数字量转换为电压大小，注意数据类型
    //  unsigned int index = 0;
}
void delay()
{
    int i;
    for(i=0;i<100;i++);
}
//实际中的VREF+为2.45V
//***********************************************************************
//            主程序
//***********************************************************************
void main(void)
{


    WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
    P2DIR=0XFF;
    P2OUT=0X00;
    static unsigned int index = 0,i;
    Clock_Init();                 //时钟初始化
    Port_init();                  //系统初始化，设置IO口属性
    LCD_Port_Init();              //液晶端口初始化
    LCD_Screan_Init();            //液晶参数初始化
    LCD_clear();                  //清屏
    //ADC_Init();                   //初始化ADC12
    P6SEL = 0x0F;                             // Enable A/D channel inputs
    ADC12CTL0 = ADC12ON+MSC+SHT0_8;           // Turn on ADC12, extend sampling time
    // to avoid overflow of results
    ADC12CTL1 = SHP+CONSEQ_3;                 // Use sampling timer, repeated sequence
    ADC12MCTL0 = INCH_0;                      // ref+=AVcc, channel = A0
    ADC12MCTL1 = INCH_1;                      // ref+=AVcc, channel = A1
    ADC12MCTL2 = INCH_2;                      // ref+=AVcc, channel = A2
    ADC12MCTL3 = INCH_3+EOS;                  // ref+=AVcc, channel = A3, end seq.
    ADC12IE = 0x08;                           // Enable ADC12IFG.3
    ADC12CTL0 |= ENC;                         // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion



    //_EINT();                      //开总中断
    //Flag=1;                       //标志位先置1
    Display_main();
    //_BIS_SR(GIE);                 // Enter LPM0, Enable interrupts}                               //使能转换器
    while(1)
    {
        switch( Key_Scan())
        {
        case 1: LED=0xEF;     //给不同的键赋键值，键值1，亮1个LED灯D1
        key=0;
        // for(int i=0;i<0xffff;i++);
        // start_ADC12();              //启动ADC12



        Display();
        P2OUT=0x22;
        while(1)
        {
            for(i=0;i<8;i++)
            {
                A0results[index] = ADC12MEM0;             // Move A0 results, IFG is cleared
                A1results[index] = ADC12MEM1;             // Move A1 results, IFG is cleared
                index = (index+1)%Num_of_Results;         // Increment results index, modulo; Set Breakpoint here
            }
            temp1=(A0results[0]+A0results[1]+A0results[2]+A0results[3]+A0results[4]+A0results[5]+ A0results[6]+A0results[7])/8;
            temp2=(A1results[0]+A1results[1]+A1results[2]+A1results[3]+A1results[4]+A1results[5]+ A1results[6]+A1results[7])/8;
            temp3=temp1*2.5/4095;
            //temp3=(temp3+0.07536)/2.082;
            temp4=temp2*2.5/4095;
            //temp4=(temp4+0.002)/1.594;
            Lcd_Show(0x85,temp3);        //显示电压
            Lcd_Show(0x8D,temp4);        //显示电压

            delay();
            delay();
            delay();
            Key_Scan();
            if(key!=0)
                break;
        }
        break;
        case 2: LED=0xDF;
        key=0;
        // for(int i=0;i<0xffff;i++);
        // start_ADC12();              //启动ADC12
        Display();
        P2OUT=0x44;
        while(1)
        {
            for(i=0;i<8;i++)
            {
                A0results[index] = ADC12MEM0;             // Move A0 results, IFG is cleared
                A1results[index] = ADC12MEM1;             // Move A1 results, IFG is cleared
                index = (index+1)%Num_of_Results;         // Increment results index, modulo; Set Breakpoint here
            }
            temp1=(A0results[0]+A0results[1]+A0results[2]+A0results[3]+A0results[4]+A0results[5]+ A0results[6]+A0results[7])/8;
            temp2=(A1results[0]+A1results[1]+A1results[2]+A1results[3]+A1results[4]+A1results[5]+ A1results[6]+A1results[7])/8;
            temp3=temp1*2.5/4095;
            //temp3=(temp3+0.07536)/2.082;
            temp4=temp2*2.5/4095;
            //temp4=(temp4+0.002)/1.594;
            Lcd_Show(0x85,temp3);        //显示电压
            Lcd_Show(0x8D,temp4);        //显示电压

            delay();
            delay();
            delay();
            Key_Scan();

            if(key!=0)
                break;
        }
        break;  //给不同的键赋键值，键值2，亮1个LED灯D2
        case 3: Display_explain();
        key=0;
        while(1)
        {
            Key_Scan();
        }
        }
    }
}
