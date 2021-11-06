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

int main (void) {
// Kom ihåg att sätta rätt com-port i makefile!
    LED_init();
    uart_init();
    timer_init();
    button_init();
    while (1) {
        while(!(TIFR0 & (1 << OCF0A))){} // vänta tills att output compare A matchar flag av timer0
        buttonState(&currentButtonState, &prevButtonState);     
        TIFR0 |= (1 << OCF0A); // rensa flaggan
        
    }
    return 0;
} 

