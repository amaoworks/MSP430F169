#include <msp430x16x.h>
#include "Config.h"
#define CPU_F ((double)8000000) //����
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

#define KeyPort         P1IN                              //�������̽���P10~P13
#define LED             P3OUT                             //LED�ƽ���P34��P35��

#define   Num_of_Results   8

static unsigned int A0results[Num_of_Results];  // These need to be global in
static unsigned int A1results[Num_of_Results];  // this example. Otherwise, the
uchar key=0;

static uchar Flag;                          //��־����
uint temp1,temp2;                           //ADCֵ�ݴ����
float temp3,temp4;
unsigned char bank[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39}; //ʮ�����ֵ�ASCII��

//*************************************************************************
//  ��ʼ��IO���ӳ���
//*************************************************************************
void Port_init()
{
    P1SEL = 0x00;                   //P1��ͨIO����
    P1DIR = 0xF0;                   //P10~P13����ģʽ���ⲿ��·�ѽ���������
    P3SEL = 0x00;                   //P3����ͨIO����
    P3DIR = 0xFF;                   //P3�����ģʽ
}

//**********************************************************************
//  ����ɨ���ӳ��򣬲������ɨ��ķ�ʽ
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
//               LCD�˿ڳ�ʼ��
//***********************************************************************
void LCD_Port_Init(void)
{
    P4SEL=0x00;             //��ͨIO��
    P4DIR=0xFF;             //�������
    P5SEL=0x00;             //��ͨIO��
    P5DIR|=0xE3;            //P5.0,P5.1,P5.5,P5.6,P5.7Ϊ�������
    P5OUT|=BIT0;        //PSB��1��Һ�����ڷ�ʽ
    P5OUT|=BIT1;            //��λ��RST�ø�
}
//***********************************************************************
//  ��ʾ������д�뺯��
//***********************************************************************
void LCD_write_com(unsigned char com)
{
    RS_CLR;                 //P5OUT &= ~BIT5  RS�õ�
    RW_CLR;                 //P5OUT &= ~BIT6  RW�õ�
    EN_SET;                 //P5OUT |=  BIT7  E�ø�
    DataPort=com;           //P4OUT    P4��Ϊ���ݿ�
    delay_ms(5);
    EN_CLR;}                //P5OUT &= ~BIT7 E�õ�
//***********************************************************************
//  ��ʾ������д�뺯��
//***********************************************************************
void LCD_write_data(unsigned char data)
{
    RS_SET;                  //P5OUT |=  BIT5  RS�ø�
    RW_CLR;                  //P5OUT &= ~BIT6  RW�õ�
    EN_SET;                  //P5OUT |=  BIT7  E�ø�
    DataPort=data;
    delay_ms(5);
    EN_CLR;}                 //P5OUT &= ~BIT7  E�õ�
//***********************************************************************
//  ��ʾ����ʼ������
//***********************************************************************
void LCD_Screan_Init(void)
{
    LCD_write_com(FUN_MODE);            //��ʾģʽ����(0x30)����ģʽ��8λ����ָ�
    delay_ms(5);
    LCD_write_com(FUN_MODE);            //��ʾģʽ����
    delay_ms(5);
    LCD_write_com(DISPLAY_ON);          //��ʾ��(0x0c)��ʾ�α꣬���α�λ�÷���
    delay_ms(5);
    LCD_write_com(CLEAR_SCREEN);        //����(0x01)����ָ�������ACֵΪ00H
    delay_ms(5);}
//***********************************************************************
//  ��ʾ�������ʾ
//***********************************************************************
void LCD_clear(void)
{
    LCD_write_com(0x01);
    delay_ms(5);}
//***********************************************************************
//               ��ʾCGROM��ĺ���
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
//�������ƣ�Display()��ʾ����
//****************************************************************
void Display(void)
{
    LCD_clear();
    DisplayCgrom(0x80,"ͨ��2(A):");
    DisplayCgrom(0x90,"                ");
    DisplayCgrom(0x88,"ͨ��1(A):");
    DisplayCgrom(0x98,"��S5�������˵�  ");

}

