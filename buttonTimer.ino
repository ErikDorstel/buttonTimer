// Example of using the buttonTimer library.

#include "buttonTimer.h"

void buttonChanged(uint8_t gpio,uint32_t duration) {
  Serial.print(gpio); Serial.print(",");
  Serial.print(duration); Serial.print("\r\n"); }

buttonTimer exampleOne(18,buttonChanged,LOW,50,5000,true);
buttonTimer exampleTwo(19,buttonChanged,LOW,50,5000,true);

void setup() { Serial.begin(115200); }

void loop() { exampleOne.worker(); exampleTwo.worker(); }
