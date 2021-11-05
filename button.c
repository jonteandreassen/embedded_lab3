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





