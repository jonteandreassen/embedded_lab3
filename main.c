#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"
#include "adc.h"

uint8_t prevButtonState = 0;
uint8_t currentButtonState = 0;

volatile uint8_t ADCvalue = 0;

#include <avr/delay.h>
ISR(ADC_vect){
	
	ADCvalue = ADCH; // läser datan från ADCH eftersom vi har vänsterjusterat 10 bit datan
}

int main (void) {
// Kom ihåg att sätta rätt com-port i makefile!
    LED_init();
    uart_init();
    timer_init();
    //button_init();
    adc_init();

    while (1) {
        /*
        while(!(TIFR0 & (1 << OCF0A))){} // vänta tills att output compare A matchar flag av timer0
        buttonState(&currentButtonState, &prevButtonState);  
        TIFR0 |= (1 << OCF0A); // rensa flaggan
        */
        OCR0A = ADCvalue;
        printf_P(PSTR("%i"), ADCvalue);
        _delay_ms(1000);
    }
    return 0;
} 

