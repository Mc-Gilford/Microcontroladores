/*
 * Realizado por: Jose de Jesus Rodriguez Aparicio y Karla Reyes Reyes
 * Fecha: 6/23/21
 * PIC U2 Control LED, Practica 3
*/

/*En dado caso de que el codigo no funcione comentar este codigo hasta el siguiente comentario de fin*/
#pragma config FOSC = XT // OSCILADOR
#pragma config WDTE = OFF // Perro Guardian
#pragma config PWRTE = OFF // Power Up Tiempo habilitado
#pragma config BOREN = OFF // Brown out reset
#pragma config LVP = OFF // Low volatge 
#pragma config CPD = OFF // Dta EEPROM Memory
#pragma config WRT = OFF //Flash Program Memory Write
#pragma config CP = OFF // Flash Program Memory Code

/*Fin de codigo*/

#define _XTAL_FREQ 32000000
#include <pic.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f819.h>
#include <string.h>

#define ADDRA 0xA0 //Direccion de PIC1
#define ADDRB 0xA1 // Direccion PIC2

/*Para envio de datos*/
int ADRES=0;
unsigned char envio;

void iniciar_puertos()
{
    PORTA = 0x00;
    PORTB = 0x00;
    /*Al poner TRIS en 1 significa entrada y 0 salida*/

    /*Configuran puertos de A como salida*/   
    TRISBbits.TRISB1 = 0; 
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISAbits.TRISA4 = 1; 
    //ADCON1 =  0b00000110;
    ADCON1 = 0x07;
}

void evaluar_dato()
{
            if(ADRES < 127)     // 0V
                envio = 0x00;
            if(ADRES > 127)     // 625 mv 
                envio = 0x01;
            if(ADRES > 255)     // 1.25 V
                envio=0x03;
            if(ADRES > 352)     // 1.87 V
                envio=0x07;
            if(ADRES > 511)     // 2.5 V
                envio=0x0F;
            if(ADRES > 639)     // 3.12 V
                envio=0x1F;
            if(ADRES > 767)     // 3.75 V
                envio=0x3F;
            if(ADRES > 894)     // 4.37 V
                envio=0x7F;
            if(ADRES > 1022)   // 5 V
                envio=0xFF;
}

// Funcion de conversion Analogico Digital 
void Canal0()    
{
                
    CHS2 = 0;                          // Seleccion del canal analogo 0
    CHS1 = 0;
    CHS0 = 0;
    
    ADON = 1;                          // Activa el modulo del covertidor analogico digital
     
    __delay_ms(4);//Delay_ms(z);                       // Tiempo de espera para adquisicion 5ms
                     
     GO = 1;                            // Inicia la conversion 
     
    
    ADCA:  if (ADIF == 0)              // Espera hasta que termine la conversion
    goto ADCA;                
    
    ADON = 0;                          // Desactiva el convertidor
    
    ADRES = (ADRESH << 8) | ADRESL;    // Almcena la conversion en la variable Peso1 
    
    ADIF = 0;                          // Borrado de bandera de conversion finalizada     

    evaluar_dato();                                                             
}



void main()
{
    iniciar_puertos();
   /* while(1){
    }*/
}
