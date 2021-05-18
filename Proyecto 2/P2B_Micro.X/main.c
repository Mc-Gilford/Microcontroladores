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
#include <time.h>

void iniciar_puertos();
int ECO;
int ADRES;

void set_configuraciones()
{
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
                       
    PORTB = 0x00;         // Limpia el puerto B
}

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
    
    //ADRES = (ADRESH << 8) | ADRESL;    // Almcena la conversion en la variable Peso1 
    
    ADIF = 0;                          // Borrado de bandera de conversion finalizada     
                                                              
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

void imprimir_valor_lcd() //Imprime el resulatado en los leds
{
    /*En caso de mal funcionamiento eliminar este codigo hasta el comentario de fin*/
    ADRESL = Rx_Dato();      // Recepcion del eco del dato
    Tx_Dato(ADRESL);      // Transmite el dato de ADRESL
    ADRESH = Rx_Dato();      // Recepcion del eco del dato 
    Tx_Dato(ADRESH);      // Transmite el dato de ADRESH                             
    /*Fin de codigo*/
    ADRES = (ADRESH << 8) | ADRESL;    // Almcena la conversion en la variable Peso1
}

void enviar_datos()
{
            Tx_Dato(ADRESL);      // Transmite el dato de ADRESL
            ECO = Rx_Dato();      // Recepcion del eco del dato
            Tx_Dato(ADRESH);      // Transmite el dato de ADRESH
            ECO = Rx_Dato();      // Recepcion del eco del dato                               
}

int main()
{
    iniciar_puertos();
    set_configuraciones();
    bucle:                 
            Canal0(2);            // realiza la conversion y tiempo de espera 2ms
            enviar_datos();
            //imprimir_valor_lcd();
            
            if(ADRES < 127)     // 0V
                PORTB = 0x00;
            if(ADRES > 127)     // 625 mv 
                PORTB = 0x01;
            if(ADRES > 255)     // 1.25 V
                PORTB = 0x03;
            if(ADRES > 352)     // 1.87 V
                PORTB = 0x07;
            if(ADRES > 511)     // 2.5 V
                PORTB = 0x0F;
            if(ADRES > 639)     // 3.12 V
                PORTB = 0x1F;
            if(ADRES > 767)     // 3.75 V
                PORTB = 0x3F;
            if(ADRES > 894)     // 4.37 V
                PORTB = 0x7F;
            if(ADRES > 1022)   // 5 V
                PORTB = 0xFF;
            
            goto bucle;                  // Bucle infinito
                    
}

void iniciar_puertos()
{
    
 /*   // Configuracion de puertos
    
    TRISA = 0x0F;         // puerto RA 0-1-2-3 son configurados como entrada
    TRISB = 0x00;         // Puerto B como de salida
    TRISC = 0xBF;          // Rx/DT como entrada y Tx/Ck como salida*/
    
    /*Configuracion de los puertos*/
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    /*TRIS 1 ENTRADA Y TRIS 0 SALIDA*/
    TRISA0 = 1;
    TRISA1 = 0;
    TRISA2 = 0;
    TRISC6 = 0;
    TRISC7 = 1;
    TRISB = 0x00; //Puertos B como salida
    
}