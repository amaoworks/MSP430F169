#include <msp430f169.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//LED!!
#define LEDDIR  P1DIR
#define LED     P1OUT

#define SCL_H P3OUT |= BIT3//此IO在硬件上需要更改
#define SCL_L P3OUT &= ~BIT3
#define SDA_H P3OUT |= BIT1
#define SDA_L P3OUT &= ~BIT1

#define SCL_OUT P3DIR |= BIT3
#define SDA_IN  P3DIR &= ~BIT1   //SDA改成输入模式
#define SDA_OUT P3DIR |= BIT1    //SDA变回输出模式
#define SDA_VAL P3IN&BIT1        //SDA的位值

#define DataDir     P4DIR
#define DataPort    P4OUT
#define Busy        0x80
//#define CtrlDir     P5DIR
//#define CLR_RS P5OUT&=~BIT0     //RS = P5.0
//#define SET_RS P5OUT|=BIT0
//#define CLR_RW P5OUT&=~BIT1     //RW = P5.1
//#define SET_RW P5OUT|=BIT1
//#define CLR_EN P5OUT&=~BIT2     //EN = P5.2
//#define SET_EN P5OUT|=BIT2

#define set_RS P5OUT |=  BIT5          //设置RS为1
#define clr_RS P5OUT &= ~BIT5          //设置RS为0
#define set_EN P5OUT |=  BIT7          //设置EN为1
#define clr_EN P5OUT &= ~BIT7          //设置EN为0
#define set_RW P5OUT |=  BIT6          //设置RW为1
#define clr_RW P5OUT &= ~BIT6          //设置RW为0
#define dataout P4DIR=0xff             //初始化D0~D7
//#define dataport P4OUT

#define _NOP()  __no_operation()
#define SlaveAddress 0x46  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                                //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A
unsigned char ge,shi,bai,qian,wan;  //显示变量
int dis_data;
uchar BUF[8];

void LED_init(){
    LEDDIR = 0xff;
    LED = 0xFF;
}

void I2C_init(){
    SDA_OUT;
    SDA_H;
    SCL_OUT;
    SCL_H;
}

void Delay5us(void)
{
    uchar i;

 for(i = 0;i < 15;i++);
   _NOP();
}
void Delay5ms(void)
{
    uint i=40000;
    while (i != 0)
    {
        i--;
    }
}

void delay(uint x)
{
  uchar i;
  while(x--)for(i=0;i<125;i++);
}

void BH1750_Start()
{
  SDA_H;                    //拉高数据线
  SCL_H;                    //拉高时钟线
  Delay5us();               //延时
  SDA_L;                    //产生下降沿
  Delay5us();               //延时
  SCL_L;                    //拉低时钟线
}
void BH1750_Stop()
{
  SDA_L;                    //拉低数据线
  SCL_H;                    //拉高时钟线
  Delay5us();                 //延时
  SDA_H;                    //产生上升沿
  Delay5us();                 //延时
}

void BH1750_SendACK(void)
{
  SDA_L;                  //写应答信号
  _NOP();_NOP();
  SCL_H;                    //拉高时钟线
  Delay5us();                  //延时
  SCL_L;                    //拉低时钟线
  _NOP();_NOP();
  SDA_H;
  Delay5us();                 //延时
}

void mnack(void)
{
  SDA_H;
  _NOP(); _NOP();
  SCL_H;
  Delay5us();
  SCL_L;
  _NOP(); _NOP();
  SDA_L;
  Delay5us();
}

uchar BH1750_RecvACK()
{
  uchar ack;

  SDA_H;
  _NOP(); _NOP();
  SCL_H;
  _NOP(); _NOP();
  SDA_IN;
  _NOP(); _NOP();
  ack = SDA_VAL;   //读入SDA数值
  SCL_L;
  Delay5us();
  SDA_OUT;
  if(ack)    return 0;
  else            return  1;
}

void write1(void)
{
  SDA_H;
  //Delay5us();
  SCL_H;
  Delay5us();
  SCL_L;
  Delay5us();
}

void write0(void)
{
  SDA_L;
 // Delay5us();
  SCL_H;
  Delay5us();
  SCL_L;
  Delay5us();
}
void BH1750_SendByte(unsigned char dat)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {        //8位计数器
       if(dat&0x80)
         write1();
       else
         write0();
       dat <<= 1;              //移出数据的最高位
    }
    BH1750_RecvACK();
}

