/*En dado caso de que el codigo no funcione comentar este codigo hasta el siguiente comentario de fin*/
#pragma config FOSC = XT // OSCILADOR
#pragma config WDTE = ON // Perro Guardian
#pragma config PWRTE = ON // Power Up Tiempo habilitado
#pragma config BOREN = OFF // Brown out reset
#pragma config LVP = OFF // Low volatge 
#pragma config CPD = OFF // Dta EEPROM Memory
#pragma config WRT = OFF //Flash Program Memory Write
#pragma config CP = OFF // Flash Program Memory Code
/*Fin de codigo*/

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

void imprimir_valor_leds()
{
     /*En caso de mal funcionamiento eliminar este codigo hasta el comentario de fin*/
    ADRESL = Rx_Dato();      // Recepcion del eco del dato
    Tx_Dato(ADRESL);      // Transmite el dato de ADRESL
    ADRESH = Rx_Dato();      // Recepcion del eco del dato 
    Tx_Dato(ADRESH);      // Transmite el dato de ADRESH                             
    /*Fin de codigo*/
    ADRES = (ADRESH << 8) | ADRESL;    // Almcena la conversion en la variable Peso1
    LCD_Print("Rec ");
    LCD_Print(ADRES);
    LCD_Print(" |");
}

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

void Canal0(int z)    
{
                
    CHS2 = 0;                          // Seleccion del canal analogo 0
    CHS1 = 0;
    CHS0 = 0;
    
    ADON = 1;                          // Activa el modulo del covertidor analogico digital
     
    __delay_ms(1);//Delay_ms(z);                       // Tiempo de espera para adquisicion 5ms
                     
     GO = 1;                            // Inicia la conversion 
     
    
    ADCA:  if (ADIF == 0)              // Espera hasta que termine la conversion
    goto ADCA;                
    
    ADON = 0;                          // Desactiva el convertidor
    
    ADRES = (ADRESH << 8) | ADRESL;    // Almcena la conversion en la variable Peso1 
    
    ADIF = 0;                          // Borrado de bandera de conversion finalizada     
                                                              
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
    
    
    /*En dado caso de que el programa no ejecute bien comentar el siguiente codigo hasta el comentario de fin*/
        // Configuracion del convertidor Analogico-Digital       
    ADCON0 = 0x80;        // 32 x Tosc, 
    ADCON1 = 0x8E;        // Los 6 bits mas significativos (ADRESH)son 0
    // Puertos RA0 es configurada como analogica
    
    // Configuracion de las interrupciones        
    ADIF = 0;             // Borra se£alizador del de interrupcion del ADC                   
    
    /*Configuracion del temporizador*/
    OPTION_REG = 0x51;    // configura el prescaler a 4
    TMR0 = 0;             // Limpia el TMR0
    
    /*Configuracion del Puerto Serie*/
    TXSTA = 0x00;         // Limpia el registro TXSTA
    RCSTA = 0x00;         // Limpia el registro RCSTA
    RCSTAbits.SPEN = 1;   // Activa el modulo USART
    TXSTAbits.SYNC = 0;   // Activa el modo UART
    TXSTAbits.BRGH = 1;   // Alta velocidad
    TXSTAbits.TXEN = 1;   // Activa la transmision
    RCSTAbits.CREN = 1;   // Habilita la recepcion continua
                       
    SPBRG = 25;           // Carga 25 a SPBRG
                       
    /* Velocidad a 9600 baudios con 0.16% de error*/
    
    /*Hasta aqui termina el codigo, que podria causar ruido*/
    
    while(1){

    imprimir_valor_leds();
    
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
         LCD_Print("Env");
         Canal0(2);            // realiza la conversion y tiempo de espera 2ms
         Tx_Dato(ADRESL);      // Transmite el dato de ADRESL
         ECO = Rx_Dato();      // Recepcion del eco del dato
         Tx_Dato(ADRESH);      // Transmite el dato de ADRESH
         ECO = Rx_Dato();      // Recepcion del eco del dato    
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