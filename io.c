#include <stdlib.h>
#include <util/delay.h>
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
		lcd_gotoxy(1,1);
		
		unsigned int distance = getDistance(); //measure avg distance between gun and object
		
		utoa(distance, buffer, 10);   //convert distance to char array (buffer)
		
		//prints "Distance: "
		lcd_print(Msg1);
		
		//then prints the measured distance value
		lcd_gotoxy(11,1);
		lcd_print(buffer);
		
		//prints which distance unit is used
		lcd_gotoxy(1,2);
		lcd_print(unitUsed);
		
		//drive PB0 high (turn on buzzer for 300ms)
		PORTB |= (1 << PB0); 
		_delay_ms(500);
		//drive PB0 low (turn buzzer off)
		PORTB &= ~(1 << PB0);
		
		//waits until PC0 is high again (button released) before running again
		while(!(PINC & (1 << PC0))){}
	
	}

}
