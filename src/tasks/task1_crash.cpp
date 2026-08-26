#include <Arduino.h>
#include <stdlib.h>
#include "tasks/task1_crash.h"

void task1Setup() {
  Serial.println("INFO | TASK 1 | ready");
}

void task1Loop() {
  delay(5000);
  Serial.println("ERROR | TASK 1 | intentional crash");
  abort();
}