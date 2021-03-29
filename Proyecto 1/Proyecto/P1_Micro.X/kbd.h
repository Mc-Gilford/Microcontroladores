void disp_num(float num);
int get_num (char ch);
char scan_key(void);
//Puestos de columas y filas
#define r0 RB0 
#define r1 RB1
#define r2 RB2
#define r3 RB3
#define c0 RB4
#define c1 RB5
#define c2 RB6
#define c3 RB7

char scan_alpha()
{
if(c0==0 && r0==0){ __delay_ms(100);while(c0==0);return '7';}
if(c1==0 && r0==0){ __delay_ms(100);while(c1==0);return '8';}
if(c2==0 && r0==0){ __delay_ms(100);while(c2==0);return '9';}
if(c3==0 && r0==0){ __delay_ms(100);while(c3==0);return '/';}
r0=1;r1=0;r2=1;r3=1;
if(c0==0 && r1==0){  __delay_ms(100);while(c0==0);return '4';}
if(c1==0 && r1==0){  __delay_ms(100);while(c1==0);return '5';}
if(c2==0 && r1==0){  __delay_ms(100);while(c2==0);return '6';}
if(c3==0 && r1==0){  __delay_ms(100);while(c3==0);return '*';}
r0=1;r1=1;r2=0;r3=1;
if(c0==0 && r2==0){  __delay_ms(100);while(c0==0);return '1';}
if(c1==0 && r2==0){  __delay_ms(100);while(c1==0);return '2';}
if(c2==0 && r2==0){  __delay_ms(100);while(c2==0);return '3';}
//if(c3==0 && r2==0){  __delay_ms(100);while(c3==0);return '-';}
r0=1;r1=1;r2=1;r3=0;
if(c1==0 && r3==0){  __delay_ms(100);while(c1==0);return '0';}
//if(c3==0 && r3==0){  __delay_ms(100);while(c3==0);return '+';}
return 'n';
}

char scan_key()      //Scan the Pressed Key by user 
{
r0=0;r1=1;r2=1;r3=1;
if(c0==0 && r0==0){ __delay_ms(100);while(c0==0);return '7';}
if(c1==0 && r0==0){ __delay_ms(100);while(c1==0);return '8';}
if(c2==0 && r0==0){ __delay_ms(100);while(c2==0);return '9';}
if(c3==0 && r0==0){ __delay_ms(100);while(c3==0);return '/';} // Cambio a alfabeto
r0=1;r1=0;r2=1;r3=1;
if(c0==0 && r1==0){  __delay_ms(100);while(c0==0);return '4';}
if(c1==0 && r1==0){  __delay_ms(100);while(c1==0);return '5';}
if(c2==0 && r1==0){  __delay_ms(100);while(c2==0);return '6';}
if(c3==0 && r1==0){  __delay_ms(100);while(c3==0);return '*';} //Cambio a numeros
r0=1;r1=1;r2=0;r3=1;
if(c0==0 && r2==0){  __delay_ms(100);while(c0==0);return '1';}
if(c1==0 && r2==0){  __delay_ms(100);while(c1==0);return '2';}
if(c2==0 && r2==0){  __delay_ms(100);while(c2==0);return '3';}
if(c3==0 && r2==0){  LCD_Cmd(LCD_MOVE_CURSOR_LEFT);__delay_ms(100);while(c3==0);return '!';}//- Mover cursor a la izquierda
r0=1;r1=1;r2=1;r3=0;
if(c0==0 && r3==0){  LCD_Cmd(LCD_CLEAR);__delay_ms(100);while(c3==0);return '!';}//ON/c Borra todo
if(c1==0 && r3==0){  __delay_ms(100);while(c1==0);return '0';}
if(c2==0 && r3==0){  __delay_ms(100);while(c3==0);return '\0';}//= Borra un dato antes del cursor
if(c3==0 && r3==0){  LCD_Cmd(LCD_MOVE_CURSOR_RIGHT);__delay_ms(100);while(c3==0);return '!';}//+ Mover cursor a la dereche
return 'n';
}

int get_num(char ch)         //converting character into integer
{
switch(ch)
{
case '0': return 0; break;
case '1': return 1; break;
case '2': return 2; break;
case '3': return 3; break;
case '4': return 4; break;
case '5': return 5; break;
case '6': return 6; break;
case '7': return 7; break;
case '8': return 8; break;
case '9': return 9; break;
}
return 0;
}