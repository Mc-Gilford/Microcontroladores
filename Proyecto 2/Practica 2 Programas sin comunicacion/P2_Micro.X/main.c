

#define _XTAL_FREQ 32000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f873.h>
#include "lcd.h"
#include "kbd.h"
#include <string.h>
void iniciar_puertos();
void inicio_presentacion();

//Agregar variable global
char number[4];

int X = 47;
char M[] = {"El ADC y el UART Jose Rdgz y Karla Reyes"};
int ECO;
int ADRES;


void Tx_Dato(unsigned char X)
{
    PIR1bits.TXIF = 0;      //  Restaura la bandera del transmisor
    TXREG = X;          //  Pasa el dato de la conversion 
    
    /* Inicia la transmision*/                    
Transmitiendo:     
                if(TXSTAbits.TRMT == 0)  //  Byte a sido transmitido?  
                goto Transmitiendo;   //  No, Esperar a que termine la transmision
}
            
                
/* Funcion de recepcion*/            
unsigned char Rx_Dato(void)
{
    wait:   
        if(PIR1bits.RCIF == 0)      // Se recibio un dato?
        goto wait;                 // No, Esperar a recibir                                               
    PIR1bits.RCIF = 0;          // Se repone la bandera RCIF a 0
    return RCREG;
} 

int main()
{
    int i=0; //Para concatenar dentro del array 
    iniciar_puertos();
    
    /*Iniciar LCD*/
    LCD_Begin();
    inicio_presentacion();
    __delay_ms(500);
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
         LCD_PutC(' ');
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

void inicio_presentacion ()
{
    LCD_Goto(1,1);
    LCD_Print(M);
    __delay_ms(50);
    for(int i=0;i<40;i++){
        LCD_Cmd(LCD_SHIFT_LEFT);
        __delay_ms(40);
    }   
    __delay_ms(50);
    LCD_Cmd(LCD_CLEAR);
    LCD_Goto(1, 1);
}