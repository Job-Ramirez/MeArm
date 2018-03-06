#include "meArm.h"
#include <Servo.h>

int basePin = 11;
int shoulderPin = 6;
int elbowPin = 10;
int gripperPin = 3;

meArm arm;

void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
}

void loop() {
  arm.goDirectlyToCylinder(0,21, 25);
  delay(2000);
  arm.goDirectlyToCylinder(0,0,25);
  delay(1000);
}
