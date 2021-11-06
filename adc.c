#include <avr/io.h>
#include "adc.h"


// ADC Settings
// ADC = Vin * 1024 / Vref = 5.0 * 1024 / 5 = 1024 - 1 = 1023
// Vmax = 1023 == 5v (spänning mellan 0 - 1023)



// 28.9.1. ADC Multiplexer Selection Register
// Register name: ADMUX
// Bits: REFS1 | REFS0 | ADLAR | MUX3 | MUX2 | MUX1 | MUX0
// -----------------------------------------------------------------------------
// Table 28-3. ADC Voltage Reference Selection

// REFS1  0     Voltage Reference Selection
//   0    0     AREF, Internal Vref turned off
//   0    1     AVCC with external capacitor at AREF pin
//   1    0     Reserved
//   1    1     Internal 1.1V Voltage Reference with external capacitor at AREF pin
// -----------------------------------------------------------------------------

// Bit 5 – ADLAR: ADC Left Adjust Result
// The ADLAR bit affects the presentation of the ADC conversion result in the ADC Data Register. Write one
// to ADLAR to left adjust the result. Otherwise, the result is right adjusted. Changing the ADLAR bit will
// affect the ADC Data Register immediately, regardless of any ongoing conversions. For a complete
// description of this bit, see ADCL and ADCH.

// -----------------------------------------------------------------------------
// Bits 3:0 – MUXn: Analog Channel Selection [n = 3:0]
//Table 28-4. Input Channel Selection
// MUX3 MUX2 MUX1 MUX0 Single Ended Input
//  0    0    0    0        ADC0 // Potentiometern är kopplad till denna
//  0    0    0    1        ADC1
//  0    0    1    0        ADC2
//  0    0    1    1        ADC3
//  0    1    0    0        ADC4
//  0    1    0    1        ADC5
//  0    1    1    0        ADC6
//  0    1    1    1        ADC7
//  1    0    0    0        Temperature sensor
//  1    0    0    1        Reserved
//  1    0    1    0        Reserved
//  1    0    1    1        Reserved
//  1    1    0    0        Reserved
//  1    1    0    1        Reserved
//  1    1    1    0        1.1V (VBG)
//  1    1    1    1        0V (GND)
// -----------------------------------------------------------------------------

// 28.9.2. ADC Control and Status Register A
// Register name: ADCSRA
// Bits: ADEN | ADSC | ADATE | ADIF | ADIE | ADPS2 | ADPS1 | ADPS0

// Bits 2:0 – ADPSn: ADC Prescaler Select [n = 2:0]
// Table 28-5. Input Channel Selection
// ADPS2 ADPS1 ADPS0 Division Factor
//  0     0     0      2
//  0     0     1      2
//  0     1     0      4
//  0     1     1      8
//  1     0     0      16
//  1     0     1      32
//  1     1     0      64
//  1     1     1      128
// -----------------------------------------------------------------------------
// 28.9.3. ADC Data Register Low (ADLAR=0)
// When an ADC conversion is complete, the result is found in these two registers.
// When ADCL is read, the ADC Data Register is not updated until ADCH is read. Consequently, if the result
// is left adjusted and no more than 8-bit precision is required, it is sufficient to read ADCH. Otherwise,
// ADCL must be read first, then ADCH.

// Register name: ADCL
// Bits: ADC7 | ADC6|  ADC5|  ADC4|  ADC3|  ADC2|  ADC1|  ADC0
// -----------------------------------------------------------------------------

// 28.9.7. ADC Control and Status Register B
// Register name: ADCSRB
// Bits: ACME | ADTS2 | ADTS1 | ADTS0

// ADTS2 ADTS1 ADTS0    Trigger Source
//  0     0      0      Free Running mode
//  0     0      1      Analog Comparator
//  0     1      0      External Interrupt Request 0
//  0     1      1      Timer/Counter0 Compare Match A
//  1     0      0      Timer/Counter0 Overflow
//  1     0      1      Timer/Counter1 Compare Match B
//  1     1      0      Timer/Counter1 Overflow
//  1     1      1      Timer/Counter1 Capture Event
// -----------------------------------------------------------------------------



void adc_init(){
// AVCC with external capacitor at AREF pin
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << REFS0); 
// Bit 5 – ADLAR: ADC Left Adjust Result
    ADMUX |= (1 << ADLAR);
// Bits 3:0 – MUXn: Analog Channel Selection [n = 3:0]   
    ADMUX &= (1 << MUX3) & (1 <<MUX2) & (1 << MUX1) & (1 << MUX0);
// Bit 7 – ADEN: ADC Enable
    ADCSRA |= (1 << ADEN);
// Bit 6 – ADSC: ADC Start Conversion In Single Conversion mode, write this bit to one to start each conversion.
    ADCSRA |= (1 << ADSC);
// Bit 4 – ADIF: ADC Interrupt Flag This bit is set when an ADC conversion completes and the Data Registers are updated.
    //ADCSRA |= (1 << ADIF);
// Bit 3 – ADIE: ADC Interrupt Enable When this bit is written to one and the I-bit in SREG is set, the ADC Conversion Complete Interrupt is activated.
    ADCSRA |= (1 << ADIE);
// Bits 2:0 – ADPSn: ADC Prescaler Select [n = 2:0]
// Division Factor == 8
    ADCSRA &= ~(1 << ADPS2);
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
// Bits 2:0 – ADTSn: ADC Auto Trigger Source [n = 2:0]
    ADCSRB &= ~(1 << ADTS2);
    ADCSRB |= (1 << ADTS1) | (1 << ADTS0);


}