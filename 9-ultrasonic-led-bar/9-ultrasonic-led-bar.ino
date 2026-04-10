// Exercice 9 : ultrason et LEDs (0..12 LEDs blanches proportionnelles a la distance)

#include "MeAuriga.h"
#include "Wire.h"

const int Nled = 12;
const int maxDistanceCm = 120;

MeRGBLed led(0, Nled);
MeUltrasonicSensor ultrasound(10);

void setup() {
  Serial.begin(9600);
  led.setpin(44);
  led.setColor(0, 0, 0, 0);
  led.show();
}

void loop() {
  int distanceCm = ultrasound.distanceCm();
  int clampedDistance = constrain(distanceCm, 0, maxDistanceCm);
  int ledsOn = map(clampedDistance, 0, maxDistanceCm, 0, Nled);

  led.setColor(0, 0, 0, 0);
  for (int i = 1; i <= ledsOn; i++) {
    led.setColor(i, 255, 255, 255);
  }
  led.show();

  Serial.print("distance(cm): ");
  Serial.print(distanceCm);
  Serial.print(" -> ledsOn: ");
  Serial.println(ledsOn);

  delay(100);
}
