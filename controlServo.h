#ifndef controlServo_H
#define controlServo_H

#include <avr/io.h>

#define SERVO1			 PORTB0 //pin 8
#define SERVO2			 PORTB3 //pin 11
#define SERVO3			 PORTB4 //pin 12

#define SERVO1_ON 		PORTB |= (1<<SERVO1)
#define SERVO2_ON 		PORTB |= (1<<SERVO2)
#define SERVO3_ON 		PORTB |= (1<<SERVO3)

#define SERVO1_OFF		PORTB &= ~(1<<SERVO1)
#define SERVO2_OFF 		PORTB &= ~(1<<SERVO2)
#define SERVO3_OFF 		PORTB &= ~(1<<SERVO3)

#define SERVO_MAX_VAL 		580 //180 degrees
#define SERVO_MIN_VAL		380 //90 degrees
#define TOP_VALUE_TIMER1 	4999 //Timer1 for 20ms in CTC mode

void controlServo(unsigned int *arr);
void servoOnOff(unsigned char servo1, unsigned char servo2, unsigned char servo3);




#endif
