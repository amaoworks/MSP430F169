/********************************************************************
//DM430-L����Сϵͳ���ⲿ��Դ�����ļ�Config.h
//�������ظ�����Դ��Ӳ�����ã�����û�ʹ�ù����У���Ӧ��Ӳ�������˸��ģ������ø�ͷ�ļ�����ʹ��
//SD/MMC����ʼ��Ӳ������δ����
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2014.03.01
********************************************************************/
#include <msp430f169.h>
//��ʱ������IAR�Դ�������ʹ�õ�
#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//�Զ������ݽṹ������ʹ��
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

uint    temp_value;
uint    temp,j,speed,j;
uchar   A1,A2,A3;                     //����ı���,��ʾ���ݴ���
uchar   Temp_Value[6];                     //��ʾ�õ��¶����ݣ������÷�������׼������
uchar bb;
uchar keyvalue;

//���ڲ����ʼ��㣬��BRCLK=CPU_Fʱ������Ĺ�ʽ���Լ��㣬����Ҫ�������ü����Ƶϵ��
#define baud           9600                                //���ò����ʵĴ�С
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //�����ʼ��㹫ʽ
#define baud_h         (uchar)(baud_setting>>8)            //��ȡ��λ
#define baud_l         (uchar)(baud_setting)               //��λ

//RS485���ƹܽţ�CTR���ڿ���RS485�����ջ��߷�״̬
#define RS485_CTR1      P5OUT |= BIT2;          //�������øߣ�RS485����״̬
#define RS485_CTR0      P5OUT &= ~BIT2;         //�������õͣ�RS485����״̬

//2.8��TFT������ʾ�������Ӳ������
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�

#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�

#define RD_CLR          P5OUT &= ~BIT7           //E�õ�
#define RD_SET          P5OUT |=  BIT7           //E�ø�

#define CS_CLR          P5OUT &= ~BIT0            //CS�õ�
#define CS_SET          P5OUT |=  BIT0            //CS�ø�

#define RST_CLR         P5OUT &= ~BIT3            //RST�õ�
#define RST_SET         P5OUT |=  BIT3            //RST�ø�

#define LE_CLR          P5OUT &= ~BIT1            //LE�õ�
#define LE_SET          P5OUT |=  BIT1            //LE�ø�

////2.8��TFT�����������������Ӳ������
//#define PEN_CLR         P2OUT &= ~BIT0           //PEN�õ�,����������ʱ��Penirq������δ����ʱ�ĸߵ�ƽ��Ϊ�͵�ƽ
//#define PEN_SET         P2OUT |=  BIT0           //PEN�ø�
//#define PEN             (P2IN & 0x01)            //P2.0�����ֵ
//
//#define TPDO_CLR    P2OUT &= ~BIT1           //TPDO�õ�
//#define TPDO_SET    P2OUT |=  BIT1           //TPDO�ø�
//#define TPDOUT          ((P2IN>>1)&0x01)         //P2.1�����ֵ
//
//#define BUSY_CLR    P2OUT &= ~BIT3           //BUSY�õ�
//#define BUSY_SET    P2OUT |=  BIT3           //BUSY�ø�
//
//#define TPDI_CLR    P2OUT &= ~BIT4            //TPDI�õ�
//#define TPDI_SET    P2OUT |=  BIT4            //TPDI�ø�
//
//#define TPCS_CLR    P2OUT &= ~BIT5            //TPCS�õ�
//#define TPCS_SET    P2OUT |=  BIT5            //TPCS�ø�
//
//#define TPCLK_CLR   P2OUT &= ~BIT6            //TPCLK�õ�
//#define TPCLK_SET   P2OUT |=  BIT6            //TPCLK�ø�

//����/12864Һ��/1602Һ�������ݿڣ���Һ������
#define DataDIR         P6DIR                     //���ݿڷ���
#define DataPort        P6OUT                     //P4��Ϊ���ݿ�

//12864/1602Һ�����ƹܽ�
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�

#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�

#define EN_CLR          P5OUT &= ~BIT7           //E�õ�
#define EN_SET          P5OUT |=  BIT7           //E�ø�

