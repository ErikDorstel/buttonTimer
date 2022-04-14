# buttonTimer
Arduino millis() based buttonTimer library

This library defines a C++ class to evaluate the time that a button was closed. Is the button pressed or
released the object calls a function and passes the duration. The Arduino function millis() is required.

Six attributes are used for parameterization:

* uint8_t gpio - The number of the GPIO port. (no default value)
* void call - The name of a function to call when the button is released. (no default value)
* uint8_t active - The value LOW configure the GPIO port to active low. (default value LOW)
* uint16_t bounce - The time in ms at which level changes are suppressed to prevent bouncing. (default value 50)
* uint32_t max - The maximum time in ms to wait for button release. false for infinite. (default value false)
* uint8_t pull - If true the pull up/down resistors get activated. (default value true)

The following methods are supported:

* constructor(gpio,call) - Set gpio and call.
* constructor(gpio,call,active) - Set gpio, call and active.
* constructor(gpio,call,active,bounce) - Set gpio, call, active and bounce.
* constructor(gpio,call,active,bounce,max) - Set gpio, call, active, bounce and max.
* constructor(gpio,call,active,bounce,max,pull) - Set gpio, call, active, bounce, max and pull.
* set(gpio,call) - Set gpio and call.
* set(gpio,call,active) - Set gpio, call and active.
* set(gpio,call,active,bounce) - Set gpio, call, active and bounce.
* set(gpio,call,active,bounce,max) - Set gpio, call, active, bounce and max.
* set(gpio,call,active,bounce,max,pull) - Set gpio, call, active, bounce, max and pull.
* worker() - This method must be called cyclically in the main loop.

### Basic example
Outputs the duration the button was closed on the serial interface.

    #include "buttonTimer.h"
    
    void doExampleOne(uint8_t gpio,uint32_t duration) { Serial.println(duration); }
    
    buttonTimer exampleOne(19,doExampleOne,LOW,50,5000,true);
    
    void setup() { Serial.begin(115200); }
    
    void loop() { exampleOne.worker(); }