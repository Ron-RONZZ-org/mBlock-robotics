// Exercice 5 : LEDs (sequence + couleurs aleatoires)

#include "MeAuriga.h"
#include "Wire.h"

const int Nled = 12;
MeRGBLed led(0, Nled);

int a = 1;
int r = 0;
int v = 0;
int b = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  led.setpin(44);
  led.setColor(0, 0, 0, 0);
  led.show();

  Serial.println("Phase 1: allumage successif (1 s)");
  for (a = 1; a <= Nled; a++) {
    led.setColor(a, 0, 0, 255);
    led.show();
    Serial.print("LED active: ");
    Serial.println(a);
    delay(1000);
  }

  delay(5000);
  led.setColor(0, 0, 0, 0);
  led.show();

  Serial.println("Phase 2: couleurs aleatoires");
  for (a = 1; a <= Nled; a++) {
    r = random(0, 256);
    v = random(0, 256);
    b = random(0, 256);
    led.setColor(a, r, v, b);

    Serial.print("LED ");
    Serial.print(a);
    Serial.print(" -> RGB(");
    Serial.print(r);
    Serial.print(",");
    Serial.print(v);
    Serial.print(",");
    Serial.print(b);
    Serial.println(")");
  }
  led.show();
}

void loop() {
  // Conserver l'affichage final des couleurs aleatoires
}
