#pragma warning disable 520

#include <stdint.h>

#define LCD_FIRST_ROW          0x80
#define LCD_SECOND_ROW         0xC0
#define LCD_THIRD_ROW          0x94
#define LCD_FOURTH_ROW         0xD4
#define LCD_CLEAR              0x01
#define LCD_RETURN_HOME        0x02
#define LCD_ENTRY_MODE_SET     0x04
#define LCD_CURSOR_OFF         0x0C
#define LCD_UNDERLINE_ON       0x0E
#define LCD_BLINK_CURSOR_ON    0x0F
#define LCD_MOVE_CURSOR_LEFT   0x10
#define LCD_MOVE_CURSOR_RIGHT  0x14
#define LCD_TURN_ON            0x0C
#define LCD_TURN_OFF           0x08
#define LCD_SHIFT_LEFT         0x18
#define LCD_SHIFT_RIGHT        0x1E


//LCD module connections
#define LCD_RS       PORTAbits.RA0
#define LCD_RW       PORTAbits.RA1
#define LCD_EN       PORTAbits.RA2
/*#define LCD_D0       PORTBbits.RB0
#define LCD_D1       PORTBbits.RB1
#define LCD_D2       PORTBbits.RB2
#define LCD_D3       PORTBbits.RB3*/
#define LCD_D4       PORTBbits.RB4
#define LCD_D5       PORTBbits.RB5
#define LCD_D6       PORTBbits.RB6
#define LCD_D7       PORTBbits.RB7
#define LCD_RS_DIR   TRISAbits.TRISA0
#define LCD_RW_DIR   TRISAbits.TRISA1
#define LCD_EN_DIR   TRISAbits.TRISA2
/*#define LCD_D0_DIR   TRISBbits.TRISB0
#define LCD_D1_DIR   TRISBbits.TRISB1
#define LCD_D2_DIR   TRISBbits.TRISB2
#define LCD_D3_DIR   TRISBbits.TRISB3*/
#define LCD_D4_DIR   TRISBbits.TRISB4
#define LCD_D5_DIR   TRISBbits.TRISB5
#define LCD_D6_DIR   TRISBbits.TRISB6
#define LCD_D7_DIR   TRISBbits.TRISB7
//End LCD module connections

#ifndef LCD_TYPE
   #define LCD_TYPE 2           // 0=5x7, 1=5x10, 2=2 lines
#endif

__bit RS;

void LCD_Write_Nibble(uint8_t n);
void LCD_Cmd(uint8_t Command);
void LCD_Goto(uint8_t col, uint8_t row);
void LCD_PutC(char LCD_Char);
void LCD_Print(char* LCD_Str);
void LCD_Begin();

void LCD_Write_Nibble(uint8_t n)
{
  LCD_RS = RS;
  LCD_D4 = n & 0x01;
  LCD_D5 = (n >> 1) & 0x01;
  LCD_D6 = (n >> 2) & 0x01;
  LCD_D7 = (n >> 3) & 0x01;

  // send enable pulse
  LCD_EN = 0;
  __delay_us(1);
  LCD_EN = 1;
  __delay_us(1);
  LCD_EN = 0;
  __delay_us(100);
}

void LCD_Cmd(uint8_t Command)
{
  RS = 0;
  LCD_Write_Nibble(Command >> 4);
  LCD_Write_Nibble(Command);
  if((Command == LCD_CLEAR) || (Command == LCD_RETURN_HOME))
    __delay_ms(2);
}

void LCD_Goto(uint8_t col, uint8_t row)
{
  switch(row)
  {
    case 2:
      LCD_Cmd(LCD_SECOND_ROW + col - 1);
      break;
    case 3:
      LCD_Cmd(LCD_THIRD_ROW  + col - 1);
      break;
    case 4:
      LCD_Cmd(LCD_FOURTH_ROW + col - 1);
    break;
    default:      // case 1:
      LCD_Cmd(LCD_FIRST_ROW  + col - 1);
  }

}

void LCD_PutC(char LCD_Char)
{
  RS = 1;
  LCD_Write_Nibble(LCD_Char >> 4);
  LCD_Write_Nibble(LCD_Char );
}

void LCD_Print(char* LCD_Str)
{
  uint8_t i = 0;
  RS = 1;
  while(LCD_Str[i] != '\0')
  {
    LCD_Write_Nibble(LCD_Str[i] >> 4);
    LCD_Write_Nibble(LCD_Str[i++] );
  }
}

void LCD_Begin()
{
  RS = 0;
  LCD_RS     = 0;
  LCD_RW     = 0;
  LCD_EN     = 0;
 /* LCD_D0     = 0;
  LCD_D1     = 0;
  LCD_D2     = 0;
  LCD_D3     = 0;*/
  LCD_D4     = 0;
  LCD_D5     = 0;
  LCD_D6     = 0;
  LCD_D7     = 0;
  LCD_RS_DIR = 0;
  LCD_RW_DIR = 0;
  LCD_EN_DIR = 0;
 /* LCD_D0_DIR = 0;
  LCD_D1_DIR = 0;
  LCD_D2_DIR = 0;
  LCD_D3_DIR = 0;*/
  LCD_D4_DIR = 0;
  LCD_D5_DIR = 0;
  LCD_D6_DIR = 0;
  LCD_D7_DIR = 0;
  __delay_ms(40);
  LCD_Cmd(3);
  __delay_ms(5);
  LCD_Cmd(3);
  __delay_ms(5);
  LCD_Cmd(3);
  __delay_ms(5);
  LCD_Cmd(LCD_RETURN_HOME);
  __delay_ms(5);
  LCD_Cmd(0x20 | (LCD_TYPE << 2));
  __delay_ms(50);
  LCD_Cmd(LCD_TURN_ON);
  __delay_ms(50);
  LCD_Cmd(LCD_CLEAR);
  __delay_ms(50);
  LCD_Cmd(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
  __delay_ms(50);
  LCD_Cmd(LCD_BLINK_CURSOR_ON);
  __delay_ms(50);
}