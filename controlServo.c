#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "INCLUDES.h"

extern volatile unsigned char Timer1_count;



/////// perform rotation of servos following sequential order //////////
void controlServo(unsigned int *arr)
{
	unsigned int sum;
	unsigned char count = 1;
	unsigned char countReach = 1; //no. of times signal needs to be sent to ensure servo moves to position
	// it will not be needed once developed system to move by steps from pos. A to B
	
	//while(count)
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
				//OCR1A = arr[3];
				sum=arr[0]+arr[1]+arr[2];
				OCR1A = TOP_VALUE_TIMER1-sum; // 4999 ensures 20 ms period //
				servoOnOff(0,0,0);
				Timer1_count=0;
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
				servoOnOff(0,0,0);
			}
	}
}


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
