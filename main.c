/*
 * main.c
 *
 * Created: 4/2/2026 8:14:16 PM
 *  Author: CrAzY
 */ 

//updated by Dakota

#include <avr/io.h>
#include <util/delay.h>
//header Files for Cleaner Code
#include "distanceSensor.h"
#include "lcdDisplay.h"
#include "io.h"

int main(void)
{
	//initial setup
	lcd_init();
	ultraSonicInit();
	IOInit();
	
    IO(); //runs IO function in an infinite loop (see io.c)
}
