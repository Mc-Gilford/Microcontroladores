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

![Imagen de Error](relative/path/to/CaptureError.png?raw=true "Error Puertos C")
![Error](/CaptureError.png)

Error en el puerto C, se piensa en un posible problema conforme alguna configuracion con estos, dado que no envia bien
los datos atraves de los puertos.

## Carpetas por PIC
1. P3 es -> PIC16F873A
2. P3_NOR -> PIC16F873