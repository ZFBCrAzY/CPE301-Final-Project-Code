/*
 * distanceSensor.h
 *
 * Created: 4/2/2026 8:15:13 PM
 *  Author: CrAzY
 */ 


#ifndef DISTANCESENSOR_H_
#define DISTANCESENSOR_H_

//PIN Mappings
#define TRIG PD4
#define ECHO PD5  

//Sensor Setup
void ultraSonicInit();

//Measures Distance
unsigned int measureDistance();

//calculates distance
unsigned int getDistance();

#endif /* DISTANCESENSOR_H_ */