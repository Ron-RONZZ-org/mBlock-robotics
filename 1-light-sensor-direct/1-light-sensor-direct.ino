// Exercice 1 : capteur de luminosite (mode direct)

#include "MeAuriga.h"
#include "Wire.h"

MeLightSensor lightSensor1(12);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lightValue = lightSensor1.read();
  Serial.print("lightSensor1: ");
  Serial.println(lightValue);
  delay(500);
}
