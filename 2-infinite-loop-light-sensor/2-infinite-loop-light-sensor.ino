// Exercice 2 : boucle infinie

#include "MeAuriga.h"
#include "Wire.h"

MeLightSensor lightSensor1(12);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lightValue = lightSensor1.read();
  Serial.print("Bonjour ! Lumiere: ");
  Serial.println(lightValue);
  delay(500);
}
