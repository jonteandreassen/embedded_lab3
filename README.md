## embedded_lab3

1 INLÄMNINGSUPPGIFT/LABB 03

1.4.2 DELUPPGIFT 2: LÄS AV DIGITALINGÅNG
  1. Konfigurera upp pinne PD2 som ingång, som använder ett externt pulldown motstånd.
  2. Skriv, och anropa periodiskt, en funktion som läser av pinnen och skriver ut 
  - ’pushed\r\n’ och ’released\r\n’ på UARTen när knappen trycks in, respektive släpps upp. Meddelandena ska bara skrivas ut en gång per knapptryck
  3. Städa upp din kod och skapa en git-commit med ovanstående.
#
1.4.3 DELUPPGIFT 3: LÄS SPÄNNING MED HJÄLP AV ADCN
1. Konfigurera upp ADC-enheten mha kap 28 i databladet:
- Single conversion
- Bit-data, vänsterjusterat
- Prescaler = 8, referensspänning VCC
- Använd kanal ADC0
2. Skriv en avbrottshanterare för ’ADC conversion complete’, och i den, läs ut ADC-värdet och spara undan det i en global variabel
3. Konfigurera upp timer0 i:
- Fast PWM-mod, 255 som TOP, prescaler = 64
4. Konfigurera upp timer2:
* CTC-mod på samma sätt som i labb 2, men slå på interrupts för compare match, och använd inte busy wait-loopar
- CTC-mod, 100 Hz,
- prescaler 1024, ’clear on match/set on bottom’
- Skriv en avbrottshanterare för compare match A, och i den, starta en ADC-omvandling, och skriv föregående ADC-värde (sparat i variabeln) till OCR0A
5. Städa upp din kod och skapa en git-commit med ovanstående.
### Förväntat beteende: potentiometern kan användas för att styra ljusstyrkan på LEDen. Moturs bottenläge = helt släckt, medurs bottenläge = helt på.
#
1.4.4 DELUPPGIFT 4 (VG-KRAV): ANVÄNDARSTYRT BETEENDE
1. Kombinera koden från de två föregående deluppgifterna, och ändra den så att följande beteende uppnås:
• 10ms-timern används också för att periodiskt läsa av knappen
• När knappen tryckts in och sedan släppts upp helt, växlar LEDen beteende mellan följande moder, i den angivna sekvensen:
1. Pulserande, med hjälp av simple_ramp-funktionen från labb 2 (Utgångsläge vid reset/uppstart)
2. Potentiometerstyrd, med hjälp av deluppgift 2
3. Blinkande av/på, i ca 1 Hz
4. Släckt
2. Beteendet implementeras med fördel med hjälp av en tillståndsmaskin
3. Delay-funktioner ska ej användas, ej heller busy-wait på flaggor för timers eller ADC
4. Tänk på att avbrottsrutinen ska exekvera minimalt med kod
5. Städa upp din kod och skapa en git-commit med ovanstående.
