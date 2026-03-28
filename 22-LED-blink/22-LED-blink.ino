#include "MeAuriga.h"
#include "Wire.h"

// Tutmondaj variabloj
int Nled = 12;
MeRGBLed led(0, Nled);
int lastBlinkTime = 0;
int i = 0;
unsigned long currentTime;

void setup() {
  Serial.begin(9600);
  // efektivigita unufoje
  led.setpin(44);
  led.setColor(0, 0, 0, 0); // ekbrilo de la unua LED
}

void loop() {
  currentTime = millis() % 16384;

  // efektivigita en buklo ĉiun 200ms
  if (currentTime - lastBlinkTime > 200) {
    lastBlinkTime = currentTime;

    // malŝaltu la antaŭan LED
    led.setColor(i+1, 0, 0, 0);

    // sekva LED
    i = (i + 1) % Nled;

    // ekbrilu la aktualan LED
    led.setColor(i+1, random(100,255),random(100,255),random(100,255));
    Serial.print("currentTime: ");
    Serial.print(currentTime);
    Serial.print("  i: ");
    Serial.println(i);
  }

  // ĝisdatigu la LED-ojn
  led.show();
}

