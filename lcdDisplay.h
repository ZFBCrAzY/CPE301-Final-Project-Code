/*
 * lcdDisplay.h
 *
 * Created: 4/2/2026 8:16:34 PM
 *  Author: CrAzY
 */ 


#ifndef LCDDISPLAY_H_
#define LCDDISPLAY_H_

#include <avr/io.h>
#include <stdint.h>

void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_print(const char *str);
void lcd_clear(void);
void lcd_gotoxy(uint8_t col, uint8_t row);

#endif /* LCDDISPLAY_H_ */
