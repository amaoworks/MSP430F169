#include <msp430f169.h>
#include "config.h"
#include "DS1302.h"
#include "UART.h"
#include "miaobiao.h"
#include "keypd.h"

//液晶显示数字编码
uchar shuzi[] = {"0123456789"};
//顺序：秒，分，时，日，月，星期，年；格式：BCD
uchar times[7];
//cflag=0;
//PP=0;

void ShowTime(void);

int main(void)
{

    WDT_Init();	                        // stop watchdog timer
    //Reset_DS1302();                     //初始化DS1302
    init_clk();
	LCD_Port_init();
	delay_ms(100);                      //延时100ms
	LCD_init();                         //液晶参数初始化设置
	LCD_clear();                        //清屏
	LCD_Desk();
	DS18B20_Reset();                    //复位D18B20
	xianshi();
	timer_A_init();
	ele_init();

	timer_B_init();
	init_port1();

	UART_Init();
	speed = 0;
	j=0;
	_EINT();
	keyvalue=0;
	while(1){
	    //youbiao(keyvalue);
	    stopwatch(keyvalue);                //暂停、继续定时

	    ds1820_start();                     //启动一次转换
	    ds1820_read_temp();                 //读取温度数值
	    data_do(temp_value);                //处理数据，得到要显示的值

	    lcd_pos(3,3);
	    DisplayCgrom(Temp_Value);           //显示温度，温度值在Temp_Value数组里
	    DisplayCgrom("摄氏度");

	    if(keyvalue == 4) j=0;
	    if(keyvalue == 5) j=1;

	    if(keyvalue == 0) speed = 0 ,j = 0;
	    if((keyvalue == 1)&(j == 0)) speed = 2;
	    if((keyvalue == 2)&(j == 0)) speed = 3;
	    if((keyvalue == 3)&(j == 0)) speed = 5;

	    if(j == 1){
	        if(temp_value>=200 & temp_value<210) speed = 1;
	        if(temp_value>=210 & temp_value<220) speed = 2;
	        if(temp_value>=220 & temp_value<230) speed = 3;
	        if(temp_value>=230 & temp_value<240) speed = 4;
	        if(temp_value>=240 & temp_value<250) speed = 5;
	        if(temp_value>=250) speed = 6;
	    }

	    if(speed == 0){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 0;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 0;
	        lcd_pos(2,0);
	        if(j == 0) DisplayCgrom("手动：零档");
	        if(j == 1) DisplayCgrom("自动：零档");
	    }
	    if(speed == 1){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 2000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 2000;
	        lcd_pos(2,0);
	        if(j == 1) DisplayCgrom("自动：一档");
	    }
	    if(speed == 2){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 4000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 4000;
	        lcd_pos(2,0);
	        if(j == 0) DisplayCgrom("手动：一档");
	        if(j == 1) DisplayCgrom("自动：二档");
	    }
	    if(speed == 3){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 6000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 6000;
	        lcd_pos(2,0);
	        if(j == 0) DisplayCgrom("手动：二档");
	        if(j == 1) DisplayCgrom("自动：三档");
	    }

	    if(speed == 4){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 8000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 8000;
	        lcd_pos(2,0);
	        if(j == 1) DisplayCgrom("自动：四档");
	    }
	    if(speed == 5){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 9000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 9000;
	        lcd_pos(2,0);
	        if(j == 0) DisplayCgrom("手动：三档");
	        if(j == 1) DisplayCgrom("自动：五档");
	    }
	    if(speed == 6){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 9000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 9000;
	        lcd_pos(2,0);
	        if(j == 1) DisplayCgrom("自动：六档");
	    }
	}
	
}



/*------------------------------------------
P1口中断函数
------------------------------------------*/
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    if(P1IFG&0x0f)
     {
       Key_Event();   //检测按键
       if(key_Flag == 1)
       {
        key_Flag = 0;
        switch(key_val)
        {
            case 0x01:
            switch(PP++)      //确定游标地址
            {
            case 0: lcd_pos(0,1);break;
            case 1: lcd_pos(0,3);break;
            case 2: lcd_pos(0,5);break;
            case 3: lcd_pos(1,0);break;
            case 4: lcd_pos(1,2);break;
            case 5: lcd_pos(1,4);break;
            default:break;
            }
            LCD_write_com(0x0f);   //打开游标
            if(PP == 6) PP = 0;
            cflag = 1;          //标志置位
            break;
       case 0x02:
           if(cflag)
           {
               switch(PP)
               {
               case 1:         //年
                   year++;
                   LCD_write_data(year / 10 + 0x30);
                   LCD_write_data(year % 10 + 0x30);
                   lcd_pos(0,1);
                   break;
               case 2:         //月
                   month++;
                   LCD_write_data(month / 10 + 0x30);
                   LCD_write_data(month % 10 + 0x30);
                   lcd_pos(0,3);
                   break;
               case 3:         //日
                   day++;
                   LCD_write_data(day / 10 + 0x30);
                   LCD_write_data(day % 10 + 0x30);
                   lcd_pos(0,5);
                   break;
               case 4:         //时
                   hour++;
                   LCD_write_data(hour / 10 + 0x30);
                   LCD_write_data(hour % 10 + 0x30);
                   lcd_pos(1,0);
                   break;
               case 5:         //分
                   min++;
                   LCD_write_data(min / 10 + 0x30);
                   LCD_write_data(min % 10 + 0x30);
                   lcd_pos(1,2);
                   break;
               case 6:         //秒
                   sec++;
                   LCD_write_data(sec / 10 + 0x30);
                   LCD_write_data(sec % 10 + 0x30);
                   lcd_pos(1,4);
                   break;
               default:
                   break;

               }
           }break;
      case 0x03:
               if(cflag)
               {
                   switch(PP-1)
                   {
                       case 0:         //年
                                year--;
                                LCD_write_data(year / 10 + 0x30);
                                LCD_write_data(year % 10 + 0x30);
                                lcd_pos(0,1);
                                break;
                        case 1:         //月
                                month--;
                                LCD_write_data(month / 10 + 0x30);
                                LCD_write_data(month % 10 + 0x30);
                                lcd_pos(0,3);
                                break;
                        case 2:         //日
                                day--;
                                LCD_write_data(day / 10 + 0x30);
                                LCD_write_data(day % 10 + 0x30);
                                lcd_pos(0,5);
                                break;
                        case 3:         //时
                                hour--;
                                LCD_write_data(hour / 10 + 0x30);
                                LCD_write_data(hour % 10 + 0x30);
                                lcd_pos(1,0);
                                break;
                         case 4:         //分
                                min--;
                                LCD_write_data(min / 10 + 0x30);
                                LCD_write_data(min % 10 + 0x30);
                                lcd_pos(1,2);
                                break;
                         case 5:         //秒
                                sec--;
                                LCD_write_data(sec / 10 + 0x30);
                                LCD_write_data(sec % 10 + 0x30);
                                lcd_pos(1,3);
                                break;
                        default:
                                break;
                        }
                    }break;
          case 0x04:
                    if(cflag)
                    {
                        cflag = 0;
                        PP = 0;
                        LCD_write_com(0x0c);   //关闭游标
                        P1IFG=0x00;
                    }
                    break;


        }
       }
 }
}

