//bibliotekojn kaj variabloj tutmondaj

#include "MeAuriga.h"
#include "Wire.h"

unsigned long currentTime;
int Nled = 12;
MeRGBLed led(0, Nled); // 0: ĉio, LED: 1_>Nled led.setColor(LED_num,R0_255,G0_255,B0_255)
MeLightSensor lightSensor1(12); // lightSensor1.read();
MeLightSensor lightSensor2(11);
int reading_lightSensor1;
int reading_lightSensor2;
// kutima header:
float reading_total;
float light_level;


// efektivigita unufoje
void setup ()  {
  Serial.begin(9600);
  led.setpin(44);
  led.setColor(0,100,100,100);
  led.show();
  delay(1000);
  led.setColor(0, 0, 0, 0); // ekbrilo de la unua LED
  led.show();
                           
// kutima setup():

}

// efektivigita en buklo
void loop() {
  currentTime = millis() % 16384; // `%`: eviti superfluon
  Serial.print("currentTime: ");
  Serial.print(currentTime);
  delay(500);
  reading_lightSensor1=lightSensor1.read();
  reading_lightSensor2=lightSensor2.read();
  led.setColor(0,0,0,0);
  led.show();
//kutima loop():
  Serial.println("sensor 1, sensor 2:");
  Serial.println(reading_lightSensor1);
  Serial.println(reading_lightSensor2);
  reading_total=reading_lightSensor1+reading_lightSensor2;
  light_level=reading_total/2048;
  for (int i=1;i<(light_level*12+1);i++) {
    //led.setColor(i,light_level*256,light_level*256,light_level*256);
    led.setColor(i,10-light_level*10,10*light_level,0);
  }
  led.show();
}


