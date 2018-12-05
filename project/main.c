#include <msp430f169.h>
#include "config.h"
#include "DS1302.h"
#include "UART.h"
#include "miaobiao.h"
#include "keypd.h"

//Һ����ʾ���ֱ���
uchar shuzi[] = {"0123456789"};
//˳���룬�֣�ʱ���գ��£����ڣ��ꣻ��ʽ��BCD
uchar times[7];
//cflag=0;
//PP=0;

void ShowTime(void);

int main(void)
{

    WDT_Init();	                        // stop watchdog timer
    //Reset_DS1302();                     //��ʼ��DS1302
    init_clk();
	LCD_Port_init();
	delay_ms(100);                      //��ʱ100ms
	LCD_init();                         //Һ��������ʼ������
	LCD_clear();                        //����
	LCD_Desk();
	DS18B20_Reset();                    //��λD18B20
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
	    stopwatch(keyvalue);                //��ͣ��������ʱ

	    ds1820_start();                     //����һ��ת��
	    ds1820_read_temp();                 //��ȡ�¶���ֵ
	    data_do(temp_value);                //�������ݣ��õ�Ҫ��ʾ��ֵ

	    lcd_pos(3,3);
	    DisplayCgrom(Temp_Value);           //��ʾ�¶ȣ��¶�ֵ��Temp_Value������
	    DisplayCgrom("���϶�");

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
	        if(j == 0) DisplayCgrom("�ֶ����㵵");
	        if(j == 1) DisplayCgrom("�Զ����㵵");
	    }
	    if(speed == 1){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 2000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 2000;
	        lcd_pos(2,0);
	        if(j == 1) DisplayCgrom("�Զ���һ��");
	    }
	    if(speed == 2){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 4000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 4000;
	        lcd_pos(2,0);
	        if(j == 0) DisplayCgrom("�ֶ���һ��");
	        if(j == 1) DisplayCgrom("�Զ�������");
	    }
	    if(speed == 3){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 6000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 6000;
	        lcd_pos(2,0);
	        if(j == 0) DisplayCgrom("�ֶ�������");
	        if(j == 1) DisplayCgrom("�Զ�������");
	    }

	    if(speed == 4){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 8000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 8000;
	        lcd_pos(2,0);
	        if(j == 1) DisplayCgrom("�Զ����ĵ�");
	    }
	    if(speed == 5){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 9000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 9000;
	        lcd_pos(2,0);
	        if(j == 0) DisplayCgrom("�ֶ�������");
	        if(j == 1) DisplayCgrom("�Զ����嵵");
	    }
	    if(speed == 6){
	        TBCCR0 = 10000;
	        TBCCTL0 = CCIE;
	        TBCCTL2 = OUTMOD_2;
	        TBCCR2 = 9000;
	        TBCCTL3 = OUTMOD_7;
	        TBCCR3 = 9000;
	        lcd_pos(2,0);
	        if(j == 1) DisplayCgrom("�Զ�������");
	    }
	}
	
}



/*------------------------------------------
P1���жϺ���
------------------------------------------*/
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    if(P1IFG&0x0f)
     {
       Key_Event();   //��ⰴ��
       if(key_Flag == 1)
       {
        key_Flag = 0;
        switch(key_val)
        {
            case 0x01:
            switch(PP++)      //ȷ���α��ַ
            {
            case 0: lcd_pos(0,1);break;
            case 1: lcd_pos(0,3);break;
            case 2: lcd_pos(0,5);break;
            case 3: lcd_pos(1,0);break;
            case 4: lcd_pos(1,2);break;
            case 5: lcd_pos(1,4);break;
            default:break;
            }
            LCD_write_com(0x0f);   //���α�
            if(PP == 6) PP = 0;
            cflag = 1;          //��־��λ
            break;
       case 0x02:
           if(cflag)
           {
               switch(PP)
               {
               case 1:         //��
                   year++;
                   LCD_write_data(year / 10 + 0x30);
                   LCD_write_data(year % 10 + 0x30);
                   lcd_pos(0,1);
                   break;
               case 2:         //��
                   month++;
                   LCD_write_data(month / 10 + 0x30);
                   LCD_write_data(month % 10 + 0x30);
                   lcd_pos(0,3);
                   break;
               case 3:         //��
                   day++;
                   LCD_write_data(day / 10 + 0x30);
                   LCD_write_data(day % 10 + 0x30);
                   lcd_pos(0,5);
                   break;
               case 4:         //ʱ
                   hour++;
                   LCD_write_data(hour / 10 + 0x30);
                   LCD_write_data(hour % 10 + 0x30);
                   lcd_pos(1,0);
                   break;
               case 5:         //��
                   min++;
                   LCD_write_data(min / 10 + 0x30);
                   LCD_write_data(min % 10 + 0x30);
                   lcd_pos(1,2);
                   break;
               case 6:         //��
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
                       case 0:         //��
                                year--;
                                LCD_write_data(year / 10 + 0x30);
                                LCD_write_data(year % 10 + 0x30);
                                lcd_pos(0,1);
                                break;
                        case 1:         //��
                                month--;
                                LCD_write_data(month / 10 + 0x30);
                                LCD_write_data(month % 10 + 0x30);
                                lcd_pos(0,3);
                                break;
                        case 2:         //��
                                day--;
                                LCD_write_data(day / 10 + 0x30);
                                LCD_write_data(day % 10 + 0x30);
                                lcd_pos(0,5);
                                break;
                        case 3:         //ʱ
                                hour--;
                                LCD_write_data(hour / 10 + 0x30);
                                LCD_write_data(hour % 10 + 0x30);
                                lcd_pos(1,0);
                                break;
                         case 4:         //��
                                min--;
                                LCD_write_data(min / 10 + 0x30);
                                LCD_write_data(min % 10 + 0x30);
                                lcd_pos(1,2);
                                break;
                         case 5:         //��
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
                        LCD_write_com(0x0c);   //�ر��α�
                        P1IFG=0x00;
                    }
                    break;


        }
       }
 }
}

