#include <avr/io.h>
#include "button.h"
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "led.h"
#include "serial.h"

int isPressed;


void button_init(){
    DDRD &= ~(1<<PD2); //Input Switch
}

void checkButton(){  
    while(1){
        if(!(PIND & (1<<PD2))) {
            PORTD &= ~(1<<PD6);
            printf_P(PSTR("released\r\n"));
            isPressed = 0;

        }
        else {
            PORTD |= (1<<PD6);
            printf_P(PSTR("pushed\r\n"));
            isPressed = 1;
        }
    }
}

