#include <avr/interrupt.h>

volatile unsigned char Timer0_count = 0;
volatile unsigned char Timer1_count = 0;

ISR(TIMER0_COMPA_vect)
{
Timer0_count++;
}


ISR(TIMER1_COMPA_vect)
{
Timer1_count++;
}
