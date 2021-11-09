#ifndef _LED_H_
#define _LED_H_

void LED_init(void);

volatile uint8_t simple_ramp(volatile uint8_t *ADCvalue);

#endif // _LED_H_

