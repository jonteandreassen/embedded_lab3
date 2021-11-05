#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"

uint8_t prevButtonState = 0;
uint8_t currentButtonState = 0;

int main (void) {

    LED_init();
    uart_init();
    timer_init();
    button_init();
    while (1) {
        //while(!(TIFR0 & (1 << OCF0A))){} // vänta tills att output compare A matchar flag av timer0
        //OCR0A = test();     
        //TIFR0 |= (1 << OCF0A); 
        test();
    }
    return 0;
} 

void test(){
    char on[] = {"pushed\r\n"};
    char off[] = {"released\r\n"};
        if((PIND & (1 << PD2))){ // om knappen är nedtryckt
            currentButtonState = 1;
            PORTD |= (1 << PD6); //tänd LED
        }
        else if (!(PIND & (1 << PD2))){ // om inte knappen är nedtryckt
            currentButtonState = 0;
            PORTD &= ~(1 << PD6); //släck LED
        }
            if (currentButtonState == 1 && prevButtonState == 0){
                printf_P(PSTR("%s"), on);
            }
            else if (currentButtonState == 0 && prevButtonState == 1){
                printf_P(PSTR("%s"), off);
            }
    prevButtonState = currentButtonState;
}