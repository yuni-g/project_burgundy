#ifndef setupTimers_H
#define setupTimers_H

#define FREQ_TMR0 	50 //frequency Timer 0 in Hertz
#define N_TMR0 		1024 //prescaler Timer 0

void initTimer0();
void startTimer1();
void stopTimer1();

#endif