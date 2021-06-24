# Practica 3 Microcontroladores


## Descripcion de Programa
Dentro de esta practica nosotros tenemos un PIC maestro el cual sera el PIC16F873A
el cual su tarea sera el manejo del LCD mediante los puertos B, y el control del keypad
en los puertos A y C, mediante el manejo del keypad se estableceran las siguientes funciones:
* Presionando A visualizando el ventilador 1 con su voltaje y VRM
* Presionando B visualizando el ventilador 2 con sy voltaje y VRM
* "#" Aceptar y el "*" Rechazar
Este a la vez cargara dentro de la EPROM para ser guardados

El PIC12F1822 manejara un led que prendera y apagara segun los valores que reciba por parte del
microcontrolador maestro PIC16F873A por las salidas SCL y SDA, las cuales enviara al PIC maestro
para mostrar el voltaje con el cual el led prende.

EL PIC16F819 manejara 2 ventiladores, segun los valores enviados mediante los puertos SCL y SDA este
enviara los valores de cada ventilador en proceso.

### Funcionamiento Explicado
En la practica nuestro PIC16F873A (Maestro) sera el principal en llevar juntos los procesos de ambos PICS
en los cuales su principal objetivo sera la recepcion de cada uno de los valores que los PICS le envien mediante
los puertos SCL y SDA para almacenarlos en la EPROM, en el caso del PIC16F819 que es el que manejara ambos ventiladores
dado un voltaje ira activando cada uno de los ventiladores y al realizar la activacion de algun ventilador enviara esta
informacion al PIC16F873A (Maestro), en el caso del PIC12F1822 que es el encargado de encender y prender el led mediante el
voltaje que este reciba, una vez que prenda o apague el led le enviara esta informacion a nuestro PIC16F873A (Maestro) para que
este los guarden en la EPROM, el PIC16F873A sera tecnicamente nuestro control y administrador de visualizacion, mediante cierta operaciones pasara a un proceso para visualizar cada uno de los pines esclavos que le envien la informacion, y mostrara los
resultado que estos le envien.

