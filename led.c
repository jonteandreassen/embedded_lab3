#include <avr/io.h>
#include "led.h"

void LED_init() {
    DDRD |= (1 << PD6); //Output led
}

uint8_t simple_ramp(uint8_t ADCvalue) {

	uint8_t count = 0;
    uint8_t direction = -1; // annars blir loopen fel

    if (count == 0 || direction == 255){
        direction *= -1;
    }
    return count += direction;
}
