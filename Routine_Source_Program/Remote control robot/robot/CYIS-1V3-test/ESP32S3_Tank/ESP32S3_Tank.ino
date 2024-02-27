#include "tank_functions.h"
#include <WiFi.h>

void setup() {
  Serial.begin(115200); //set your serial monitor to this baud
  initMotors();

  accelerateForward(4000);

  delay(500);
  turnLeft(90);
  delay(500);

  accelerateForward(4000);

}

void loop() {

}