![Error](https://github.com/McGilfordJose/Microcontroladores/blob/main/Proyecto%203/CaptureError.PNG)

Error en el puerto C, se piensa en un posible problema conforme alguna configuracion con estos, dado que no envia bien
los datos atraves de los puertos.

Nota: Estaba activado el UART, al quitarlo funciona correctamente


### Microcontrolador 1 PIC16F873A
Dentro de este PIC se hayo que en el esquema estaba mal diseñado dado que los valores de las FILAS que van de ENTRADA deben de ir de SALIDA, mientras que en las COLUMNAS en vez de ir de SALIDA deben de ir de ENTRADA. Este error se visualizo dado que el PIC, no obtenia valores del KEYPAD.

Tambien debemos realizar un configuracion de los puertos de A para que sean digitales, en este caso deseamos que todos los puertos de A por lo cual se realizo con la siguiente instruccion:
```C
ADCON1 = 0x07;
```
Uno de los otros errores fue dentro del PORT RA4 dado que este es un puerto es pull up para salidas, para la solucion de este se hizo la siguiente configuracion, para poder usarlo como salida.

### Configuracion nueva
![Funcionando](https://github.com/McGilfordJose/Microcontroladores/blob/main/Proyecto%203/Circuito%20RA4%20Funcionando.PNG)

### Configuracion pasada
![Error](https://github.com/McGilfordJose/Microcontroladores/blob/main/Proyecto%203/Circuito%20No%20Funcionando.PNG)

### Anexo de configuracion
![Anexo](https://github.com/McGilfordJose/Microcontroladores/blob/main/Proyecto%203/Added_Part.PNG)

## KEYPAD

Para el KEYPAD se hizo la configuracion respecto al que se puede ver en la imagen:
![Keypad](https://circuitdigest.com/sites/default/files/inlineimages/4x4-matrix-keypad.gif)

El interpretado es el siguiente:
               | Voltaje: xx.x mv |
               | Vel_1: xxxx RPM  |    Si se presiona una tecla "A" que despliegue lo siguiente
                ------------------
             
                __________________
               | Voltaje: xx.x mv |
               | Vel_2: xxxx RPM  |    Solo cambia esta linea
                ------------------              

                __________________
               | Cambiar cond. V  |
               |  Si: 1    No: 2  |    Si se presiona una tecla "B" que despliegue lo siguiente
                ------------------
               
                __________________
               | Cambiar cond. F1 |
               |  Si: 1    No: 2  |    Si se presiona una tecla "C" que despliegue lo siguiente
                -------------------- 

                __________________
               | Cambiar cond. F2 |
               |  Si: 1    No: 2  |    Si se presiona una tecla "D" que despliegue lo siguiente
                -------------------- 

                Cuando se acepta cambiar el valor (de cualquiera de las condiciones) se debe desplegar este
                __________________
               |    Nuevo valor:  |
               |     xx.xx mv     |    Si se presiona una tecla "#" acepta el valor, si se presiona "*" No acepta el valor
                ------------------     ( lo mismo aplica para velocidad 1 y velocidad 2 )

![Menu](https://github.com/McGilfordJose/Microcontroladores/blob/main/Proyecto%203/New%20Interface.PNG)
### EEPROM
Para la parte de EEPROM dentro de nuestro PIC16F873A (Maestro) nosotros tendremos configurados unos valos determinados por el equipo haciendo uso de las siguientes lineas para realizar la asignacion de valores en las direcciones de memoria
Para hacer uso de nuestro EEPROM debemos tener la siguiente instruccion:
```C
#pragma config CPD = OFF // Dta EEPROM Memory
```
```C
void load_values()
{  
    //Direcciones, Valores
        eeprom_write(0x00,4); 
        eeprom_write(0x01,5);
        eeprom_write(0x02,3);
        eeprom_write(0x03,1);
        eeprom_write(0x04,2);
        eeprom_write(0x05,0);
}
```
Dentro de este nosotros tenemos una interfaz para la asignacion de valores a nuestras direcciones y poder hacer uso de ellas mediante la siguiente instruccion:
```C
void write_value(int direction, int value){
        eeprom_write(direction,value);
}
```
### Interfaz I2C
El PIC16F873A Maestro recibe el voltaje, el cual se comunicaran con los PIC esclavos mediante la comunicacion I2C, el cual tendra una frecuencia de 100kbps. Como tenemos 2 esclavos se usara 2 direcciones.
Se utilizara un variable definida para la direccion de nuestro PICS esclavos mediante las siguiente instruccion:
```C
#define ADDRA 0xA0 //Direccion de PIC1
#define ADDRB 0xA1 // Direccion PIC2
```
Crearemos nuestras variables ADRES como int donde vamos hacer la concadenacion de la conversion analogico-digital y un char para que no nos manden warning al realizar el envio de nuestro dato.
```C
    int ADRESA;
    int ADRESB;
    int ADRES;
    unsigned char envio;
``` 
Despues usaremos una funcion para analogico digital
```C
// Funcion de conversion Analogico Digital 
void Canal0(int z)    
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

```

## NOTAS
* Dentro del PIC hacer la configuracion como esta en nuestro esquema
* Se observa que a mayor cantidad de codigo, mayor tiempo de espera en la ejecucion de la simulacion tiempo aproximado (10 min)
* Dentro de nuestro PIC tener una frecuencia minima de 4MHz, para que su ejecucion sea mas rapida
![FrecuenciaPIC](https://github.com/McGilfordJose/Microcontroladores/blob/main/Proyecto%203/PICFrec.jpeg)
* MPLAB deshabilito la forma de conversion para numeros flotante, no se pueden use ftoa(), ni sprintf() dentro del codigo vienen comentado dado que estas son las soluciones mas viables para su operacion

## Carpetas por PIC
1. P3 es -> PIC16F873A
2. P3_NOR -> PIC16F873