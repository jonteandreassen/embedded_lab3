#include <avr/io.h>

#include "timer.h"

void timer_init() {

    //                timer0 settings                    
/*
 - Konfigurera upp timer0 i Fast PWM-mod på samma sätt som i labb 2
 - Fast PWM-mod, 255 som TOP, prescaler = 64
*/ 
// 19.9.1. TC0 Control Register A
//  - Register name: TCCR0A
//  - Bits: COM0A1 | COM0A0 | COM0B1 | COM0B0 | WGM01 | WGM00
// ---------------------------------------------------------------------------------
// Table 19-4. Compare Output Mode, Fast PWM
/*              Output compare mode settings                */
//  COM0A1 COM0A0 Description
//    0      0    // Normal port operation, OC0A disconnected.
//    0      1    // WGM02 = 0: Normal Port Operation, OC0A Disconnected
                  // WGM02 = 1: Toggle OC0A on Compare Match
//    1      0    // Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
//    1      1    // Set OC0A on Compare Match, clear OC0A at BOTTOM (inverting mode)
    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);
// ---------------------------------------------------------------------------------   
/*                  FAST PWM settings                      */
//! Combined with the WGM02 bit found in the TCCR0B Register
//  Mode WGM02 WGM01 WGM00 Timer/Counter Mode of Operation       TOP       Update of OCR0x at      TOV Flag Set on
//   0     0     0     0         Normal                          0xFF           Immediate                  MAX
//   1     0     0     1         PWM, Phase Correct              0xFF            TOP                      BOTTOM
//   2     0     1     0         CTC                             OCRA           Immediate                  MAX
//   3     0     1     1         Fast PWM                        0xFF           BOTTOM                     MAX
//   4     1     0     0         Reserved                         -               -                         -
//   5     1     0     1         PWM, Phase Correct              OCRA            TOP                      BOTTOM
//   6     1     1     0         Reserved                         -               -                         -
//   7     1     1     1         Fast PWM                        OCRA           BOTTOM                     TOP
    TCCR0A = (1 << WGM01) | (1 << WGM00);
// ---------------------------------------------------------------------------------
//  19.9.2. TC0 Control Register B
// - Register name: TCCR0B
// - Bits: FOC0A | FOC0B | WGM02 | CS0[2:0]
// ---------------------------------------------------------------------------------   
/*                  Prescale settings                      */    
//          Table 19-10. Clock Select Bit Description
//   CA02 CA01 CS00 Description
//    0    0     0    No clock source (Timer/Counter stopped).
//    0    0     1    clkI/O/1 (No prescaling)
//    0    1     0    clkI/O/8 (From prescaler)
//    0    1     1    clkI/O/64 (From prescaler)
//    1    0     0    clkI/O/256 (From prescaler)
//    1    0     1    clkI/O/1024 (From prescaler)
//    1    1     0    External clock source on T0 pin. Clock on falling edge.
//    1    1     1    External clock source on T0 pin. Clock on rising edge.
    TCCR0B &= ~(1 << WGM02); // Setting for fast PWM 
    TCCR0B &= ~(1 << CS02);
    TCCR0B = (1<< CS01) | (1 << CS00);
// ---------------------------------------------------------------------------------  
// 19.9.5. TC0 Counter Value Register
// Register name: TCNT0
// Bits: TCNT0[7:0]
/*
    Bits 7:0 – TCNT0[7:0]: TC0 Counter Value
    The Timer/Counter Register gives direct access, both for read and write operations, to the Timer/Counter
    unit 8-bit counter. Writing to the TCNT0 Register blocks (removes) the Compare Match on the following
    timer clock. Modifying the counter (TCNT0) while the counter is running, introduces a risk of missing a
    Compare Match between TCNT0 and the OCR0x Registers.
*/
// ---------------------------------------------------------------------------------  
// 19.9.6. TC0 Output Compare Register A
// - Register name: OCR0A
// - Bits: OCR0A[7:0]
/*
    Bits 7:0 – OCR0A[7:0]: Output Compare 0 A
    The Output Compare Register A contains an 8-bit value that is continuously compared with the counter
    value (TCNT0). A match can be used to generate an Output Compare interrupt, or to generate a
    waveform output on the OC0A pin.
*/
    OCR0A = 249; //  16000000/64 = 250000 => 250000/((1/1)*1000) -1 = 249 (ticks) => 249 (1 ms)
// --------------------------------------------------------------------------------- 
// 19.9.8. TC0 Interrupt Flag Register
// - Register name: TIFR0
// - Bits: OCFB  OCFA TOV //! OCFA
/*
    Bit 1 – OCFA: Timer/Counter0, Output Compare A Match Flag
    The OCF0A bit is set when a Compare Match occurs between the Timer/Counter0 and the data in
    OCR0A – Output Compare Register0. OCF0A is cleared by hardware when executing the corresponding
    interrupt handling vector. Alternatively, OCF0A is cleared by writing a logic one to the flag. When the I-bit
    in SREG, OCIE0A (Timer/Counter0 Compare Match Interrupt Enable), and OCF0A are set, the Timer/
    Counter0 Compare Match Interrupt is executed.
*/
// --------------------------------------------------------------------------------- 
    //                      timer2 settings                    
