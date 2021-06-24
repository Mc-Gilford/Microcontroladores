/*
 * Realizado por: Jose de Jesus Rodriguez Apaicio y Karla Reyes
 * Fecha: 6/23/21
 * PIC MAESTRO Control de ventiladores y LED, Practica 3
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
#include <pic16f873a.h>
#include "lcd.h"
#include "kbd.h"
#include <string.h>
#include "ftoaa.h"

#define ADDRA 0xA0 //Direccion de PIC1
#define ADDRB 0xA1 // Direccion PIC2


char number[4];
int i =0;
int length_grupo = 5;
char grupo[] = {"3CV16"};
int length_presentacion = 38;
char presentacion[] = {"Jose Rodriguez y Karla Reyes"};
int length_saludo = 22;
char saludo[] = {"Hola Mundo bienvenido!"};
int ECO;
int va=0,vb=0;
/*Para envio de datos*/
int ADRES;
unsigned char envio;

void load_values()
{  
        eeprom_write(0x00,4);
        eeprom_write(0x01,5);
        eeprom_write(0x02,3);
        eeprom_write(0x03,1);
        eeprom_write(0x04,2);
        eeprom_write(0x05,0);
}

void iniciar_puertos()
{
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
 
    /*Al poner TRIS en 1 significa entrada y 0 salida*/
    
    /*Confgurando los puertos de C*/
    TRISCbits.TRISC0 = 0; 
    TRISCbits.TRISC1 = 0;
    //TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 1; // SCL como entrada
    TRISCbits.TRISC4 = 1; // SDA como salida
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

void conditional_screen(int x)
{
    char msj[]="Cambiar cond.";
    char con[]="1.Si 2.No";
    LCD_Cmd(LCD_CLEAR);
    if(x==1)
    {
        strcat(msj," V");
    }
    else if(x==2)
    {
        strcat(msj," F1");
    }
    else if(x==3)
    {
        strcat(msj," F2");   
    }
    LCD_Goto(1,1);
    LCD_Print(msj);
    LCD_Goto(1,2);
    LCD_Print(con);
}


void ventilator_screen(float voltaje, int vrm, int ventilator_number)
{
    LCD_Cmd(LCD_CLEAR);
    unsigned char vol[]="Voltaje: ";
    unsigned char vel[]="Vel ";
    char vol_value[]="";
    char vel_number[]="";
    char vel_value[]="";
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

/*Configuracion del modulo MSSP configuracion como modulo  maestro*/
void C_config(const unsigned long c)
{
    SSPCON =0b00101000; // Configuracion y activacion del MSSP en modo T2C maestro
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*c))-1; // Velocidad de transmision
    SSPSTAT = 0;
    /*Dado que la configuracion de nuestros PIN C3 Y C4 ya estan configurados ya no tenemos que proceder a realizar alguna
     accion */
}

/*Funcion de condicion de inicio*/
void C_inicio()
{
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); // Transmision en progreso
    SSPCON2bits.SEN =1; // Activa secuencia de inicio
}

/* Condicion de parada*/
void C_parada()
{
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); // Transmision en progreso
    SSPCON2bits.PEN =1; // Activa secuencia de parada
}

//Funcion de transmision 
void Tx_Dato(unsigned char x)
{
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); // Transmision en progreso
    SSPBUF = x; // transmicion de dato
}

void write_value(int direction, int value){
        eeprom_write(direction,value);
}

void key_writing_value()
{
   char c;
   LCD_Cmd(LCD_CLEAR);
   LCD_Goto(1,1);
   LCD_Print("Escribe valor");  
   c = keypad_readkey();
   va = atoi(c);
   LCD_Goto(1,2);
   LCD_PutC(c);
   __delay_ms(50);
   LCD_Cmd(LCD_CLEAR);
   LCD_Goto(1,1);
   LCD_Print("Escribe Direccion");
   c = keypad_readkey();
   vb = atoi(c);
   LCD_Goto(1,2);
   LCD_PutC(c);
   __delay_ms(50);
   LCD_Cmd(LCD_CLEAR);
   
}

void screen_selector(char c, char k)
{
    
    LCD_Cmd(LCD_CLEAR);
    LCD_Goto(1,1);
    if(c=='1')
    {
        LCD_Print("Nuevo Valor");
        LCD_Goto(1,2);
        float v=5.12;
        char value[]="";
        int dir=0, val=0;
        /*EEPROM WRITE
        Escribe la direccion de alojamiento, y el valor*/
        key_writing_value();
        //val=key_writing_value();
        
        //write_value(dir,val);
        itoa(value,v,10);
        strcat(value," mv");
        LCD_Print(value);
    }
    else if(c=='2')
    {
         LCD_Print("Saliendo");
        __delay_ms(50);
        LCD_Cmd(LCD_CLEAR);
    }
    else{
        
        LCD_Print("Opcion Invalida");
        __delay_ms(50);
        //screen_selector(c);
        LCD_Cmd(LCD_CLEAR);
    }
}

void selector_type(char c)
{
    char k=c;
    if(c=='A')
        {
            if(i==1){
                ventilator_screen(1.1,1000,1);
            ++i;
            }
            else if(i==2){
                ventilator_screen(2.2,1000,2);
                --i;
            }
            
        }
    else if(c=='B')
    {
        conditional_screen(1);
        c = keypad_getkey();
        screen_selector(c,k);
    }
    else if(c=='C')
    {
        conditional_screen(2);
        c = keypad_getkey();
        screen_selector(c,k);
    }
    else if(c=='D')
    {
        conditional_screen(3);
        c = keypad_getkey();
        screen_selector(c,k);
    }
    else {
        envio=c;
        C_inicio(); //Envia la condicion de inicio
        Tx_Dato(0xA0); //Envio de direccion de 7 bits y orden de escritura
        Tx_Dato(envio); // Envio conversion del ADC parte baja
        C_parada(); // Condicion de parada
        __delay_ms(100); //Retraso para evitar errores
    }
}

void main()
{
    i=1; //Para concatenar dentro del array  
    //set_configuraciones();
    load_values();
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
    char c = keypad_getkey();
        LCD_PutC(c);
        selector_type(c);
    __delay_ms(60);
    }
}