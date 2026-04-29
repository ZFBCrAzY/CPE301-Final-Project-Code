#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcdDisplay.h"

/*
LCD Control Pins
RS -> PB2
RW -> PB3
EN -> PB4
*/
#define LCD_CTRL_DDR   DDRB
#define LCD_CTRL_PORT  PORTB

#define LCD_RS         PB2
#define LCD_RW         PB3
#define LCD_EN         PB4

/*
LCD Data pins
DB4 -> PD0
DB5 -> PD1
DB6 -> PD2
DB7 -> PD3

DB4-DB7 are used for 4-bit mode
*/
#define LCD_DATA_DDR   DDRD
#define LCD_DATA_PORT  PORTD

#define LCD_DB4        PD0
#define LCD_DB5        PD1
#define LCD_DB6        PD2
#define LCD_DB7        PD3

//Function Prototypes
static void lcd_pulse_enable(void);
static void lcd_send_nibble(uint8_t nibble);
//Generate Enable Pulse for LCD

/*
The LCD runs data only when EN goes:
LOW->HIGH->LOW
This function is implemented to create that pulse
*/
static void lcd_pulse_enable(void)
{
	LCD_CTRL_PORT |= (1 << LCD_EN); //Sets EN High
	_delay_us(2);					//small delay
	LCD_CTRL_PORT &= ~(1 << LCD_EN);// Sets EN Low
	_delay_us(100);	//Time for LCD to process
}
/*
Send 4-bit data(nibble) to LCD

Since this project is using 4-bit mode, we send the data in two areas:
Upper 4 bits and Lower 4 bits
Each bit of the nibble is mapped in DB4-DB7
*/
static void lcd_send_nibble(uint8_t nibble)
{
	//Clears the previous data on DB4-DB7
	LCD_DATA_PORT &= ~((1 << LCD_DB4) |
	(1 << LCD_DB5) |
	(1 << LCD_DB6) |
	(1 << LCD_DB7));
//Sets each bit if needed
	if (nibble & 0x01) LCD_DATA_PORT |= (1 << LCD_DB4);
	if (nibble & 0x02) LCD_DATA_PORT |= (1 << LCD_DB5);
	if (nibble & 0x04) LCD_DATA_PORT |= (1 << LCD_DB6);
	if (nibble & 0x08) LCD_DATA_PORT |= (1 << LCD_DB7);
// Tells LCD to read the nibble
	lcd_pulse_enable();
}

/*
Send Commands to LCD

RS = 0 (Command Mode)
RW = 0 (Write Mode)

*/
void lcd_command(uint8_t cmd)
{
	LCD_CTRL_PORT &= ~(1 << LCD_RS);  // RS = 0 for command
	LCD_CTRL_PORT &= ~(1 << LCD_RW);  // RW = 0 for write
	// Send upper 4 bits(first)
	lcd_send_nibble(cmd >> 4);
	//Send lower 4 bits
	lcd_send_nibble(cmd & 0x0F);

	//Providing delays for certain commands
	if (cmd == 0x01 || cmd == 0x02)
	_delay_ms(3);
	else
	_delay_us(100);
}
/*
Send data to LCD
RS = 1 (Data Mode)
Allows for printing characters
*/
void lcd_data(uint8_t data)
{
	LCD_CTRL_PORT |= (1 << LCD_RS);   // RS = 1 for data
	LCD_CTRL_PORT &= ~(1 << LCD_RW);  // RW = 0 for write

// Send upper and lower nibbles
	lcd_send_nibble(data >> 4);
	lcd_send_nibble(data & 0x0F);

	_delay_us(100);
}
/*
Initialize LCD
As for the initialization process, the LCD is forced into 8-bit mode
and we switch to 4-bit and configure the display setting
*/
void lcd_init(void)
{
	// Set control pins as outputs
	LCD_CTRL_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN);

	// Set data pins (DB4-DB7) as output
	LCD_DATA_DDR |= (1 << LCD_DB4) |
	(1 << LCD_DB5) |
	(1 << LCD_DB6) |
	(1 << LCD_DB7);
	//Initialize the control pins LOW
	LCD_CTRL_PORT &= ~((1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN));

	_delay_ms(40);

	// 4-bit initialization sequence
	lcd_send_nibble(0x03);
	_delay_ms(5);

	lcd_send_nibble(0x03);
	_delay_us(200);

	lcd_send_nibble(0x03);
	_delay_us(200);

	lcd_send_nibble(0x02);  // Switch to 4-bit mode
	_delay_us(200);

	lcd_command(0x28);  // 4-bit mode, 2 lines, 5x8 font
	lcd_command(0x0C);  // Display ON, cursor OFF
	lcd_command(0x06);  // Entry mode: move cursor right
	lcd_command(0x01);  // Clear display
	_delay_ms(3);
}

//Clears LCD Screen
void lcd_clear(void)
{
	lcd_command(0x01);
	_delay_ms(3);
}
/*
Set Cursor Position

Row 0 -> Address starts at 0x80
Row 1 -> Address starts at 0xC0
*/
void lcd_gotoxy(uint8_t col, uint8_t row)
{
	 if (row == 0)
	 lcd_command(0x80 + col);
	 else
	 lcd_command(0xC0 + col);
}
//Print String to LCD

void lcd_print(const char *str)
{
//loops until null character
	while (*str)
	{
		lcd_data(*str++);//Sends character than moves next
	}
}
