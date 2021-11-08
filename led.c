#include <avr/io.h>
#include "led.h"

void LED_init() {
    DDRD |= (1 << PD6); //Output led
}

uint8_t simple_ramp(uint8_t *ADCvalue) {
    uint8_t PWMdirection = -1;
    if (*ADCvalue == 0 || PWMdirection == 254){
        PWMdirection *= -1;
    }
    return *ADCvalue += PWMdirection;
}
