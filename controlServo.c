#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "setupServo.h"
#include "setupPin.h"
#include "blueLED.h"


#define PI 	3.14159265359
#define SERVO_MAX_VAL 	570 //180 degrees
#define SERVO_MIN_VAL	390 //90 degrees
#define SERVO_SAFETY_VAL	3 	//degrees, prevent servo from reaching extremes
#define TOP_VALUE_TIMER1 	4999 //Timer1 for 20ms in CTC mode

extern volatile unsigned char Timer1_count;

/////// check if MatLab value is ready //////
bool matlabReady(void)
{
	unsigned char data = 0;
	data = USARTreceive();

	if (data == '<') // initiate sending data //
		return true;
	else
		return false;
}

/////// receive values from MatLab and store into array //////////
void servoFillArr(unsigned int *arr, char count)
{
	char i=0;
	unsigned int sum = 0;

	for (i=0;i<count;i++)
	{
		arr[i] = USARTreceive(); //receive data from MatLab
		arr[i] += SERVO_MIN_VAL; //apply offset for servo
		sum += arr[i];
	}

	arr[count+1]=TOP_VALUE_TIMER1-sum; // ensure 20 ms period //
}


/////// perform rotation of servos following sequential order //////////
void controlServo(unsigned int *arr)
{
	//unsigned char count = 1;
	//unsigned char countReach = 1; //no. of times signal needs to be sent to ensure servo moves to position
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
				OCR1A = arr[3];
				//OCR1A = 4999-(arr[0]+arr[1]+arr[2]); // 4999 ensures 20 ms period //
				servoOnOff(0,0,0);
				Timer1_count=0;
			}

		else if (Timer1_count>=4)
			{
				//count++;
				
				//ensure signal has been receied by servo before sending new position 
				//if (count >= countReach)
				//	{
				//	count = 0;
				//	}

				Timer1_count=0;
				//servoOnOff(0,0,0);
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

////// do this in MATLAB ////////
unsigned int convertAngle(float rad)
{
	float deg;
	int val;

	// convert radians to degrees //
	deg = rad*180/PI;

	// set boundaries to protect mechanical system //
	if (deg > (SERVO_MAX_VAL - 3))
		deg = SERVO_MAX_VAL - 3;

	else if (deg < (SERVO_MIN_VAL + 3))
		deg = SERVO_MIN_VAL +3;

	// convert degrees to a value readable by servo (i.e. OCR1A) //
	val = deg/0.45; // 0.45 degrees per step resolution - using Timer1 //

	return val;
}

////// for testing ///////
void testServo(unsigned int *arr, char count)
{

bool i; // choose direction of rotation //
unsigned int b = 4; // stepping size to reach location //
unsigned int sum;
	if (arr[0] >= SERVO_MAX_VAL) 
			i = false;
	else if (arr[0] <= SERVO_MIN_VAL)
			i = true;

	if (i)
		{
			LED_OFF;

			arr[0]+=b;
			sum = arr[0];
			for(i=1;i<count;i++)
				{
					arr[i]=arr[0];
					sum += arr[i];
				}
			arr[count+1]=4999-sum;


		}

	else if (~i)
		{
			LED_ON;

			arr[0]-=b;
			sum = arr[0];
			for(i=1;i<count;i++)
				{
					arr[i]=arr[0];
					sum += arr[i];
				}
			arr[count+1]=4999-sum;
		}

}
