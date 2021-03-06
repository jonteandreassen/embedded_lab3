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


#include <util/delay.h> // Används för att läsa ut ADC värdet i UART

ISR(ADC_vect){
// ISR interuppt som triggas när "ADC conversion" är klart och sparar värdet till ADCvalue
	ADCvalue = ADCH; // läser datan från ADCH eftersom vi har vänsterjusterat 10 bit datan
}

ISR(TIMER2_COMPA_vect){
// ISR interrupt som triggas av timer2
// Bit 6 – ADSC: ADC Start Conversion In Single Conversion mode, write this bit to one to start each conversion.
    ADCSRA |= (1 << ADSC);
	OCR0A = ADCvalue;	
    buttonState(&currentButtonState, &prevButtonState);  // Deluppgift 2
}



int main (void) {
//! Kom ihåg att sätta rätt com-port i makefile !


    LED_init();
    button_init(); // Deluppgift 2
    uart_init();
    
    timer0_init(); // Deluppgift 3
    timer2_init(); // Deluppgift 3
    adc_init();   // Deluppgift 3
    sei(); // sätt på interrupt // Deluppgift 3
    
    while (1) {
        
        simple_ramp(&OCR0A); // skickar med adressen till OSCR0A
        //Temporärt bara för att se hur ADC värdena 
        printf_P(PSTR("AdcValue: %d \n\r"), ADCvalue); 
        _delay_ms(1000);
      
    }
    return 0;
} 

