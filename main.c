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

uint8_t ADCvalue = 0;

#include <util/delay.h>

ISR(ADC_vect){
// ISR interuppt som triggas när "ADC conversion" är klart och sparar värdet till ADCvalue
	
	ADCvalue = ADCH; // läser datan från ADCH eftersom vi har vänsterjusterat 10 bit datan
}

ISR(TIMER2_COMPA_vect){
// ISR interrupt som triggas av timer2
// Bit 6 – ADSC: ADC Start Conversion In Single Conversion mode, write this bit to one to start each conversion.
    ADCSRA |= (1 << ADSC);
	OCR0A = ADCvalue;	
}

int main (void) {
// Kom ihåg att sätta rätt com-port i makefile!
    //PORTD |= (1 << PD6); // tänd LED

    LED_init();
    uart_init();
    timer_init();
    //button_init();
    adc_init();
    sei(); // sätt på interrupt
    while (1) {
        /*
        while(!(TIFR0 & (1 << OCF0A))){} // vänta tills att output compare A matchar flag av timer0
        buttonState(&currentButtonState, &prevButtonState);  
        TIFR0 |= (1 << OCF0A); // rensa flaggan
        */
        printf_P(PSTR("%" PRIu8 "\n\r"), OCR0A); // printar 0
        _delay_ms(1000);
    }
    return 0;
} 

