#ifndef setupPin_H
#define setupPin_H

#include <avr/io.h>

///// setup using ATMega328p - RedBoard pins //////

///// Timers //////
//PB1,PB2 are fror timer1 usage
//PD6 

///// Blue Led for debug //////
#define BLUELED			PORTB5 //pin 13

//// Servos //////
#define SERVO1			 PORTB0 //pin 8
#define SERVO2			 PORTB3 //pin 11
#define SERVO3			 PORTB4 //pin 12


///// Motor Driver - Vacuum Pump/////
//#define


///// Camera Module ////////
//#define



#endif