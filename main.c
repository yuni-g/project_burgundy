#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "INCLUDES.h"

#define SERVO_MAX_VAL 	550 //0 degrees
#define SERVO_MIN_VAL	400 //90 degrees


extern volatile unsigned char Timer0_count;
extern volatile unsigned char Timer1_count;





int main()
{
//need to create function or use pointer to get servo values from outside main
bool i;
unsigned int a;
unsigned int b = 4;

unsigned int servoVal[3] = {500,500,500};

sei();
DDRB = 0xFF;
DDRD |= (1<<PD6);
initTimer0();


while(1)
{

	
		startTimer1();

		if (Timer0_count)
		{

		if (servoVal[0] >= SERVO_MAX_VAL) 
				i = false;
		else if (servoVal[0] <= SERVO_MIN_VAL)
				i = true;

		if (i)
			{
				servoVal[0]=a+b;
				a = servoVal[0];
				servoVal[1]=a;
				servoVal[2]=a;
			}

		else if (~i)
			{
				servoVal[0]=a-b;
				a = servoVal[0];
				servoVal[1]=a;
				servoVal[2]=a;
				LED_ON;
			}

		}

		/*if (i==0)
		{
			servoVal[0]=450;
			servoVal[1]=450;
			i++;
		}
		else if (i==1)
		{
			servoVal[0]=400;
			servoVal[1]=400;
			i++;
		
		}
		else if (i==2)
		{
			servoVal[0]=420;
			servoVal[1]=420;
			i = 0;
		}*/
		
		controlServo(servoVal);

}

return 0;
}
