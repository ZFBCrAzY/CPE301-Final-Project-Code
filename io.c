#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include "distanceSensor.h"
#include "lcdDisplay.h"

//PB0 buzzer
//PC0 pushbutton

void IOInit(){

	//Sets PB0 as output
	DDRB |= (1 << PB0);
	//Sets PC0 as Input
	DDRC &= ~(1 << PC0);
	
	//set pull-up resistor on PC0
	PORTC |= (1 << PC0);
	
}

void IO(){
	
	char buffer[4];
	char Msg1[] = "Distance: ";
	char unitUsed[] = "Unit: cm";
	
	//runs in a repeated loop
	while(1){

		//wait until PC0 is low (button pressed)
		while(PINC & (1 << PC0)){}
		
		//clear LCD and prepare it for next print
		lcd_clear();
		lcd_gotoxy(0,0);
		
		unsigned int distance = getDistance("cm"); //measure avg distance between gun and object
		
		sprintf(buffer, "%u", distance); 
		
		//prints "Distance: "
		lcd_print(Msg1);
		
		//then prints the measured distance value
		//lcd_gotoxy(1,1);
		lcd_print(buffer);
		
		//prints which distance unit is used
		lcd_gotoxy(0,1);
		lcd_print(unitUsed);
		
		int buzCnt = 300;
		buzCnt = buzCnt * 2; 
		 for (unsigned int i = 0; i < buzCnt; i++) {
			 PORTB |= (1 << PB0);
			 _delay_us(250);

			 PORTB &= ~(1 << PB0);
			 _delay_us(250);
		 }
		
		
		//waits until PC0 is high again (button released) before running again
		while(!(PINC & (1 << PC0))){}
		
	}

}