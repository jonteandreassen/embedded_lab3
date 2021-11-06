#include <avr/io.h>
#include "button.h"
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "led.h"
#include "serial.h"




void button_init(){
    DDRD &= ~(1 << PD2); // sätt PORTD2 till output genom att invertera till biten till en 0a
}

void buttonState(uint8_t *currentButtonState, uint8_t *prevButtonState){
    char on[] = {"pushed\r\n"};
    char off[] = {"released\r\n"};
        if((PIND & (1 << PD2))){ // om knappen är nedtryckt
            *currentButtonState = 1;
            PORTD |= (1 << PD6); //tänd LED
        }
        else if (!(PIND & (1 << PD2))){ // om inte knappen är nedtryckt
            *currentButtonState = 0;
            PORTD &= ~(1 << PD6); //släck LED
        }
            if (*currentButtonState == 1 && *prevButtonState == 0){
                printf_P(PSTR("%s"), on);
            }
            else if (*currentButtonState == 0 && *prevButtonState == 1){
                printf_P(PSTR("%s"), off);
            }
    *prevButtonState = *currentButtonState;
}



