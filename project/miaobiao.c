#include "miaobiao.h"
//#include "keypad.h"


#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A(void)
{
    sec++;    //设置标志位Flag
}

void xianshi(){
    lcd_pos(0,0);
    DisplayCgrom("20");
    lcd_pos(0,2);
    DisplayCgrom("年");
    lcd_pos(0,4);
    DisplayCgrom("月");
    lcd_pos(0,6);
    DisplayCgrom("日");
    lcd_pos(1,1);
    LCD_write_data(':');
    lcd_pos(1,3);
    LCD_write_data(':');
}
void stopwatch(int key)
{
    if(key == 10)
    {
        TACCTL0 = ~CCIE;
    }
    if(key == 11)
    {
        TACCTL0 = CCIE;
    }
    if(sec >= 60)
    {
        sec = 0;
        min++;
    }
    if(min >= 60)
    {
        min = 0;
        hour++;
    }
    if(hour >= 24)
    {
        day++;
        hour = 0;
    }
    if(day >= 30)
    {
        month++;
        day = 1;
    }
    if(month >= 12)
    {
        year++;
        month = 1;
    }

    lcd_pos(0,1);
    LCD_write_data(year / 10 + 0x30);
    LCD_write_data(year % 10 + 0x30);

    lcd_pos(0,3);
    LCD_write_data(month / 10 + 0x30);
    LCD_write_data(month % 10 + 0x30);

    lcd_pos(0,5);
    LCD_write_data(day / 10 + 0x30);
    LCD_write_data(day % 10 + 0x30);

    lcd_pos(1,0);
    LCD_write_data(hour / 10 + 0x30);
    LCD_write_data(hour % 10 + 0x30);

    lcd_pos(1,2);
    LCD_write_data(min / 10 + 0x30);
    LCD_write_data(min % 10 + 0x30);

    lcd_pos(1,4);
    LCD_write_data(sec / 10 + 0x30);
    LCD_write_data(sec % 10 + 0x30);
}

void timer_A_init()
{
    TACCTL0 = CCIE;
    CCR0 = 32768;
    TACTL = TASSEL_1 + MC_1;
    //BCSCTL2 |= SELS;
}

void init_port1()
{
    P1DIR &=~ BIT0;
    P1IES |= BIT0;
    P1IE |= BIT0;
    P1IFG &=~ BIT0;
}

