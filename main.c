#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"





void main (void) {

    //LED_init();
    uart_init();
    timer_init();

    button_init();
	
    while (1) {
        while(!(TIFR0 & (1 << OCF0A))){} // vänta tills att output compare A matchar flag av timer0
        OCR0A = test();     
        TIFR0 |= (1 << OCF0A);
    }
} 

void test(){
char pressed[] = {"pushed\r\n"};
char released[] = {"released\r\n"};
    if((PIND & (1<<PD2))){
        printf_P(PSTR("%s"), pressed);
    }
    else if (!(PIND & (1<<PD2))){
        printf_P(PSTR("%s"), released);
    }
}