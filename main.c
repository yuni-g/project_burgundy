#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "INCLUDES.h"

#define NUM_SERVOS		3
#define START_POS 		400

extern volatile unsigned char Timer0_count;
extern volatile unsigned char Timer1_count;





int main()
{
char i = 0;
unsigned int servoVal[4] = {START_POS,START_POS,START_POS,4999-3*START_POS}; // starting position //

DDRB = 0xFF;
sei();


startTimer1();


//for (i=0;i<20;i++){controlServo(servoVal)};

while(1)
{

		testServo(servoVal,NUM_SERVOS);

		//if (matlabReady())
		//	servoReadVal(servoVal,NUM_SERVOS);


		controlServo(servoVal);

}

return 0;
}
