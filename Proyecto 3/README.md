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
## Carpetas por PIC
1. P3 es -> PIC16F873A
2. P3_NOR -> PIC16F873