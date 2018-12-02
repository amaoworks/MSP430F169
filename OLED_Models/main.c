#include <msp430f169.h>

unsigned int test = 12356;

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock_Init();
    OLED_init();
    clearOLED();
/*    OLED_SetPos(4,2);
    unsigned char i;
    unsigned int a = 0;
/*   for(i=0;i<32;i++,a++){
    writeOLED_D(ch[a]);

    }
*/
//  fill_picture(0);
    while(1){
    OLED_DisplayF(1,0,0);
    OLED_DisplayF(16,0,1);
    OLED_ShowNum(32,0,test,5);
//    delay_ms(500);
    NewClear(1);
//  OLED_DisplayF8(2,2,0);
    P6DIR=0xff;
    P6OUT=0x55;
    }
    return 0;
}
