/*
 * Show.c
 *
 *  Created on: 2018Äê12ÔÂ20ÈÕ
 *      Author: With-Cappuccino
 */

#include "Show.h"

void display_interface()
{  unsigned int i,j;

   /* for(j=0;j<32;j++)
    for(i=0;i<5;i++)
         GUIline(0,j*5+i,240,j*5+i,j);
    for(j=0;j<=32;j++)
       for(i=0;i<5;i++)
            GUIline(0,160+j*5+i,240,160   +j*5+i,31-j);*/
    for(i=0;i<5;i++)
        GUIcircle(120,120,60-i,Black);
    /*
     **
     ****
     *****/
   /* for(i=0;i<32;i++)
        for(j=0;j<=i;j++)
        {
            Put_pixel(20+j,20+i,Red);
        }*/
    /*****
      ****
       ***
        **
        */
  /*  for(i=0;i<32;i++)
           for(j=0;j<=i;j++)
           {
               Put_pixel(20+j,20+i,Red);
           }*/
    /*GUIfull(0,0,240,20,0xfbe0);
    GUIfull(20,20,25,230,Red);
    GUIfull(215,20,220,230,Red);
    GUIfull(25,20,215,25,Red);
    GUIfull(25,225,215,230,Red);*/
}


