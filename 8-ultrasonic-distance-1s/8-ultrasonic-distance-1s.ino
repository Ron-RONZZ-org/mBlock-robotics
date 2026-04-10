// Exercice 8 : capteur ultrason (afficher la distance chaque seconde)

#include "MeAuriga.h"
#include "Wire.h"

MeUltrasonicSensor ultrasound(10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int distanceCm = ultrasound.distanceCm();
  Serial.print("distance(cm): ");
  Serial.println(distanceCm);
  delay(1000);
}
