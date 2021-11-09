## embedded_lab3

INLÄMNINGSUPPGIFT/LABB 03

## 1.4.2 DELUPPGIFT 2: LÄS AV DIGITALINGÅNG
  - [x] 1. Konfigurera upp pinne PD2 som ingång, som använder ett externt pulldown motstånd.
  - [x] 2. Skriv, och anropa periodiskt, en funktion som läser av pinnen och skriver ut 
  - [x] - ’pushed\r\n’ och ’released\r\n’ på UARTen när knappen trycks in, respektive släpps upp. Meddelandena ska bara skrivas ut en gång per knapptryck

## 1.4.3 DELUPPGIFT 3: LÄS SPÄNNING MED HJÄLP AV ADCN
1. Konfigurera upp ADC-enheten mha kap 28 i databladet:
- [x] Single conversion
- [x] Bit-data, vänsterjusterat
- [x] Prescaler = 8, referensspänning VCC
- [x] Använd kanal ADC0
2. Skriv en avbrottshanterare för ’ADC conversion complete’, och i den, läs ut ADC-värdet och spara undan det i en global variabel
3. Konfigurera upp timer0 i:
- [x] Fast PWM-mod, 255 som TOP, prescaler = 64
4. Konfigurera upp timer2:
- [x] CTC-mod på samma sätt som i labb 2, men slå på interrupts för compare match, och använd inte busy wait-loopar
- [x] CTC-mod, 100 Hz,
- [x] prescaler 1024, ’clear on match/set on bottom’
- [x] Skriv en avbrottshanterare för compare match A, och i den, starta en ADC-omvandling, och skriv föregående ADC-värde (sparat i variabeln) till OCR0A

## Förväntat beteende: potentiometern kan användas för att styra ljusstyrkan på LEDen. Moturs bottenläge = helt släckt, medurs bottenläge = helt på.
#
