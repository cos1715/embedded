#include <Arduino.h>
#include "tasks/task1_crash.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  task1Setup();
}

void loop() {
  task1Loop();
}