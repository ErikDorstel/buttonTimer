# buttonTimer
Arduino millis() based buttonTimer library

This library defines a C++ class to evaluate the time that a button was closed. Is the button pressed or
released the object calls a function and passes the duration. The Arduino function millis() is required.

Six attributes are used for parameterization:

* uint8_t gpio - The number of the GPIO port. (no default value)
* void call - The name of a function to call when the button is released. (no default value)
* uint8_t normally - Selects the normally state. (normOpen or normClosed, default value normOpen)
* uint8_t active - The value activeLow configure the GPIO port to active low. (default value activeLow)
* uint32_t bounce - The time in ms at which level changes are suppressed to prevent bouncing. (default value 50)
* uint32_t max - The maximum time in ms to wait for button release. Set value btInfinite for infinite. (default value btInfinite)
* bool pull - If true the pull up/down resistors get activated. (default value true)

The following methods are supported:

* constructor(gpio,call,normally,active,bounce,max,pull)
* set(gpio,call,normally,active,bounce,max,pull)
* worker() - This method must be called cyclically in the main loop.

### Basic example
Outputs the duration the button was pressed on the serial interface.

    #include "buttonTimer.h"
    
    void doExampleOne(uint8_t gpio,uint32_t duration) { Serial.println(duration); }
    
    buttonTimer exampleOne(19,doExampleOne,activeLow,50,5000,true);
    
    void setup() { Serial.begin(115200); }
    
    void loop() { exampleOne.worker(); }