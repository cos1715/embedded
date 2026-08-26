#include <Arduino.h>
#include "tasks/task1_star.h"
// #include "tasks/task1_crash.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  task1StarSetup();
}

void loop() {}