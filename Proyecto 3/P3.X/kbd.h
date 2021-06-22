void disp_num(float num);
int get_num (char ch);
char scan_key(void);
//Puestos de columas y filas
#define HIGH 1
#define LOW 0
#define r3 RA4 
#define r2 RA5
#define r1 RC0 //FILA 3
#define r0 RC1

#define c0 RA0
#define c1 RA1
#define c2 RA2
#define c3 RA3


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

unsigned char keypad_readkey(void)
{
    r0 = HIGH;		
    r1 = LOW;
    r2 = LOW;
    r3 = LOW;
    __delay_us(30);
  
    if(r0==HIGH && r1==LOW && r2==LOW && r3==LOW)  {   
        if (c0 == HIGH) return 'Z';		// Key '1' 
        if (c1 == HIGH) return '0';		// Key '2' 
        if (c2 == HIGH) return '=';		// Key '3'
        if (c3 == HIGH) return '+';		// Key '3' 
    }
    r0 = LOW;		
    r1 = HIGH;
    r2 = LOW;
    r3 = LOW;
    __delay_us(30);
  
    if(r0==LOW && r1==HIGH && r2==LOW && r3==LOW)  {   
        if (c0 == HIGH) return '1';		// Key '1' 
        if (c1 == HIGH) return '2';		// Key '2' 
        if (c2 == HIGH) return '3';		// Key '3'
        if (c3 == HIGH) return '.';		// Key '.' 
    }
    
    r0 = LOW;		
    r1 = LOW;
    r2 = HIGH;
    r3 = LOW;
    __delay_us(30);
  
    if(r0==LOW && r1==LOW && r2==HIGH && r3==LOW)  {   
        if (c0 == HIGH) return '4';		// Key '4' 
        if (c1 == HIGH) return '5';		// Key '5' 
        if (c2 == HIGH) return '6';		// Key '6'
        if (c3 == HIGH) return '*';		// Key '*' 
    }
    
    r0 = LOW;		
    r1 = LOW;
    r2 = LOW;
    r3 = HIGH;
    __delay_us(30);
  
    if(r0==LOW && r1==LOW && r2==LOW && r3==HIGH)  {   
        if (c0 == HIGH) return '7';		// Key '7' 
        if (c1 == HIGH) return '8';		// Key '8' 
        if (c2 == HIGH) return '9';		// Key '9'
        if (c3 == HIGH) return 'A';		// Key '/' 
    }
	return 'x';					// if no key press, the register is 0xFF
}

unsigned char keypad_getkey(void)
{
	unsigned char key = 'x';	
	
	// wait until any key is pressed
	while(key == 'x')
		key = keypad_readkey();
	
	// wait until that key is released
	while(keypad_readkey() != 'x');
	
	return key;
}	