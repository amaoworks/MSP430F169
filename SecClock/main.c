#include <msp430f169.h>

#define CPU_F ((double)8000000)        //外部高频晶振8MHZ
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define uchar unsigned char            //无符号字符
#define uint unsigned int
#define set_RS P5OUT |=  BIT5          //设置RS为1
#define clr_RS P5OUT &= ~BIT5          //设置RS为0
#define set_EN P5OUT |=  BIT7          //设置EN为1
#define clr_EN P5OUT &= ~BIT7          //设置EN为0
#define set_RW P5OUT |=  BIT6          //设置RW为1
#define clr_RW P5OUT &= ~BIT6          //设置RW为0
#define dataout P4DIR=0xff             //初始化D0~D7
#define dataport P4OUT

int second = 0, minute = 0, count = 0, flag = 0, a = 0, b = 0, c = 0;
unsigned char FlagLcd;

//时钟初始化
void int_clk(){
    unsigned char i;
    BCSCTL1&=~XT2OFF;             //打开XT振荡器
    BCSCTL2|=SELM1 + SELS;        //MCLK为8MHZ，SMCLK为1MHZ
    do{
        IFG1&=~OFIFG;             //清除振荡器错误标识
        for(i = 0; i < 100; i++)
            _NOP();                 //延时等待
    }while((IFG1&OFIFG) != 0);
    IFG1&=~OFIFG;                 //如果标志为1，则继续循环等待
}

//1602写命令
void write_com(uchar com){
    P5DIR|=(BIT5+BIT6+BIT7);        //将P5.5 P5.6 P5.7设置为输出
    dataout;
    clr_RS;                         //令RS为0 写入命令
    clr_RW;                         //令RW为0
    dataport = com;
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

//1602写数据
void write_date(uchar date){
    P5DIR|=(BIT5+BIT6+BIT7);
    dataout;
    set_RS;                         //写入数据
    clr_RW;
    dataport = date;
    delay_ms(5);
    clr_EN;
    delay_ms(5);
    set_EN;
    delay_ms(5);
    clr_EN;
}

//显示屏初始化
void init(){            //这里看书上的P46~P48
    write_com(0x38);
    delay_ms(5);
    write_com(0x0c);
    delay_ms(5);
    write_com(0x06);
    delay_ms(5);
    write_com(0x01);
}

//端口初始化
void port_init(){
    P4SEL = 0x00;
    P4DIR = 0xff;
    P5SEL = 0x00;
    P5DIR|=BIT5 + BIT6 + BIT7;
    P1SEL = 0x00;                   //P1普通IO功能
    P1DIR = 0xF0;                   //P10~P13输入模式，外部电路已接上拉电阻
    P1IE  = 0x0f;                   //开启 位中断
    P1IES = 0x00;                   //上升沿触发中断
    P1IFG = 0x00;                   //软件清零中断标志寄存器
}

void lcd_clear(void){
    write_com(0x01);
    delay_ms(5);
}

//显示屏字符串写入函数
void write_str(unsigned char x,unsigned char y,int w)
{
    if (y == 0)
    {
        write_com(0x80 + x);        //第一行显示
    }
    else
    {
        write_com(0xC0 + x);        //第二行显示
    }
    write_date(48+w);
}

//  显示屏单字符写入函数
void write_char(unsigned char x,unsigned char y,unsigned char data)
{
    if (y == 0)
    {
        write_com(0x80 + x);        //第一行显示
    }
    else
    {
        write_com(0xC0 + x);        //第二行显示
    }
    write_date( data);
}

//TIMERA初始化，设置为UP模式计数
void TIMERA_Init(void)                                   //UP模式计数，计数周期为CCR0+1
{
    TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK做时钟源，8分频，增加计数模式，开中断
    TACCR0 = 9999;                                         //CCR0=9999，10ms中断一次
}
//关闭计时，暂停计数
void TimerA_end(void)
{
    TACTL &= 0xfffd;
}

//  扫描按键P1^2是否长按
void GetKey()//长按，返回2；短按,返回1。
{
    unsigned char keyRetu=0; //返回的按键值
    static unsigned char s_keyState=0,keyTime=0; //按键状态,按键按下的时间
    switch (s_keyState)
    {
    case 0:
    {
        if((P1IN&0x02)==0x00) //检测到有按键，转到状态1，相当于是消抖过程。
        {
            s_keyState=1;
        }
    }
    break;
    case 1:
    {
        if((P1IN&0x02)==0x00) //再次检测到有按键，转到状态2
        {
            s_keyState=2;
            keyTime=0; //清零按键时间计数器
        }
        else
        {
            s_keyState=0; //没有检测到按键，说明状态0检测到是一个抖动，重新转到状态0
        }
    }
    break;
    case 2:
    {
        if((P1IN&0x02)==0x02) //检测到按键松开
        {
            s_keyState=0; //状态转到状态0
            keyRetu=1; //输出1
        }
        else
        {
            if(++keyTime>=150) //按下时间>1s
            {
                s_keyState=3; //转到状态3
                keyTime=0; //清零按键时间计数器
                keyRetu=2; // 输出2
            }
        }
    }
    break;
    case 3:
    {
        if((P1IN&0x02)==0x02) //检测到按键松开
        {
            s_keyState=0; //状态转到状态0
        }
        else
        {
            s_keyState=3; //转到状态3
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

//TIMERA中断服务程序，需要判断中断类型
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
    switch(TAIV)                                  //需要判断中断的类型
    {
    case 2:break;
    case 4:break;
    case 10:count++;break;                         //设置标志位Flag
    }
    if(count==100)                                 //100次为1秒
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

//P1口中断服务程序，需要判断
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
