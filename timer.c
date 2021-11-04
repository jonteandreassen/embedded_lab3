#include <avr/io.h>

#include "timer.h"

void timer_init() {
//Clear OC0A on Compare match, set OC0A at bottom(non-inverting mode)
TCCR0A = (1<<COM0A1) |(1<<WGM00) | (1<<WGM01); //Set COM0A1 to 1
TCCR0A &= ~(1<<COM0A0); //Set COM0A0 to 0
//Set Fast PWM in (Timer/Counter Control Register A, Mode 3)

OCR0A = 255; //Representation of time led is on

//Set prescale to 64 in register(Timer/Counter Control Register B)
TCCR0B &= ~(1<<WGM02); //Set WGM02 to 0
TCCR0B &= ~(1<<CS02); //Set CS02 to 0
TCCR0B = (1<<CS01) |(1<<CS00);

TCNT0 = 0; //Start timer, bottom-value 
}