#define PSB_CLR         P5OUT &= ~BIT0            //PSB�õͣ����ڷ�ʽ
#define PSB_SET         P5OUT |=  BIT0            //PSB�øߣ����ڷ�ʽ

//#define RST_CLR         P5OUT &= ~BIT1            //RST�õ�
//#define RST_SET         P5OUT |= BIT1             //RST�ø�

//12864Ӧ��ָ�
#define CLEAR_SCREEN    0x01                  //����ָ�������ACֵΪ00H
#define AC_INIT     0x02                  //��AC����Ϊ00H�����α��Ƶ�ԭ��λ��
#define CURSE_ADD   0x06                  //�趨�α��Ƶ�����ͼ�������ƶ�����Ĭ���α����ƣ�ͼ�����岻����
#define FUN_MODE    0x30                  //����ģʽ��8λ����ָ�
#define DISPLAY_ON  0x0c                  //��ʾ��,��ʾ�α꣬���α�λ�÷���
#define DISPLAY_OFF 0x08                  //��ʾ��
#define CURSE_DIR   0x14                  //�α������ƶ�:AC=AC+1
#define SET_CG_AC   0x40                  //����AC����ΧΪ��00H~3FH
#define SET_DD_AC   0x80                      //����DDRAM AC
#define FUN_MODEK   0x36                  //����ģʽ��8λ��չָ�

//��ɫ���룬TFT��ʾ��
#define White          0xFFFF                                                               //��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

//NRF2401ģ�������
#define  RF24L01_CE_0        P1OUT &=~BIT5         //CE��P15
#define  RF24L01_CE_1        P1OUT |= BIT5

#define  RF24L01_CSN_0       P2OUT &=~BIT7         //CS��P27
#define  RF24L01_CSN_1       P2OUT |= BIT7

#define  RF24L01_SCK_0       P3OUT &=~BIT3         //SCK��P33
#define  RF24L01_SCK_1       P3OUT |= BIT3

#define  RF24L01_MISO_0      P3OUT &=~BIT2         //MISO��P32
#define  RF24L01_MISO_1      P3OUT |= BIT2

#define  RF24L01_MOSI_0      P3OUT &=~BIT1         //MOSI��P31
#define  RF24L01_MOSI_1      P3OUT |= BIT1

#define  RF24L01_IRQ_0       P1OUT &=~BIT4         //IRQ��P14
#define  RF24L01_IRQ_1       P1OUT |= BIT4

//DS18B20���ƽţ����ſ���
#define DQ_IN           P1DIR &= ~BIT7        //�������룬DS18B20�ӵ�Ƭ��P53��
#define DQ_OUT          P1DIR |= BIT7         //�������
#define DQ_CLR          P1OUT &= ~BIT7            //�õ͵�ƽ
#define DQ_SET          P1OUT |= BIT7             //�øߵ�ƽ
#define DQ_R            P1IN & BIT7       //����ƽ

//�������ͷH1838���ƽţ����ſ���
#define RED_IN          P1DIR &= ~BIT6            //�������룬�������ͷ�ӵ�Ƭ��PE3��
#define RED_OUT         P1DIR |=  BIT6            //�������
#define RED_L           P1OUT &= ~BIT6            //�õ͵�ƽg'f
#define RED_H           P1OUT |= BIT6             //�øߵ�ƽ
#define RED_R           (P1IN & BIT6)             //����ƽ

void init_clk();
void WDT_Init();
void LCD_Port_init();
void LCD_write_com(unsigned char);
void LCD_write_data(unsigned char);
void LCD_clear(void);
//void DisplayCgrom(uchar,uchar *);
void DisplayCgrom(uchar *);
void LCD_write_char(unsigned char,unsigned char,unsigned char);
void LCD_write_str(unsigned char,unsigned char,unsigned char *);
void LCD_init(void);
void LCD_Desk(void);
unsigned char DS18B20_Reset(void);
unsigned char ds1820_read_byte(void);
void ds1820_write_byte(unsigned char);
void ds1820_start(void);
unsigned int ds1820_read_temp(void);
void data_do(uint);
void ele_init();
void timer_A_init();
void lcd_pos(uchar,uchar);
uchar keyscan(void);