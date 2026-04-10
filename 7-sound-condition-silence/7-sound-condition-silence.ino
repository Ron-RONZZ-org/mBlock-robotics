// Exercice 7 : conditions (volume seulement si on parle, sinon "silence")

#include "MeAuriga.h"
#include "Wire.h"

MeSoundSensor sound(14);
const int speechThreshold = 180;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int soundLevel = sound.strength();

  if (soundLevel > speechThreshold) {
    Serial.print("volume: ");
    Serial.println(soundLevel);
  } else {
    Serial.println("silence");
  }

  delay(200);
}
