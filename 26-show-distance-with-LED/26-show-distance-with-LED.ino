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
float average_lightLevel;
MeUltrasonicSensor ultrasound(10);
int reading_ultraSound;
int printLoopInterval = 1000;
float distance_level;


// kutima header:

// efektivigita unufoje
void setup ()  {
  Serial.begin(9600);
  led.setpin(44);
  led.setColor(0, 0, 0, 0); // ekbrilo de la unua LED
                           
// kutima setup():

}

// efektivigita en buklo
void loop() {
  delay(10);
  currentTime = millis() % 16384; // `%`: eviti superfluon
  reading_lightSensor1 = lightSensor1.read();
  reading_lightSensor2 = lightSensor2.read();
  average_lightLevel = (reading_lightSensor1 + reading_lightSensor2) / 2048.0;
  reading_ultraSound = ultrasound.distanceCm();
  
  if (currentTime - lastPassTime >= printLoopInterval) {
    Serial.print("currentTime: ");
    Serial.print(currentTime);
    Serial.print(" light level(0 dark 1 light): ");
    Serial.print(average_lightLevel);
    Serial.print(" obstacleDistance: ");
    Serial.println(reading_ultraSound);
    lastPassTime = currentTime;
  }
    //kutima loop():
  led.setColor(0,0,0,0);
  distance_level = min(100, reading_ultraSound) / 100.0;
  for (int i = 1; i <= distance_level * 12; i++) {
     led.setColor(i, 10 * (1 - distance_level), 10 * distance_level, 0);
  }
  led.show();
}

// utilaj:
// random(min,max)
