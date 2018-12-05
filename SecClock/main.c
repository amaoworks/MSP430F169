#include <msp430f169.h>

#define CPU_F ((double)8000000)        //�ⲿ��Ƶ����8MHZ
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define uchar unsigned char            //�޷����ַ�
#define uint unsigned int
#define set_RS P5OUT |=  BIT5          //����RSΪ1
#define clr_RS P5OUT &= ~BIT5          //����RSΪ0
#define set_EN P5OUT |=  BIT7          //����ENΪ1
#define clr_EN P5OUT &= ~BIT7          //����ENΪ0
#define set_RW P5OUT |=  BIT6          //����RWΪ1
#define clr_RW P5OUT &= ~BIT6          //����RWΪ0
#define dataout P4DIR=0xff             //��ʼ��D0~D7
#define dataport P4OUT

int second = 0, minute = 0, count = 0, flag = 0, a = 0, b = 0, c = 0;
unsigned char FlagLcd;

//ʱ�ӳ�ʼ��
void int_clk(){
    unsigned char i;
    BCSCTL1&=~XT2OFF;             //��XT����
    BCSCTL2|=SELM1 + SELS;        //MCLKΪ8MHZ��SMCLKΪ1MHZ
    do{
        IFG1&=~OFIFG;             //������������ʶ
        for(i = 0; i < 100; i++)
            _NOP();                 //��ʱ�ȴ�
    }while((IFG1&OFIFG) != 0);
    IFG1&=~OFIFG;                 //�����־Ϊ1�������ѭ���ȴ�
}

//1602д����
void write_com(uchar com){
    P5DIR|=(BIT5+BIT6+BIT7);        //��P5.5 P5.6 P5.7����Ϊ���
    dataout;
    clr_RS;                         //��RSΪ0 д������
    clr_RW;                         //��RWΪ0
    dataport = com;
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

//1602д����
void write_date(uchar date){
    P5DIR|=(BIT5+BIT6+BIT7);
    dataout;
    set_RS;                         //д������
    clr_RW;
    dataport = date;
    delay_ms(5);
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

//��ʾ����ʼ��
void init(){            //���￴���ϵ�P46~P48
    write_com(0x38);
    delay_ms(5);
    write_com(0x0c);
    delay_ms(5);
    write_com(0x06);
    delay_ms(5);
    write_com(0x01);
}

//�˿ڳ�ʼ��
void port_init(){
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|=BIT5 + BIT6 + BIT7;
    P1SEL = 0x00;                   //P1��ͨIO����
    P1DIR = 0xF0;                   //P10~P13����ģʽ���ⲿ��·�ѽ���������
    P1IE  = 0x0f;                   //���� λ�ж�
    P1IES = 0x00;                   //�����ش����ж�
    P1IFG = 0x00;                   //��������жϱ�־�Ĵ���
}

void lcd_clear(void){
    write_com(0x01);
    delay_ms(5);
}

//��ʾ���ַ���д�뺯��
void write_str(unsigned char x,unsigned char y,int w)
{
    if (y == 0)
    {
        write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        write_com(0xC0 + x);        //�ڶ�����ʾ
    }
    write_date(48+w);
}

//  ��ʾ�����ַ�д�뺯��
void write_char(unsigned char x,unsigned char y,unsigned char data)
{
    if (y == 0)
    {
        write_com(0x80 + x);        //��һ����ʾ
    }
    else
    {
        write_com(0xC0 + x);        //�ڶ�����ʾ
    }
    write_date( data);
}

//TIMERA��ʼ��������ΪUPģʽ����
void TIMERA_Init(void)                                   //UPģʽ��������������ΪCCR0+1
{
    TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK��ʱ��Դ��8��Ƶ�����Ӽ���ģʽ�����ж�
    TACCR0 = 9999;                                         //CCR0=9999��10ms�ж�һ��
}
//�رռ�ʱ����ͣ����
void TimerA_end(void)
{
    TACTL &= 0xfffd;
}

//  ɨ�谴��P1^2�Ƿ񳤰�
void GetKey()//����������2���̰�,����1��
{
    unsigned char keyRetu=0; //���صİ���ֵ
    static unsigned char s_keyState=0,keyTime=0; //����״̬,�������µ�ʱ��
    switch (s_keyState)
    {
    case 0:
    {
        if((P1IN&0x02)==0x00) //��⵽�а�����ת��״̬1���൱�����������̡�
        {
            s_keyState=1;
        }
    }
    break;
    case 1:
    {
        if((P1IN&0x02)==0x00) //�ٴμ�⵽�а�����ת��״̬2
        {
            s_keyState=2;
            keyTime=0; //���㰴��ʱ�������
        }
        else
        {
            s_keyState=0; //û�м�⵽������˵��״̬0��⵽��һ������������ת��״̬0
        }
    }
    break;
    case 2:
    {
        if((P1IN&0x02)==0x02) //��⵽�����ɿ�
        {
            s_keyState=0; //״̬ת��״̬0
            keyRetu=1; //���1
        }
        else
        {
            if(++keyTime>=150) //����ʱ��>1s
            {
                s_keyState=3; //ת��״̬3
                keyTime=0; //���㰴��ʱ�������
                keyRetu=2; // ���2
            }
        }
    }
    break;
    case 3:
    {
        if((P1IN&0x02)==0x02) //��⵽�����ɿ�
        {
            s_keyState=0; //״̬ת��״̬0
        }
        else
        {
            s_keyState=3; //ת��״̬3
        }
    }
    break;
    }
    if(keyRetu==2)
    {
        a = 0;
        b = 0;
        c = 0;
        count = 0;
        second = 0;
        minute = 0;
    }
}

//TIMERA�жϷ��������Ҫ�ж��ж�����
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
    switch(TAIV)                                  //��Ҫ�ж��жϵ�����
    {
    case 2:break;
    case 4:break;
    case 10:count++;break;                         //���ñ�־λFlag
    }
    if(count==100)                                 //100��Ϊ1��
    {
        second++;
        count=0;
    }
    if(second == 60)
    {
        minute++;
        second = 0;
    }
    GetKey();
}

//P1���жϷ��������Ҫ�ж�
#pragma vector = PORT1_VECTOR
__interrupt void P1_IRQ(void)
{
    switch(P1IFG&0x0F)
    {
    case 0x01: {

        flag++;
        P1IFG=0x00;
    }
    break;
    default:P1IFG = 0x00;break;
    }
}

/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    int_clk();
    port_init();
    delay_ms(100);
    init();
    lcd_clear();
    TIMERA_Init();
    _EINT();
    while (1)
    {
        if(flag%2==0)
        {
            write_str(0,1,c/10);
            write_str(1,1,c%10);
            write_char(2,1,0x3a);
            write_str(3,1,b/10);
            write_str(4,1,b%10);
            write_char(5,1,0x3a);
            write_str(6,1,a/10);
            write_str(7,1,a%10);
        }
        else
        {
            count = a;
            second = b;
            minute = c;
            write_str(0,1,minute/10);
            write_str(1,1,minute%10);
            write_char(2,1,0x3a);
            write_str(3,1,second/10);
            write_str(4,1,second%10);
            write_char(5,1,0x3a);
            write_str(6,1,count/10);
            write_str(7,1,count%10);
            a = count;
            b = second;
            c = minute;
        }
    }
}