void Display_main(void)
{
    LCD_clear();
    DisplayCgrom(0x80,"������          ");
    DisplayCgrom(0x90,"��ӭʹ��        ");
    DisplayCgrom(0x88,"���������Դϵͳ");
    DisplayCgrom(0x98,"��S4�鿴ʹ��˵��");
}
void Display_explain(void)
{
    LCD_clear();
    DisplayCgrom(0x80,"��S2�������Ϊ1 ");
    DisplayCgrom(0x90,"��S3�������Ϊ2 ");
    DisplayCgrom(0x88,"                ");
    DisplayCgrom(0x98,"��S5����������  ");
}
//***********************************************************************
//  ��ʾ��ѹֵ
//***********************************************************************
static void Lcd_Show(char adress,float data)
{
    int idata;
    float fdata;                           //���������ֲ���������ֺ�С������
    idata=(int)data;                       //��������
    fdata=data-idata;                      //С������
    LCD_write_com(adress);                 //�趨��ʾ��ַ
    LCD_write_data(bank[idata%10]);
    delay_ms(5);                           //������ʱ��ʱ��С����ǰһλһֱ��
    LCD_write_data(0x2E);                  //С����
    LCD_write_data(bank[(int)(fdata*10)]);
    LCD_write_data(bank[(int)(fdata*100)%10]);
    LCD_write_data(bank[(int)(fdata*1000)%10]);
}
//*************************************************************************
//  ADC��ʼ��������������ADC��ؼĴ���
//*************************************************************************
void ADC_Init(void)
{
    P6SEL = 0x03;                             // Enable A/D channel inputs������������������������������������
    ADC12CTL0 = ADC12ON+MSC+SHT0_8;//+REF2_5V;           // Turn on ADC12, extend sampling time
    // to avoid overflow of results
    ADC12CTL1 = SHP+CONSEQ_3;                 // Use sampling timer, repeated sequence
    ADC12MCTL0 = INCH_0;                      // ref+=AVcc, channel = A0
    ADC12MCTL1 = INCH_1+EOS;                      // ref+=AVcc, channel = A1
    ADC12IE = 0x08;                           // Enable ADC12IFG.3
    ADC12CTL0 |= ENC;                         // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    //ADC12CTL0&=~ADC12SC;          //���� //////////////////
    _BIS_SR(GIE);                 // Enter LPM0, Enable interrupts}                               //ʹ��ת����

}
/***********************************************************
    ����ADC12
 ************************************************************/
void start_ADC12(void)
{
    while(Flag==1)
    {
        ADC12CTL0|=ADC12SC;
        ADC12CTL0&=~ADC12SC;          //����
        Flag=0;
    }
}
//*************************************************************************
//  ADC�жϷ������
//*************************************************************************
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
    //_BIS_SR_IRQ(LPM0_bits);
    LCD_write_com(0x99);
    LCD_write_data('c');

    while((ADC12CTL0&0x01)==1);    //���ADCæ����ȴ��������ȡADCת����ֵ
    //Flag=1;
    // temp1=ADC12MEM0;              //��ȡADCת��ֵ
    // temp=(temp1)*2.45/4095;       //ת����ʽ��ADC������ת��Ϊ��ѹ��С��ע����������
    //  unsigned int index = 0;
}
void delay()
{
    int i;
    for(i=0;i<100;i++);
}
//ʵ���е�VREF+Ϊ2.45V
//***********************************************************************
//            ������
//***********************************************************************
void main(void)
{


    WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
    P2DIR=0XFF;
    P2OUT=0X00;
    static unsigned int index = 0,i;
    Clock_Init();                 //ʱ�ӳ�ʼ��
    Port_init();                  //ϵͳ��ʼ��������IO������
    LCD_Port_Init();              //Һ���˿ڳ�ʼ��
    LCD_Screan_Init();            //Һ��������ʼ��
    LCD_clear();                  //����
    //ADC_Init();                   //��ʼ��ADC12
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



    //_EINT();                      //�����ж�
    //Flag=1;                       //��־λ����1
    Display_main();
    //_BIS_SR(GIE);                 // Enter LPM0, Enable interrupts}                               //ʹ��ת����
    while(1)
    {
        switch( Key_Scan())
        {
        case 1: LED=0xEF;     //����ͬ�ļ�����ֵ����ֵ1����1��LED��D1
        key=0;
        // for(int i=0;i<0xffff;i++);
        // start_ADC12();              //����ADC12



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
            Lcd_Show(0x85,temp3);        //��ʾ��ѹ
            Lcd_Show(0x8D,temp4);        //��ʾ��ѹ

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
        // start_ADC12();              //����ADC12
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
            Lcd_Show(0x85,temp3);        //��ʾ��ѹ
            Lcd_Show(0x8D,temp4);        //��ʾ��ѹ

            delay();
            delay();
            delay();
            Key_Scan();

            if(key!=0)
                break;
        }
        break;  //����ͬ�ļ�����ֵ����ֵ2����1��LED��D2
        case 3: Display_explain();
        key=0;
        while(1)
        {
            Key_Scan();
        }
        }
    }
}
