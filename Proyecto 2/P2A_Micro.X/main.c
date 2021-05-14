#pragma config FOSC = XT // OSCILADOR
#pragma config WDTE = ON // Perro Guardian
#pragma config PWRTE = ON // Power Up Tiempo habilitado
#pragma config BOREN = OFF // Brown out reset
#pragma config LVP = OFF // Low volatge 
#pragma config CPD = OFF // Dta EEPROM Memory
#pragma config WRT = OFF //Flash Program Memory Write
#pragma config CP = OFF // Flash Program Memory Code

#define _XTAL_FREQ 32000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f873.h>

// Declaracion de variable global

int ADRES;
void Delay_ms(int time)
{
    /* Condiciones para usar el TMR0*/
    /*Prescalar en 4 para TMR0*/
    long i = 0; //Contador i para ciclo for
    TMR0 = 0; //Ecuacion para el numero de ciclos
retardo:    if(i<=time)
    {
        if(TMR0<=136) // ciclo de 1 milisegundo
        {
mili:       goto mili;
            i++;
            TMR0 = 0;  //Limpia el temporizador para otro ciclo
            goto retardo; 
        }
    }
}

void CanalIO(int x)
{
    CHS2 =0; // Seleccion del canal analogo
    CHS1 = 0;
    CHS0 = 0;
    ADON = 1;      // Activa el modo del convertidor analogico digital
    Delay_ms(x);  // Tiempo de adquision
    GO = 1;
    ADCA: if (ADIF == 0) //Espera hasta que termine la conversion
        goto ADCA;
    ADRES = (ADRESH<<0) | ADRESL; // Almacena la conversion en la variable Pesol
    /*Aplicamos un OR de ADRESH o AADRESL*/
    ADIF = 0; // Borrado de bandera de conversion finalizada
    
}

int main()
{
    /*Configuracion de los puertos*/
    TRISA = 0x0F; //Puertos R0-R3
    TRISB = 0x00; //Puertos B como salida
    /*Configuracion del convertidor analogico digital*/
    ADCON0 = 0x80; //32 x Tosc
    ADCON1 = 0x8E; //Los 8 bits mas significativos (ADRESH) son 0
    // Puerto RA0 es configurado como Analogico
    // Configuracion de las interrupciones
    ADIF = 0; // Borra el setelizador de interrupciones del ADC
    /* Configuracion del temporizador*/
    OPTION_REG = 0x51; //Configura el prescaler a 4
    TMR0 = 0; //
    PORTB = 0x00; //Limpia puerto B
bucle:    CanalIO(1); // Realiza la conversion y tiempo de espera 1ms
    // Comparacion y encendido del led
          
        if(ADRES<127)//0
            PORTB = 0x00; 
        if(ADRES>127) //625mv
            PORTB = 0x01;
        if(ADRES>255) //1.25
            PORTB = 0x03;
        if(ADRES>382) //1.87
            PORTB = 0x07;
        if(ADRES>511) // 2.5
            PORTB = 0x0F;
        if(ADRES>639) //3.12
            PORTB = 0x1F; 
        if(ADRES>767)//3.75
            PORTB = 0x3F;
        if(ADRES>894)//4.37
            PORTB = 0x7F;
        if(ADRES>1022) //5V
            PORTB = 0xFF;
goto bucle;
}

