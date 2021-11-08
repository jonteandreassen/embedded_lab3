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


    LED_init();
    //button_init(); // Deluppgift 2
    uart_init();
    timer0_init(); // Deluppgift 3
    timer2_init(); // Deluppgift 3
    
    adc_init();   // Deluppgift 3
    sei(); // sätt på interrupt // Deluppgift 3
    
    while (1) {
        
       // buttonState(&currentButtonState, &prevButtonState);  // Deluppgift 2
       
        simple_ramp(&OCR0A);
        printf_P(PSTR("AdcValue: %d \n\r"), ADCvalue); // printar 0
        _delay_ms(1000);
        
    }
    return 0;
} 

