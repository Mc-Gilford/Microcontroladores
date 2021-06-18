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

## Carpetas por PIC
1. P3 es -> PIC16F873A
2. P3_NOR -> PIC16F873