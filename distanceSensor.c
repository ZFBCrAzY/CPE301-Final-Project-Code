#include "distanceSensor.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>

// Function: Sets up Ultrasonic sensor setting
void ultraSonicInit(){
    //sets Pin Directions Needed For Ultrasonic
    //Sets Trig as output
    DDRD |= (1 << TRIG);
    //Sets Echo as Input
    DDRD &= ~(1 << ECHO);
}

// Begins to collect ultrasonic pulse data
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
    _delay_ms(60);
    }

    //gets the average
    time = time / 5;

    //returns time to be calculated
    return time;
}

// Function: Gets the Distance using the Ultrasonic Sensor
// Input: A unit label used to select desired distance unit
// Output: Distance as a int in the unit selected.
unsigned int getDistance(const char *str){
    //Initialize Distance/time variables
    unsigned int distance = 0;
    unsigned int time = 0;
    //collects time from ultrasonic pulses
    time = measureDistance();
    //Calculates Distance from time based on given unit
    if(strcmp(str,"cm") == 0){
        distance = time / 116;
    }
    else if(strcmp(str,"inch") == 0){
        distance = time / 296;
    }
    else if(strcmp(str,"feet") == 0){
        distance = time / 3552;
    }
    //returns the distance in the desired unit
    return distance;
}