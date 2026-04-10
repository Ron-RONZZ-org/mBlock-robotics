// Exercice 6 : capteur de son (affichage continu)

#include "MeAuriga.h"
#include "Wire.h"

MeSoundSensor sound(14);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int soundLevel = sound.strength();
  Serial.print("soundLevel: ");
  Serial.println(soundLevel);
  delay(200);
}
