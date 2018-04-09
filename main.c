#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "INCLUDES.h"

#define NUM_SERVOS		3
#define SERVO_MAX_VAL 	570 //178 degrees
#define SERVO_MIN_VAL	380 //92 degrees
#define START_POS 		380

extern volatile unsigned char Timer0_count;
extern volatile unsigned char Timer1_count;



void wait(int a)
{
	int i = 0;
for(i=0;i<a;i++)
_delay_ms(100);
}

int main()
{
char i = 0;
unsigned int servoValues[5] = {};// start position //
int b = 550;
unsigned int offset = 380;
char data;
DDRB = 0xFF;
sei();
startTimer1();
wait(50);
initUSART();

//for (i=0;i<20;i++){controlServo(servoVal)};
while ( !(UCSR0A & (1 << RXC0)))
			{
				servoValues[0] = b;
				servoValues[1] = b;
				servoValues[2] = b;
				controlServo(servoValues);
			}

while(1)
{
	for (i = 0; i<3; i++)
	{
		while ( !(UCSR0A & (1 << RXC0)))
			{
				controlServo(servoValues);
			}

		servoValues[i] = UDR0 + offset;
	}
}

return 0;
}
