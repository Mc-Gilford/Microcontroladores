#define _XTAL_FREQ 32000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f873.h>
#include "lcd.h"
#include "kbd.h"
#include <string.h>
void iniciar_puertos();

//Agregar variable global
char number[4];

int main()
{
    int i=0; //Para concatenar dentro del array 
    iniciar_puertos();
    /*Iniciar LCD*/
    LCD_Begin(); 
    LCD_Goto(1, 1);    
    __delay_ms(500);
    
    while(1){
    //LCD_Print("hola");
    //char c = scan_key();
    if(i<4)
    {       
    char c = keypad_getkey();
        if(c!='=' && c!='A')
        {
        LCD_PutC(c);
        number[i]=c;
        i++;
        }
        else if(c=='A')
        {
            i=0;
            LCD_Cmd(LCD_CLEAR);
        }
        /*else{
            i=0;
            LCD_Goto(1,2);
            LCD_Print("Enviado");
        }*/
    }
    else
    {
         i=0;
         LCD_Goto(1,2);
         LCD_Print("Enviado");
    }
    __delay_ms(500);
    }
}

void iniciar_puertos()
{
    
    /*Seteo de entradas PUERTO C*/
    PORTC=0X00;
    TRISC=0XF0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    /*Activamos el PULL UP para leer cada entrada del teclado*/
   // OPTION_REG &= 0x7F;
    
    //Realizar la digitalizacion
    ADCON1 =  0b00000110;
}