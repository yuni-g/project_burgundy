#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define PWMA	PB3
#define IN2		PB2
#define IN1		PB1
#define STDBY	PB0


void brake()
{
	PORTB |= (1<<IN1)|(1<<IN2);
	wait(1);
}

void stop()
{
	PORTB &= ~(1<<IN1) & ~(1<<IN2);
	PORTB |= (1<<PWMA);
	wait(1);
}

void driveCW()
{
	PORTB |= (1<<IN1) | (1<<PWMA);
	PORTB &= ~(1<<IN2);
	wait(1);
}

void driveCCW()
{
	PORTB |= (1<<IN2) | (1<<PWMA);
	PORTB &= ~(1<<IN1);
	wait(1);
}

void wait(char a)
{
	int i = 0;
	for (i =0; i<a; i++)
		_delay_ms(1000);
}

int main()
{
	DDRB = 0xFF;
	PORTB = 0x00;
	PORTB |= (1<<STDBY);

	brake();
	driveCW();
	wait(5);
	brake();
	driveCCW();
	wait(5);
	brake();
	stop();

while(1)
{
	PORTB ^= 0x20;
	_delay_ms(200);
}

return 0;
}
