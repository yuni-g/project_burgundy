#ifndef blueLED_H
#define blueLED_H

#include <avr/io.h>
#include <util/delay.h>

//#define BLUELED 	PORTB5
#define LED_ON 		PORTB |= (1<<BLUELED)
#define LED_OFF		PORTB &= ~(1<<BLUELED)
#define TOGGLE_LED 	PINB |= (1<<BLUELED) //from datasheet, use pin read to toggle 

#endif

