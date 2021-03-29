#include<stdio.h>
#include<stdlib.h>
#include <xc.h>
//#include "flex_lcd.h"
#include <pic16f873.h>
#define _XTAL_FREQ 32000000
#include "lcd.h"
#include "kbd.h"
#include <string.h>
char text[3];
char k;

void main()
{
    PORTB=0x00;         //Seteamos en 0
    TRISB=0xF0;        //Rows Output, Coulombs Input Activamos puertos
    int i = 0;
    OPTION_REG &= 0x7F;
    LCD_Begin();       // Inicializar el modulo LCD

    LCD_Goto(1, 1);      // Ubicacion columna 1 fila 1
    char type_key='*';
    
    while (1)
    {
        if (type_key=='*') //Numeros
        {
            
            k='n';
            while(k=='n')
            {
            k = scan_key();
            }
            if(k!='!' && k!='\0')
            {
            LCD_PutC(k);
            }
            if(k=='\0')
            {
                LCD_PutC(k);
                LCD_Cmd(LCD_MOVE_CURSOR_LEFT);
            }
            if(k=='/')
            {
            type_key='/'; 
            LCD_Cmd(LCD_CLEAR);
            }
            __delay_ms(500);     // wait 1/2 second
        }
        //Alfabeto en este colocas el numero de la letra en ascci que quieres
        //Este numero debe de ser colocado con ceros a la izquierda por ejmeplo A=065
        else if(type_key=='/') 
        {
            if(i==3)
            {
                //LCD_Cmd(LCD_CLEAR);
                i=0;
                int num =0;
                num = atoi(text);
                char numx=num;
                LCD_PutC(numx);
            }
            k='n';
            while(k=='n')
            {
            k = scan_key();
            }
            if(k=='*')
            {
            type_key='*';    
            }
            if(i<3)
            {
                text[i]=k;
            }
            
            i++;
            __delay_ms(500);
        }
    }
}
