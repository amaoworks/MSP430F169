#include <msp430f169.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//LED!!
#define LEDDIR  P1DIR
#define LED     P1OUT

#define SCL_H P3OUT |= BIT3//��IO��Ӳ������Ҫ����
#define SCL_L P3OUT &= ~BIT3
#define SDA_H P3OUT |= BIT1
#define SDA_L P3OUT &= ~BIT1

#define SCL_OUT P3DIR |= BIT3
#define SDA_IN  P3DIR &= ~BIT1   //SDA�ĳ�����ģʽ
#define SDA_OUT P3DIR |= BIT1    //SDA������ģʽ
#define SDA_VAL P3IN&BIT1        //SDA��λֵ

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

#define set_RS P5OUT |=  BIT5          //����RSΪ1
#define clr_RS P5OUT &= ~BIT5          //����RSΪ0
#define set_EN P5OUT |=  BIT7          //����ENΪ1
#define clr_EN P5OUT &= ~BIT7          //����ENΪ0
#define set_RW P5OUT |=  BIT6          //����RWΪ1
#define clr_RW P5OUT &= ~BIT6          //����RWΪ0
#define dataout P4DIR=0xff             //��ʼ��D0~D7
//#define dataport P4OUT

#define _NOP()  __no_operation()
#define SlaveAddress 0x46  //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                                //ALT  ADDRESS���Žӵ�ʱ��ַΪ0xA6���ӵ�Դʱ��ַΪ0x3A
unsigned char ge,shi,bai,qian,wan;  //��ʾ����
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
  SDA_H;                    //����������
  SCL_H;                    //����ʱ����
  Delay5us();               //��ʱ
  SDA_L;                    //�����½���
  Delay5us();               //��ʱ
  SCL_L;                    //����ʱ����
}
void BH1750_Stop()
{
  SDA_L;                    //����������
  SCL_H;                    //����ʱ����
  Delay5us();                 //��ʱ
  SDA_H;                    //����������
  Delay5us();                 //��ʱ
}

void BH1750_SendACK(void)
{
  SDA_L;                  //дӦ���ź�
  _NOP();_NOP();
  SCL_H;                    //����ʱ����
  Delay5us();                  //��ʱ
  SCL_L;                    //����ʱ����
  _NOP();_NOP();
  SDA_H;
  Delay5us();                 //��ʱ
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
  ack = SDA_VAL;   //����SDA��ֵ
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
    {        //8λ������
       if(dat&0x80)
         write1();
       else
         write0();
       dat <<= 1;              //�Ƴ����ݵ����λ
    }
    BH1750_RecvACK();
}

unsigned char BH1750_RecvByte()
{
  unsigned char i;
  unsigned char dat = 0,flag;

  SDA_H;                     //ʹ���ڲ�����,׼����ȡ����,
  for (i = 0; i < 8; i++)
  {       //8λ������
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
 BH1750_Start();                  //��ʼ�ź�
 BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
 BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ
 //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ
 BH1750_Stop();                   //����ֹͣ�ź�
}
void Init_BH1750()
{
  Single_Write_BH1750(0x01);
}

void Multiple_Read_BH1750(void)
{
 unsigned char i;
 BH1750_Start();                          //��ʼ�ź�
 BH1750_SendByte(0x47);         //�����豸��ַ+���ź�

 for (i = 0; i < 3; i++) {                      //������ȡ6����ַ���ݣ��洢��BUF
  BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
  if (i == 3) {


       mnack();                //���һ��������Ҫ��NOACK
  }
  else {

       BH1750_SendACK();                //��ӦACK
  }
 }
 BH1750_Stop();                          //ֹͣ�ź�
 Delay5ms();
}
void conversion(unsigned int temp_data)   //����ת���� ����ʮ���٣�ǧ����
{
    wan = temp_data / 10000 + 0x30;
    temp_data = temp_data % 10000;  //ȡ������

    qian = temp_data / 1000 + 0x30;
    temp_data = temp_data % 1000;  //ȡ������

    bai = temp_data / 100 + 0x30;
    temp_data = temp_data % 100;  //ȡ������

    shi = temp_data / 10 + 0x30;
    temp_data = temp_data % 10;   //ȡ������

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
//    while((P4IN & Busy)!=0);  //���æ��־   //STA7Ϊ0 �����д����ʹ�����˳�ѭ��
//
//    CLR_EN;
//
//    DataDir |= 0xFF;  //��P4���л�Ϊ���״̬
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

void write_com(uchar com){          //1602д����
    P5DIR|=(BIT5+BIT6+BIT7);        //��P5.5 P5.6 P5.7����Ϊ���
    dataout;
    clr_RS;                         //��RSΪ0 д������
    clr_RW;                         //��RWΪ0
    //clr_E;                          //ʹ������
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

void write_date(uchar date){        //1602д����
    P5DIR|=(BIT5+BIT6+BIT7);
    //P4DIR = 0xff;
    dataout;
    set_RS;                         //д������
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

void init(){            //���￴���ϵ�P46~P48
    //clr_E;
    write_com(0x38);
    delay_ms(5);
    write_com(0x0c);
    delay_ms(5);
    write_com(0x06);
    delay_ms(5);
    write_com(0x01);
}

void port_init(){           //�˿ڳ�ʼ��
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|=BIT5 + BIT6 + BIT7;
}

void display(unsigned long int num){        //������ʾ
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
  dis_data=(dis_data<<8)+BUF[1];//�ϳ�����

  temp=dis_data;

  conversion(temp);         //�������ݺ���ʾ
  DisplayOneChar(0x0,'L');
  DisplayOneChar(0x01,'i');
  DisplayOneChar(0x02,'g');
  DisplayOneChar(0x03,'h');
  DisplayOneChar(0x04,'t');
  DisplayOneChar(0x05,':');

  DisplayOneChar(0x07,wan); //��ʾ����
  DisplayOneChar(0x08,qian);
  DisplayOneChar(0x09,bai);
  DisplayOneChar(0x0a,shi);
  DisplayOneChar(0x0b,ge);

  DisplayOneChar(0x0c,'l'); ////��ʾ����λ
  DisplayOneChar(0x0d,'x');
}

/*
void InitLcd()
{
  CtrlDir |= 0x07;                 //�����߶˿���Ϊ���״̬
  DataDir  = 0xFF;                 //���ݶ˿���Ϊ���״̬
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
  dis_data=(dis_data<<8)+BUF[1];//�ϳ�����

  temp=dis_data;

  conversion(temp);         //�������ݺ���ʾ
  DisplayOneChar(0,'L');
  DisplayOneChar(1,'i');
  DisplayOneChar(2,'g');
  DisplayOneChar(3,'h');
  DisplayOneChar(4,'t');
  DisplayOneChar(5,':');

  DisplayOneChar(7,wan); //��ʾ����
  DisplayOneChar(8,qian);
  DisplayOneChar(9,bai);
  DisplayOneChar(10,shi);
  DisplayOneChar(11,ge);

  DisplayOneChar(13,'l'); ////��ʾ����λ
  DisplayOneChar(14,'x');
}
*/

void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //��XT2����
  BCSCTL2|=SELM1+SELS;              //MCLKΪ8MHZ��SMCLKΪ8MHZ
  do{
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
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
  delay(20);     //��ʱ200ms
//  InitLcd();           //��ʼ��LCD
  Init_BH1750();       //��ʼ��BH1750
  I2C_init();
  port_init();
  init();
  LED_init();
  while(1)
  {
    Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode

    delay(180);              //��ʱ180ms

    Multiple_Read_BH1750();       //�����������ݣ��洢��BUF��


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
