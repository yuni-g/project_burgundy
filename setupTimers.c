#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "setupTimers.h"


/////// Timer 0 - Initialize ////////
void initTimer0()
{
//OCR0A = F_CPU/(2*FREQ_TMR0*N_TMR0)-1; //freq interrupt flag enable 50 Hz
OCR0A = 155;
<<<<<<< HEAD
TCCR0A |= (1<<WGM01); //|(1<<COM0A0); //CTC MODE 2 (//set OC0A FOR DEBUG)
=======
TCCR0A |= (1<<WGM01); //|(1<<COM0A0); //CTC MODE 2 (set OC0A FOR DEBUG)
>>>>>>> 47c79d6b8594bd35777ab392ea3972d155c1bc7e
TCCR0B |= (1<<CS02)|(1<<CS00); //PRESCALER 1024
TIMSK0 |= (1 << OCIE0A); // Enable Output Compare Match A Interrupt
}


//////// Timer 1 - Enable interrupt flag ////////
void startTimer1()
{
//TCCR1A |= (1 << COM1A0); //for debug
TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS11); // CTC MODE 4 PRESCALER 64
TIMSK1 |= (1 << OCIE1A); 		// Enable Output Compare Match A Interrupt
}

void stopTimer1()
{
	TCCR1B = 0x00;
	TCCR1A = 0x00;
}

/////////////////////////////////