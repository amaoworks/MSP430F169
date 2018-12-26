#include <msp430f169.h>
#include "I2C.h"
#include "LCD.h"

#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define SMPLRT_DIV      0x19    //陀螺仪采样率，典型值：0x07(125Hz)
#define CONFIG          0x1A    //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG     0x1B    //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define ACCEL_CONFIG    0x1C    //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define ACCEL_XOUT_H    0x3B	//X轴高八位
#define ACCEL_XOUT_L    0x3C	//X轴低八位
#define ACCEL_YOUT_H    0x3D	//Y轴高八位
#define ACCEL_YOUT_L    0x3E	//Y轴低八位
#define ACCEL_ZOUT_H    0x3F	//Z轴高八位
#define ACCEL_ZOUT_L    0x40	//Z轴低八位
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48
#define PWR_MGMT_1      0x6B    //电源管理，典型值：0x00(正常启用)
#define WHO_AM_I        0x75    //IIC地址寄存器(默认数值0x68，只读)
#define SlaveAddress    0xD0    //IIC写入时的地址字节数据，+1为读取

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

void MPU6050_init()
{
    i2c_write(0x6b, 0x00);  //解除休眠状态
    i2c_write(0x19, 0x07);
    i2c_write(0x1a, 0x06);
    i2c_write(0x1b, 0x18);
    i2c_write(0x1c, 0x01);
}

void port_init(){
    P3SEL |= 0x0A;
    U0CTL |=I2C +SYNC; //选择I2c模式
    U0CTL &=~I2CEN;//复位
    I2CTCTL =I2CSSEL1; //SMCLk时钟
    I2CSA =(0xd0>>1);        //从机地址
    U0CTL |=I2CEN;      //i2c使能
//    P6DIR =0xff;
//    P6OUT =0x00;
    P3DIR &=~0x0a;
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;     // stop watchdog timer
    Clock_Init();
    port_init();
    LCD_Portinit();
    LCD_init();
    unsigned char BUF[6];
    unsigned int  X;
    unsigned int  Y;
    unsigned int  Z1;
 //   delay_ms(200);
    MPU6050_init();
 //   delay_ms(200);
    while(1){
 //  i2c_write(0x43,0x06);
        BUF[0]=i2c_read(0x3B);
        BUF[1]=i2c_read(0x3C);
        X=(BUF[0]<<8)+BUF[1];
        X/=16.4;
        Display_Num(0,0,X);
        BUF[2]=i2c_read(0x3D);
        BUF[3]=i2c_read(0x3E);
        Y=(BUF[2]<<8)+BUF[3];
        Y/=16.4;
        Display_Num(6,0,Y);
        BUF[4]=i2c_read(0x3F);
        BUF[5]=i2c_read(0x40);
        Z1=(BUF[4]<<8)+BUF[5];
        Z1/=16.4;
        Display_Num(0,1,Z1);
    }
}




