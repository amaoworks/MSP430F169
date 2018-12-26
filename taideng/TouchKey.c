/*
 * TouchKey.c
 *
 *  Created on: 2018Äê12ÔÂ25ÈÕ
 *      Author: Brown
 */
#include "TouchKey.h"

extern unsigned char key, statu, clear, voice, enter, out;
uint  LCD_X, LCD_Y;
uint minX=78, maxX=162, minY=130, maxY=166;
void touchMain(){
    if(Getpix()==1){
        if(LCD_X>78 && LCD_X<162){
            if(LCD_Y>5766 && LCD_Y<5800){
                clear=1;
                statu=1;
                while(PEN==0);
            }else if(LCD_Y>5822 && LCD_Y<5855){
                clear=1;
                statu=2;
                while(PEN==0);
            }
        }
    }
}

void touchBack(){
    while(Getpix()==1){
        if(LCD_X>99 && LCD_X<155){
            if(LCD_Y>5899 && LCD_Y<5911){
                clear=2;
                statu=0;
                while(PEN==0);
            }
        }
    }
}

void touchButton(){
    if(Getpix()==1){
        if(LCD_X>100 && LCD_X<144){
            if(LCD_Y>5777 && LCD_Y<5811){
                key++;
                if(key == 4){
                    key = 0;
                }
                while(PEN==0);
            }
        }
    }
}

void touchVoice(){
    if(Getpix()==1){
        if(LCD_X>177 && LCD_X<211){
            if(LCD_Y>5744 && LCD_Y<5788){
                enter = 0;
                out = 0;
                voice++;
                if(voice==2){
                    voice = 0;
                }
                while(PEN==0);
            }
        }
    }
}
