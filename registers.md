
## <strong>REGISTER INFORMATION LAB 3</strong>
## DELUPPGIFT 1
#
### 18.4.8. Port D Data Register
#
- Name: <strong>PORTD</strong>
- Bit: <strong>PORTD2</strong>
#
#
### 18.4.9. Port D Data Direction Register
- Name: <strong>DDRD</strong>
- Bit: <strong>DDRD2</strong>
#
### 18.4.10. Port D Input Pins Address
- Name: <strong>PIND</strong>
- Bit: <strong>PIND2</strong>
#
## Fast PWM deluppgift 2
## 19.9.1. TCNT0 (timer0) Control Register A
- Name: <strong>TCCR0A</strong>
- Bit: <strong>COM0A1 = 1 & COM0A0 = 0</strong>
- Bit: <strong>WGM00 = 1 & WGM01 = 1</strong>
## 19.9.2. TC0 Control Register B
- Name: <strong>TCCR0B</strong>
- Bit: <strong>CS00 = 1 & CS01 = 1</strong>
- Bit: <strong>WGM02 = 0</strong>
## 19.9.6. TC0 Output Compare Register A
- Name: <strong>OCR0A</strong>
##
    - Bit:  The Output Compare Register A contains an 8-bit value that is continuously compared with the counter
    value (TCNT0). A match can be used to generate an Output Compare interrupt, or to generate a
    waveform output on the OC0A pin.
#
## 19.9.8. TC0 Interrupt Flag Register
- Name: <strong>TIFR0</strong>
##
    Bit 1 – OCFA: Timer/Counter0, Output Compare A Match Flag
    The OCF0A bit is set when a Compare Match occurs between the Timer/Counter0 and the data in
    OCR0A – Output Compare Register0. OCF0A is cleared by hardware when executing the corresponding
    interrupt handling vector. Alternatively, OCF0A is cleared by writing a logic one to the flag. When the I-bit
    in SREG, OCIE0A (Timer/Counter0 Compare Match Interrupt Enable), and OCF0A are set, the Timer/
    Counter0 Compare Match Interrupt is executed.

	OCR0A = 255; //Representation of time led is on

	TCNT0 = 0; //Start timer, TOP-value 
#
## DELUPPGIFT 3
## 22.7.2. Clear Timer on Compare Match (CTC) Mode
### 22.11.1. TC2 Control Register A
- Name: <strong>TCCR2A</strong>
- Bit: <strong>COM2A1 = 1 & COM2A0 = 1</strong> Set OC2A on compare match
- Bit: <strong>WGM020 = 0 & WGM21 = 1</strong> CTC
#
- Name: <strong>TCCR2B</strong> 
- Bit: <strong>WGM022 = 01</strong> CTC
- Bit: <strong>CS20 = 1 & CS21 = 1 & CS22 =1</strong> 1024 prescaler
## 22.11.3. TC2 Counter Value Register
- Name: <strong>TCNT2</strong>
##
    Bits 7:0 – TCNT2[7:0]: Timer/Counter 2 Counter Value
    The Timer/Counter Register gives direct access, both for read and write operations, to the Timer/Counter
    unit 8-bit counter. Writing to the TCNT2 Register blocks (removes) the Compare Match on the following
    timer clock. Modifying the counter (TCNT2) while the counter is running, introduces a risk of missing a
    Compare Match between TCNT2 and the OCR2x Registers.
## 22.11.4. TC2 Output Compare Register A
- Name: <strong>OCR2A</strong>
##
    - Bits 7:0 – OCR2A[7:0]: Output Compare 2 A
    The Output Compare Register A contains an 8-bit value that is continuously compared with the counter
    value (TCNT2). A match can be used to generate an Output Compare interrupt, or to generate a
    waveform output on the OC2A pin.
#
## 22.11.6. TC2 Interrupt Mask Register
- Name: <strong>TIMSK2</strong>
- Bit: <strong>OCIEA</strong>
##
    - Bit 1 – OCIEA: Timer/Counter2, Output Compare A Match Interrupt Enable
    When the OCIEA bit is written to '1' and the I-bit in the Status Register is set (one), the Timer/Counter2
    Compare Match A interrupt is enabled. The corresponding interrupt is executed if a compare match in
    Timer/Counter2 occurs, i.e., when the OCFA bit is set in TIFR2.
#
## 22.11.7. TC2 Interrupt Flag Register
- Name: <strong>TIFR2</strong>
- Bit: <strong>OCFA</strong>
##
    - Bit 1 – OCFA: Timer/Counter2, Output Compare A Match Flag
    The OCFA bit is set (one) when a compare match occurs between the Timer/Counter2 and the data in
    OCRA – Output Compare Register2. OCFA is cleared by hardware when executing the corresponding
    interrupt handling vector. Alternatively, OCFA is cleared by writing a logic one to the flag. When the I-bit in
    SREG, OCIEA (Timer/Counter2 Compare match Interrupt Enable), and OCFA are set (one), the Timer/
    Counter2 Compare match Interrupt is executed.
#