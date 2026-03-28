// bibliotekoj kaj variabloj tutmondaj

#include "MeAuriga.h"
#include "Wire.h"

unsigned long currentTime;
unsigned long lastPassTime = 0;
int Nled = 12;
MeRGBLed led(0, Nled); // 0: ĉio, LED: 1->Nled led.setColor(LED_num,R0_255,G0_255,B0_255)
MeLightSensor lightSensor1(12); // lightSensor1.read();
MeLightSensor lightSensor2(11);
int reading_lightSensor1;
int reading_lightSensor2;
MeUltrasonicSensor ultrasound(10);
int reading_ultraSound;


// kutima header:
int loopInterval = 1000;

// efektivigita unufoje
void setup ()  {
  Serial.begin(9600);
  led.setpin(44);
  led.setColor(0, 0, 0, 0); // ekbrilo de la unua LED
                           
// kutima setup():

}

// efektivigita en buklo
void loop() {
  currentTime = millis() % 16384; // `%`: eviti superfluon
  reading_lightSensor1 = lightSensor1.read();
  reading_lightSensor2 = lightSensor2.read();
  reading_ultraSound = ultrasound.distanceCm();

//kutima loop():
  if (currentTime - lastPassTime >= loopInterval) {
  Serial.print("currentTime: ");
  Serial.print(currentTime);
    // agoj
    Serial.print(" obstacleDistance: ");
    Serial.print(reading_ultraSound);
    Serial.print("");
    lastPassTime = currentTime;
  }
}

// utilaj:
// random(min,max)
