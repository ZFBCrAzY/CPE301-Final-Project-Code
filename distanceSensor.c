#include "distanceSensor.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Function: Sets up Ultrasonic sensor setting
//
void ultraSonicInit(){
    //sets Pin Directions Needed For Ultrasonic
    //Sets Trig as output
    DDRD |= (1 << TRIG);
    //Sets Echo as Input
    DDRD &= ~(1 << ECHO);
}

//sets up timer to get echo pulse time
unsigned int measureDistance(){
    //holds the time 
    unsigned int time = 0;
    //counter for loop
    unsigned int count = 0;
    //Collects 5 data points
    while(count < 5){
    //Insures trig is low for pulse
    PORTD &= ~(1 << TRIG);
    //Delay
    _delay_us(5);
    //sends pulse to trig
    PORTD |= (1 << TRIG);
    // Delay for 10 us pulse
    _delay_us(10);
    PORTD &= ~(1 << TRIG);
    //sets up timer for measurement
    TCCR1A = 0x00;
    TCCR1B |= (1 << CS11);
    //waits until Echo is high
    while(!(PIND & (1 << ECHO))){}
    //sets timer to 0 for count
    TCNT1 = 0;
    //wait until ECHO is low
    while(PIND & (1 << ECHO)){}
    //save time value
    time += TCNT1;
    //stop timer
    TCCR1B = 0x00;
    count++; 
    _delay_ms(10);
    }

    //gets the average
    time = time / 5

    /returns time to be calculated
    return time;
}

unsigned int getDistance(const char *str){
    if(str == "cm"){

    }
    else if(str == "inch"){
    
    }
    else if(str == "feet"){
        
    }


}