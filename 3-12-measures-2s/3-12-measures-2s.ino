// Exercice 3 : boucle N fois (12 mesures espacees de 2 s)

#include "MeAuriga.h"
#include "Wire.h"

MeLightSensor lightSensor1(12);

void setup() {
  Serial.begin(9600);
  Serial.println("Debut des 12 mesures...");

  for (int i = 1; i <= 12; i++) {
    int lightValue = lightSensor1.read();
    Serial.print("Mesure ");
    Serial.print(i);
    Serial.print("/12 : ");
    Serial.println(lightValue);
    delay(2000);
  }

  Serial.println("12 mesures terminees.");
}

void loop() {
  // Fin de l'exercice: rien a repeter
}
