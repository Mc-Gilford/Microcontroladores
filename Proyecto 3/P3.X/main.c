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
#include <pic16f873a.h>
#include "lcd.h"
#include "kbd.h"
#include <string.h>
#include "ftoaa.h"

void iniciar_puertos();
void inicio_presentacion(int, char*);
void ventilator_screen(float , int , int );
void selector_type(char );
//Agregar variable global
char number[4];

int length_grupo = 5;
char grupo[] = {"3CV16"};
int length_presentacion = 38;
char presentacion[] = {"Jose Rodriguez y Karla Reyes"};
int length_saludo = 22;
char saludo[] = "Hola Mundo bienvenido!";
int ECO;
int ADRES;

/*Jose de Jesus Rodriguez Apaicio y Karla Reyes*/


int main()
{
    int i=1; //Para concatenar dentro del array  
    //set_configuraciones();
    iniciar_puertos();
    /*Iniciar LCD*/
    LCD_Begin();
    inicio_presentacion(length_saludo, saludo);
    __delay_ms(20);
    inicio_presentacion(length_presentacion,presentacion);
    __delay_ms(20);
    inicio_presentacion(length_grupo,grupo);
    __delay_ms(20);
    LCD_Goto(1, 1);    
    __delay_ms(50);
    
    while(1){
    //imprimir_valor_leds(); 
    char c = keypad_getkey();
        LCD_PutC(c);
        if(c=='A')
        {
            if(i==1){
                ventilator_screen(1.2,1000,1);
            ++i;
            }
            else if(i==2){
                ventilator_screen(2.1,1000,2);
                --i;
            }
            
        }
    __delay_ms(500);
    }
}

void iniciar_puertos()
{
   
        /*Seteo de entradas PUERTO C*/
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
 
    /*Al poner TRIS en 1 significa entrada y 0 salida*/
    
    /*Confgurando los puertos de C*/
    TRISCbits.TRISC0 = 0; 
    TRISCbits.TRISC1 = 0;
    //TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    //TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    //TRISCbits.TRISC7 = 0;
    //TRISC = 0X10;
    /*Configuran puertos de A como salida*/   
    TRISAbits.TRISA0 = 1; 
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA4 = 0; 
    TRISAbits.TRISA5 = 0;
    /*Activamos el PULL UP para leer cada entrada del teclado*/
   // OPTION_REG &= 0x7F;
    //ADCON1 =  0b00000110;
    ADCON1 = 0x07;
    
}

void inicio_presentacion (int length, char *str)
{
    LCD_Goto(1,1);
    LCD_Print(str);
    __delay_ms(25);
    for(int i=0;i<length;i++){
        LCD_Cmd(LCD_SHIFT_LEFT);
        __delay_ms(20);
    }   
    __delay_ms(10);
    LCD_Cmd(LCD_CLEAR);
    LCD_Goto(1, 1);
}


void ventilator_screen(float voltaje, int vrm, int ventilator_number)
{
    unsigned char vol[16]="Voltaje: ";
    unsigned char vel[16]="Vel ";
    char vol_value[3];
    char vel_number[1];
    char vel_value[4];
    /*
      Voltaje: xx.x mv   
      Vel_2: xxxx RPM
    */
    LCD_Goto(1,1);
    //sprintf(vol, "Voltaje: %.1f mv", voltaje); 
    //ftoa_safe(voltaje,vol_value);
    itoa(vol_value,voltaje,10);
    strcat(vol,vol_value);
    //sprintf(vol, "Voltaje: %.1f mv", voltaje);
    LCD_Print(vol);
    LCD_Goto(1,2);
    itoa(vel_number,ventilator_number,10);
    strcat(vel,vel_number);
    strcat(vel,": ");
    itoa(vel_value,vrm,10);
    strcat(vel,vel_value);
    strcat(vel," RPM");
    //sprintf(vel, "Vel %d: %d RPM", ventilator_number, vrm);
    LCD_Print(vel);
}