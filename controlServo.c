#include <avr/io.h>
#include <avr/interrupt.h>
#include "setupServo.h"
#include "setupPin.h"
#include "blueLED.h"

#define PI 	3.14159265359
#define SERVO_MAX		180 //degrees, OCR1A = 580
#define SERVO_MIN		0 	//degrees, OCR1A = 180
#define SERVO_SAFETY_N 	3 	//degrees, prevent servo from reaching extremes

extern volatile unsigned char Timer1_count;


void servoOnOff(unsigned char servo1, unsigned char servo2, unsigned char servo3)
{
	if (servo1)
		SERVO1_ON;
	else
		SERVO1_OFF;

	if (servo2)
		SERVO2_ON;
	else
		SERVO2_OFF;
		
	if (servo3)
		SERVO3_ON;
	else
		SERVO3_OFF;
}


unsigned int convertAngle(float rad)
{
	float deg;
	int val;

	// convert radians to degrees //
	deg = rad*180/PI;

	// set boundaries to protect mechanical system //
	if (deg > (SERVO_MAX - 3))
		deg = SERVO_MAX - 3;

	else if (deg < (SERVO_MIN + 3))
		deg = SERVO_MIN +3;

	// convert degrees to a value readable by servo (i.e. OCR1A) //
	val = deg/0.45; // 0.45 degrees per step resolution - using Timer1 //

	return val;
}


void controlServo(unsigned int *arr)
{
	unsigned char count = 1;
	unsigned char countReach = 1; //no. of times signal needs to be sent to ensure servo moves to position
	// it will not be needed once developed system to move by steps from pos. A to B
	while(count)
	{
		if(Timer1_count==0)
			{
				OCR1A = arr[0];
				servoOnOff(1,0,0);
			}

		else if (Timer1_count==1)
			{
				OCR1A = arr[1];
				servoOnOff(0,1,0);
			}

		else if (Timer1_count==2)
			{
				OCR1A = arr[2];
				servoOnOff(0,0,1);
			}

		else if (Timer1_count==3)
			{
				//OCR1A = 4999 ensures 20 ms period
				//so, subtract the three servo values from 4999 (with prescaler 64)
				//to yield a 50 Hz signal
				OCR1A = 4999-(arr[0]+arr[1]+arr[2]);		
				servoOnOff(0,0,0);
			}

		else if (Timer1_count>=4)
			{
				count++;
				
				//ensure signal has been receied by servo before sending new position 
				if (count >= countReach)
					{
						count = 0;
					}

				Timer1_count=0;
				//servoOnOff(0,0,0);
			}
	}
}
