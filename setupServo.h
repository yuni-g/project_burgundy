#ifndef setupServo_H
#define setupServo_H

#include <avr/io.h>

#define SERVO1_ON 		PORTB |= (1<<SERVO1)
#define SERVO2_ON 		PORTB |= (1<<SERVO2)
#define SERVO3_ON 		PORTB |= (1<<SERVO3)

#define SERVO1_OFF		PORTB &= ~(1<<SERVO1)
#define SERVO2_OFF 		PORTB &= ~(1<<SERVO2)
#define SERVO3_OFF 		PORTB &= ~(1<<SERVO3)


//#define SERVO_MAX_VAL     580 //180 degrees
//#define SERVO_MIN_VAL    380 //90 degrees

///// defined in pinSetup.h /////////
/*
 #define SERVO1             PORTBx //pin 8
 #define SERVO2             PORTBy //pin 11
 #define SERVO3             PORTBz //pin 12
 */



#endif