unsigned char BH1750_RecvByte()
{
  unsigned char i;
  unsigned char dat = 0,flag;

  SDA_H;                     //使能内部上拉,准备读取数据,
  for (i = 0; i < 8; i++)
  {       //8位计数器
    //SDA_H;
    //Delay5us();
    SCL_H;
    SDA_IN;
    Delay5us();
    flag=SDA_VAL;
    dat <<= 1;
    if(flag)
      dat|=0x01;
    SDA_OUT;
    SCL_L;
    Delay5us();
  }
  return dat;
}

void Single_Write_BH1750(unsigned char REG_Address)
{
 BH1750_Start();                  //起始信号
 BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
 BH1750_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页
 //  BH1750_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页
 BH1750_Stop();                   //发送停止信号
}
void Init_BH1750()
{
  Single_Write_BH1750(0x01);
}

void Multiple_Read_BH1750(void)
{
 unsigned char i;
 BH1750_Start();                          //起始信号
 BH1750_SendByte(0x47);         //发送设备地址+读信号

 for (i = 0; i < 3; i++) {                      //连续读取6个地址数据，存储中BUF
  BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
  if (i == 3) {


       mnack();                //最后一个数据需要回NOACK
  }
  else {

       BH1750_SendACK();                //回应ACK
  }
 }
 BH1750_Stop();                          //停止信号
 Delay5ms();
}
void conversion(unsigned int temp_data)   //数据转换出 个，十，百，千，万
{
    wan = temp_data / 10000 + 0x30;
    temp_data = temp_data % 10000;  //取余运算

    qian = temp_data / 1000 + 0x30;
    temp_data = temp_data % 1000;  //取余运算

    bai = temp_data / 100 + 0x30;
    temp_data = temp_data % 100;  //取余运算

    shi = temp_data / 10 + 0x30;
    temp_data = temp_data % 10;   //取余运算

    ge = temp_data + 0x30;
}

//void WaitForEnable(void)
//{
//    DataDir &= 0x00;
//
//    CLR_RS;
//    SET_RW;
//    _NOP();
//    SET_EN;
//    _NOP();
//    _NOP();
//
//    while((P4IN & Busy)!=0);  //检测忙标志   //STA7为0 允许读写操作使能则退出循环
//
//    CLR_EN;
//
//    DataDir |= 0xFF;  //将P4口切换为输出状态
//}
//void WriteCommandLCM(unsigned char CMD,uchar Attribc)
//{
//    if(Attribc)
//      WaitForEnable();
//    CLR_RS;
//    CLR_RW;
//    _NOP();
//    DataPort = CMD;
//    _NOP();
//    SET_EN;
//    _NOP();
//    _NOP();
//    CLR_EN;
//}

//void WriteDataLCM(unsigned char dataW)
//{
//  WaitForEnable();
//  SET_RS;
//  CLR_RW;
//  _NOP();
//  DataPort = dataW;
//  _NOP();
//  SET_EN;
//  _NOP();
//  _NOP();
//  CLR_EN;
//}

