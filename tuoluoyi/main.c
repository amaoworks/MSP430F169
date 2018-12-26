#include <msp430f169.h>
#include "I2C.h"
#include "LCD.h"

#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define SMPLRT_DIV      0x19    //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define CONFIG          0x1A    //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define GYRO_CONFIG     0x1B    //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define ACCEL_CONFIG    0x1C    //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define ACCEL_XOUT_H    0x3B	//X��߰�λ
#define ACCEL_XOUT_L    0x3C	//X��Ͱ�λ
#define ACCEL_YOUT_H    0x3D	//Y��߰�λ
#define ACCEL_YOUT_L    0x3E	//Y��Ͱ�λ
#define ACCEL_ZOUT_H    0x3F	//Z��߰�λ
#define ACCEL_ZOUT_L    0x40	//Z��Ͱ�λ
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48
#define PWR_MGMT_1      0x6B    //��Դ��������ֵ��0x00(��������)
#define WHO_AM_I        0x75    //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define SlaveAddress    0xD0    //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

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

void MPU6050_init()
{
    i2c_write(0x6b, 0x00);  //�������״̬
    i2c_write(0x19, 0x07);
    i2c_write(0x1a, 0x06);
    i2c_write(0x1b, 0x18);
    i2c_write(0x1c, 0x01);
}

void port_init(){
    P3SEL |= 0x0A;
    U0CTL |=I2C +SYNC; //ѡ��I2cģʽ
    U0CTL &=~I2CEN;//��λ
    I2CTCTL =I2CSSEL1; //SMCLkʱ��
    I2CSA =(0xd0>>1);        //�ӻ���ַ
    U0CTL |=I2CEN;      //i2cʹ��
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