/*
 - Konfigurera upp timer2 i CTC-mod på samma sätt som i labb 2,
   men slå på interrupts för compare match, och använd inte busy wait-loopar
 - CTC-mod, 100 Hz, prescaler 1024, ’clear on match/set on bottom’
*/
// 22.11.1. TC2 Control Register A
// Register name: TCCR2A
// Bits: COM2A1 | COM2A0 | COM2B1 | COM2B0 | WGM21 | WGM20
// ---------------------------------------------------------------------------------
/*                  CTC settings                      */    
//        Table 22-3. Compare Output Mode, non-PWM
// ---------------------------------------------------------------------------------
//  COM2A1 COM2A0    Description
//    0      0           Normal port operation, OC2A disconnected.
//    0      1           Toggle OC2A on Compare Match.
//    1      0           Clear OC2A on Compare Match.
//    1      1           Set OC2A on Compare Match .
    TCCR2A &= ~(1 << COM2A0);
	TCCR2A |= (1 << COM2A1);

// Bits 1:0 – WGM2n: Waveform Generation Mode [n = 1:0]
//! Combined with the WGM22 bit found in the TCCR2B Register
// Table 22-9. Waveform Generation Mode Bit Description
//   Mode WGM22 WGM21 WGM20 | Timer/Counter Mode of Operation |  TOP | Update of OCR0x at | TOV Flag Set on
//    0     0     0    0                 Normal                  0xFF        Immediate           MAX
//    1     0     0    1                 PWM, Phase Correct      0xFF        TOP                 BOTTOM
//    2     0     1    0                 CTC                     OCRA        Immediate           MAX
//    3     0     1    1                 Fast PWM                0xFF        BOTTOM              MAX
//    4     1     0    0                 Reserved                 -           -                   -
//    5     1     0    1                 PWM, Phase Correct      OCRA        TOP                 BOTTOM
//    6     1     1    0                 Reserved                 -           -                   -
//    7     1     1    1                 Fast PWM                OCRA        BOTTOM              TOP
    TCCR2A |= (1 << WGM21);
// ---------------------------------------------------------------------------------
// 22.11.2. TC2 Control Register B
// Register name: TCCR2B
// Bits: FOC2A | FOC2B | WGM22 | CS2[2:0]
/*
    Bit 7 – FOC2A: Force Output Compare A
    The FOC2A bit is only active when the WGM bits specify a non-PWM mode.
    To ensure compatibility with future devices, this bit must be set to zero when TCCR2B is written when
    operating in PWM mode. When writing a logical one to the FOC2A bit, an immediate Compare Match is
    forced on the Waveform Generation unit. The OC2A output is changed according to its COM2A[1:0] bits
    setting. Note that the FOC2A bit is implemented as a strobe. Therefore it is the value present in the
    COM2A[1:0] bits that determines the effect of the forced compare.
    A FOC2A strobe will not generate any interrupt, nor will it clear the timer in CTC mode using OCR2A as
    TOP.
    The FOC2A bit is always read as zero.
*/
// ---------------------------------------------------------------------------------
// Bits 2:0 – CS2[2:0]: Clock Select 2 [n = 0..2]
// CA22 CA21 CS20   Description
//  0    0     0        No clock source (Timer/Counter stopped).
//  0          1        clkI/O/1 (No prescaling)
//  0    1     0        clkI/O/8 (From prescaler)
//  0    1     1        clkI/O/32 (From prescaler)
//  1    0     0        clkI/O/64 (From prescaler)
//  1    0     1        clkI/O/128 (From prescaler)
//  1    1     0        clkI/O/256 (From prescaler)
//  1    1     1        clkI/O/1024 (From prescaler)
    TCCR2B &= ~(1 << WGM22); // CTC settings
    TCCR2B &= ~(1 << WGM20); // CTC settings
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
// ---------------------------------------------------------------------------------
// 22.11.3. TC2 Counter Value Register
// Register name: TCNT2
// Bits: TCNT2[7:0]
/*
    Bits 7:0 – TCNT2[7:0]: Timer/Counter 2 Counter Value
    The Timer/Counter Register gives direct access, both for read and write operations, to the Timer/Counter
    unit 8-bit counter. Writing to the TCNT2 Register blocks (removes) the Compare Match on the following
    timer clock. Modifying the counter (TCNT2) while the counter is running, introduces a risk of missing a
    Compare Match between TCNT2 and the OCR2x Registers.
*/  
// ---------------------------------------------------------------------------------
// 22.11.4. TC2 Output Compare Register A
// Register name: OCR2A
// Bits: OCR2A[7:0]
/*
    Bits 7:0 – OCR2A[7:0]: Output Compare 2 A
    The Output Compare Register A contains an 8-bit value that is continuously compared with the counter
    value (TCNT2). A match can be used to generate an Output Compare interrupt, or to generate a
    waveform output on the OC2A pin.
*/
    OCR2A = 155; //16000000/1024 = 15625 => 15625/((1/10)*1000) -1 = 155,25 (ticks) => 155 (10 ms)
// ---------------------------------------------------------------------------------
// 22.11.7. TC2 Interrupt Flag Register
// Register name: TIFR2
// Bits: OCFB OCFA TOV  //! OCFA
/*
    Bit 1 – OCFA: Timer/Counter2, Output Compare A Match Flag
    The OCFA bit is set (one) when a compare match occurs between the Timer/Counter2 and the data in
    OCRA – Output Compare Register2. OCFA is cleared by hardware when executing the corresponding
    interrupt handling vector. Alternatively, OCFA is cleared by writing a logic one to the flag. When the I-bit in
    SREG, OCIEA (Timer/Counter2 Compare match Interrupt Enable), and OCFA are set (one), the Timer/
    Counter2 Compare match Interrupt is executed.
*/
}

 