void write_com(uchar com){          //1602写命令
    P5DIR|=(BIT5+BIT6+BIT7);        //将P5.5 P5.6 P5.7设置为输出
    dataout;
    clr_RS;                         //令RS为0 写入命令
    clr_RW;                         //令RW为0
    //clr_E;                          //使能置零
    //delay5ms();
    //delay_ms(5);
    //set_EN;
    DataPort = com;
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

void write_date(uchar date){        //1602写数据
    P5DIR|=(BIT5+BIT6+BIT7);
    //P4DIR = 0xff;
    dataout;
    set_RS;                         //写入数据
    clr_RW;
    DataPort = date;
    delay_ms(5);
    clr_EN;
    delay_ms(5);
    set_EN;
    //P4OUT = date;
    //delay5ms();
    delay_ms(5);
    //set_E;
    //delay5ms();
    clr_EN;
}

DisplayOneChar(unsigned char x, unsigned char date){
    write_com(0x80 + x);
    write_date(date);
}

void init(){            //这里看书上的P46~P48
    //clr_E;
    write_com(0x38);
    delay_ms(5);
    write_com(0x0c);
    delay_ms(5);
    write_com(0x06);
    delay_ms(5);
    write_com(0x01);
}

void port_init(){           //端口初始化
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|=BIT5 + BIT6 + BIT7;
}

void display(unsigned long int num){        //数字显示
    uchar k;
    uchar dis_flag = 0;
    uchar table[7];
    if(num <= 9&num > 0){
        dis_flag = 1;
        table[0] = num % 10 + '0';
    }else if(num <= 99&num > 9){
        dis_flag = 2;
        table[0] = num/10 + '0';
        table[1] = num % 10 + '0';
    }else if(num <= 999&num > 99){
        dis_flag = 3;
        table[0] = num/100 + '0';
        table[1] = num/10 % 10 + '0';
        table[2] = num % 10 + '0';
    }else if(num <= 9999&num > 999){
        dis_flag = 4;
        table[0] = num/1000 + '0';
        table[1] = num/100 % 10 + '0';
        table[2] = num/10 % 10 + '0';
        table[3] = num % 10 + '0';
    }
    for(k = 0; k < dis_flag; k++){
        write_date(table[k]);
        delay_ms(5);
    }
}

void inmaindispaly()
{
  uint temp;
  dis_data=BUF[0];
  dis_data=(dis_data<<8)+BUF[1];//合成数据

  temp=dis_data;

  conversion(temp);         //计算数据和显示
  DisplayOneChar(0x0,'L');
  DisplayOneChar(0x01,'i');
  DisplayOneChar(0x02,'g');
  DisplayOneChar(0x03,'h');
  DisplayOneChar(0x04,'t');
  DisplayOneChar(0x05,':');

  DisplayOneChar(0x07,wan); //显示数据
  DisplayOneChar(0x08,qian);
  DisplayOneChar(0x09,bai);
  DisplayOneChar(0x0a,shi);
  DisplayOneChar(0x0b,ge);

  DisplayOneChar(0x0c,'l'); ////显示数单位
  DisplayOneChar(0x0d,'x');
}

/*
void InitLcd()
{
  CtrlDir |= 0x07;                 //控制线端口设为输出状态
  DataDir  = 0xFF;                 //数据端口设为输出状态
  WriteCommandLCM(0x38,0);
  delay(15);
  WriteCommandLCM(0x08,1);
  delay(1);
  WriteCommandLCM(0x01,1);
  delay(1);
  WriteCommandLCM(0x06,1);
  delay(1);
  WriteCommandLCM(0x0c,1);
  delay(1);
}
void DisplayOneChar(unsigned char X,unsigned char DData)
{
   X |= 0x80;
  WriteCommandLCM(X,0);
  WriteDataLCM(DData);
}

void inmaindispaly()
{
  uint temp;
  dis_data=BUF[0];
  dis_data=(dis_data<<8)+BUF[1];//合成数据

  temp=dis_data;

  conversion(temp);         //计算数据和显示
  DisplayOneChar(0,'L');
  DisplayOneChar(1,'i');
  DisplayOneChar(2,'g');
  DisplayOneChar(3,'h');
  DisplayOneChar(4,'t');
  DisplayOneChar(5,':');

  DisplayOneChar(7,wan); //显示数据
  DisplayOneChar(8,qian);
  DisplayOneChar(9,bai);
  DisplayOneChar(10,shi);
  DisplayOneChar(11,ge);

  DisplayOneChar(13,'l'); ////显示数单位
  DisplayOneChar(14,'x');
}
*/

void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //打开XT2振荡器
  BCSCTL2|=SELM1+SELS;              //MCLK为8MHZ，SMCLK为8MHZ
  do{
    IFG1&=~OFIFG;                   //清楚振荡器错误标志
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //如果标志位1，则继续循环等待
  IFG1&=~OFIFG;
}

void main( void )
{
  uint temp = 0;
  uint a = 0;
  uint b = 10;
  uint c = 30;
  uint d = 50;
  P4DIR=0XFF;
  P5DIR|=0X07;
  P3DIR|=0XC0;
  WDTCTL = WDTPW + WDTHOLD;// Stop watchdog timer to prevent time out reset
  Clock_Init();
  delay(20);     //延时200ms
//  InitLcd();           //初始化LCD
  Init_BH1750();       //初始化BH1750
  I2C_init();
  port_init();
  init();
  LED_init();
  while(1)
  {
    Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode

    delay(180);              //延时180ms

    Multiple_Read_BH1750();       //连续读出数据，存储在BUF中


    inmaindispaly();
//    LED |= 1<<0;
    temp=dis_data;
    if(temp > a && temp < b){
        LED = 0xFD;
    }else if(temp>b && temp<c){
        LED = 0xF9;
    }else if(temp>c){
        LED = 0xF1;
    }
//    LED_init();
    delay(100);
//    LED |= 1<<0;
//    LED |= 1<<1;
//    LED |= 1<<2;

  }
}
