// buttonTimer 2022 by Erik Dorstel
// published 2022 under GNU GENERAL PUBLIC LICENSE Version 3
// https://github.com/ErikDorstel/buttonTimer
//
// This library defines a C++ class to evaluate the time that a button was closed. Is the button pressed or
// released the object calls a function and passes the duration. The Arduino function millis() is required.
//
// Six attributes are used for parameterization:
//
// * uint8_t gpio - The number of the GPIO port. (no default value)
// * void call - The name of a function to call when the button is released. (no default value)
// * uint8_t active - The value activeLow configure the GPIO port to active low. (default value activeLow)
// * uint32_t bounce - The time in ms at which level changes are suppressed to prevent bouncing. (default value 50)
// * uint32_t max - The maximum time in ms to wait for button release. Set value infinite for infinite. (default value infinite)
// * bool pull - If true the pull up/down resistors get activated. (default value true)
//
// The following methods are supported:
//
// * constructor(gpio,call,active,bounce,max,pull)
// * set(gpio,call,active,bounce,max,pull)
// * worker() - This method must be called cyclically in the main loop.

#ifndef BUTTON_TIMER_H
#define BUTTON_TIMER_H

#define infinite 0
#define activeLow 0
#define activeHigh 1

class buttonTimer {
  public:
    uint8_t gpio;
    void (*call)(uint8_t,uint32_t)=nullptr;
    uint8_t active=activeLow;
    uint32_t bounce=50;
    uint32_t max=infinite;
    bool pull=true;
    uint8_t lastState=!active;
    uint8_t currState=!active;
    uint32_t lastTime=0;
    uint32_t duration=0;

    buttonTimer(uint8_t value1,void (*value2)(uint8_t,uint32_t),uint8_t value3=activeLow,uint16_t value4=50,uint32_t value5=infinite,uint8_t value6=true) {
      gpio=value1; call=value2; active=value3; bounce=value4; max=value5; pull=value6; setPinMode(); }

    void set(uint8_t value1,void (*value2)(uint8_t,uint32_t),uint8_t value3=activeLow,uint16_t value4=50,uint32_t value5=infinite,uint8_t value6=true) {
      gpio=value1; call=value2; active=value3; bounce=value4; max=value5; pull=value6; setPinMode(); }

    void setPinMode() {
      if (pull==false) { pinMode(gpio,INPUT); }
      else { if (active==activeLow) { pinMode(gpio,INPUT_PULLUP); } else { pinMode(gpio,INPUT_PULLDOWN); } } }

    void doCallback() { if (call!=nullptr) { call(gpio,duration); } }

    void worker() {
      currState=digitalRead(gpio); duration=millis()-lastTime;
      if (lastState==active && currState==!active && duration>bounce) { lastTime=millis(); lastState=!active; doCallback(); }
      if (lastState==!active && currState==active && duration>bounce) { lastTime=millis(); lastState=active; duration=0; doCallback(); }
      if (currState==active && max && duration>=max) { lastTime=millis(); lastState=active; doCallback(); } } };

#endif
