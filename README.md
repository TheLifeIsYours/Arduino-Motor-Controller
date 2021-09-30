#  Motor Kontroller

## Funksjoner

### L293D Funksjoner
Ved å benytte en L293D IC for kontrollering av en motor, kan man ved en mikrokontroller og kode; endre hastighet, og retning av motorer.
 I vårt senario benytter L293D IC'n seg av pwm signalet vi gir inn på pinne 1 (1,2 enable), fra pinne ~9 på mikrokontrolleren, dette signalet representerer farten av motoren, samt også spenningen tilført motoren (1,5v - 3,5v). For å kunne si hvilken retning motoren skal snurre, gir vi digitale signaler (HIGH/LOW) inn på pinne 1A og 2A, disse må være motsatt av hverandre for å gi retningen. Lav på 1A og høy på 2A vil få motoren til å kjøre med klokken, og motsatt oppkobling mot klokken (alt ettersom man har koblet opp polene på motoren). Motoren er koblet til på pinne 1Y og 2Y.

### Programmerte funkjsoner
 
 - Minimum hastighet før motoren skrur seg av.
 - Motoren starter uten å henge fra full stans til kjørende.potmeteret sier hastigheten skal være.
 - Motoren endrer retning med en myk overgang med trykk av en knapp.
 - Endre hastighet av motoren med et pot-meter

#### Start
Når motoren starter opp fra full stans, er det ett lite kick som får motoren i gang. Dette forhindrer at motoren henger ved for lav tilført driv spenning.
   - Når motoren får tilført en for lav drive spenning, så vil motoren henge helt til man enten fysisk gir rotoren rotasjon, eller man gir litt høyere driv spenning. For å komme rundt at motoren henger, er det definert en safe_min_start_speed, som forklarer minimum trygg start fart/signal, som vil garantere at motoren starter. Etter motoren har startet å snurre fra safe_min_start_speed, settes hastigheten til hva 

#### Stop
Programmert er det begrensinger for hvor sakte motoren kan kjøre, når pot-meteret er under en bestemt verdi, skrus motoren av.
- Ved for lav tilført driver signal, skrus motoren av for å forhindre at motoren henger.

#### Retnigns endring
Motoren vil endre retning ved en myk stop/start funksjon.
- Om man trykker på den oppkoblede knappen, vil dette signalisere at motoren skal endre retning. Mikrokontrolleren vil da først gradvis stanse motoren før den endrer retning. for så å sette opp hastigheten til hva potentiometeret tilsier. Dette forhindrer momentat endring av rettning, og forhindrer uegnet last på moteren fra momentetet av lasten koblet til rotoren.

#### Hastighet
Hastigheten kan kontrolleres ved et potmeter.
   - Snur man på potmeteret så leses verdien digitalt av med mikrokontrolleren, signalet gjøres om fra 0-1023 til 0-255 som driver motoren. Snur man potmeteret for langt til venstre (mot klokken), vil motoren skrus av. Dette forhindrer at motoren henger ved for lav tilført driv spenning.

## Komponenter
<table>
    <tbody>
        <tr>
            <td>Del</td>
            <td>Antall</td>
            <td>Data ark</td>
        </tr>
        <tr>
            <td>Arduino Uno</td>
            <td>1</td>
            <td><a href="https://store-usa.arduino.cc/products/arduino-uno-rev3">https://store-usa.arduino.cc/products/arduino-uno-rev3</a></td>
        </tr>
        <tr>
            <td>Breadboard</td>
            <td>1</td>
            <td><a href="https://components101.com/sites/default/files/component_datasheet/Breadboard%20Datasheet.pdf">https://components101.com/sites/default/files/component_datasheet/Breadboard%20Datasheet.pdf</a></td>
        </tr>
        <tr>
            <td>L293D</td>
            <td>1</td>
            <td><a href="https://www.ti.com/lit/ds/symlink/l293.pdf">https://www.ti.com/lit/ds/symlink/l293.pdf</a></td>
        </tr>
        <tr>
            <td>6,9V DC Motor</td>
            <td>1</td>
            <td><a href="https://www.arduino.cc/documents/datasheets/DCmotor6_9V.pdf">https://www.arduino.cc/documents/datasheets/DCmotor6_9V.pdf</a></td>
        </tr>
        <tr>
            <td>Trykk knapp</td>
            <td>1</td>
            <td><a href="http://arduino.cc/documents/datasheets/Button.pdf">http://arduino.cc/documents/datasheets/Button.pdf</a></td>
        </tr>
        <tr>
            <td>10K Ohm Potentiometer</td>
            <td>1</td>
            <td><a href="https://www.arduino.cc/documents/datasheets/ACP_potentiometers.pdf">https://www.arduino.cc/documents/datasheets/ACP_potentiometers.pdf</a></td>
        </tr>
        <tr>
            <td>LED (Red, Green, Yellow)</td>
            <td>3</td>
            <td>
                <a href="http://arduino.cc/documents/datasheets/LEDR-L-7113ID-12V%28Ver1287713938.7%29.pdf">http://arduino.cc/documents/datasheets/LEDR-L-7113ID-12V%28Ver1287713938.7%29.pdf</a><br/>
                <a href="http://arduino.cc/documents/datasheets/LEDG-L-7113GT%28Ver1286952261.13%29.pdf">http://arduino.cc/documents/datasheets/LEDG-L-7113GT%28Ver1286952261.13%29.pdf</a><br/>
                <a href="http://arduino.cc/documents/datasheets/LEDY-L-7113YT.pdf">http://arduino.cc/documents/datasheets/LEDY-L-7113YT.pdf</a>
            </td>
        </tr>
        <tr>
            <td>220Ohm Resistor</td>
            <td>3</td>
            <td><a href="http://arduino.cc/documents/datasheets/Resistors.pdf">http://arduino.cc/documents/datasheets/Resistors.pdf</a></td>
        </tr>
        <tr>
            <td>Koblings kabler</td>
            <td>17</td>
            <td><a href="https://www.adafruit.com/product/153#technical-details">https://www.adafruit.com/product/153#technical-details</a></td>
        </tr>
    </tbody>
</table>

## Oppkobling
![Oppkoblingskjema](https://github.com/TheLifeIsYours/Arduino-Motor-Controller/blob/master/Motor-controller-sketch.png?raw=true)
