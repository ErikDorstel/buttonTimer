# buttonTimer
Arduino millis() based buttonTimer library

Diese Bibliothek implementiert eine C++ Klasse welche die Dauer eines Tastendrucks ermittelt. Wird die Taste gedrückt
oder losgelassen, ruft das Objekt eine Funktion auf und übergibt die Dauer. Die Arduino Funktion millis() wird benötigt.

Zur Parametrisierung werden sechs Attribute verwendet:

* uint8_t gpio - Die Nummer des GPIO Pin. (kein Standardwert)
* void call - Der Name der Funktion welche nach einem Tastendruck aufgerufen wird. (kein Standardwert)
* uint8_t normally - Wählt NO oder NC Taste. (normOpen oder normClosed, Standardwert normOpen)
* uint8_t active - Wenn der Pegel des GPIO Pin bei gedrückter Taste „LOW“ ist, ist hier activeLow zu übergeben. (Standardwert activeLow)
* uint32_t bounce - Zeit in ms in welcher als Prellschutz keine Auswertung erfolgt. (Standardwert 50)
* uint32_t max - Zeit nach welcher das Warten auf einen Tastendruck abgebrochen wird. Der Wert btInfinite steht für unendlich. (Standardwert btInfinite)
* bool pull - Legt fest ob die Pull Up/Down Widerstände aktiviert werden. True aktiviert sie. (Standardwert true)

Folgende Methoden werden unterstützt:

* constructor(gpio,call,normally,active,bounce,max,pull)
* set(gpio,call,normally,active,bounce,max,pull)
* worker() - Diese Methode muss zyklisch im Main Loop aufgerufen werden.

### Einfaches Beispiel
Gibt die Dauer eines Tastendrucks auf der seriellen Schnittstelle aus.

    #include "buttonTimer.h"
    
    void doExampleOne(uint8_t gpio,uint32_t duration) { Serial.println(duration); }
    
    buttonTimer exampleOne(19,doExampleOne,activeLow,50,5000,true);
    
    void setup() { Serial.begin(115200); }
    
    void loop() { exampleOne.worker(); }