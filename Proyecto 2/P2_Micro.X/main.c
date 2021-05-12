#define _XTAL_FREQ 32000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f873.h>
#include "lcd.h"
//#include "kbd.h"

void iniciar_puertos();

int main()
{
    iniciar_puertos();
    /*Iniciar LCD*/
    LCD_Begin(); 
    LCD_Goto(1, 1);    
    __delay_ms(500);
    
    while(1){
    //LCD_Print("hola"); 
    LCD_PutC('x');  
    __delay_ms(500);
    }
}

void iniciar_puertos()
{
    
    /*Seteo de entradas PUERTO C*/
    PORTC=0X00;
    TRISC=0XF0;
    RA0=0;
    /*Activamos el PULL UP para leer cada entrada del teclado*/
   // OPTION_REG &= 0x7F;
    
    //Realizar la digitalizacion
    ADCON1 =  0b00000110;
}