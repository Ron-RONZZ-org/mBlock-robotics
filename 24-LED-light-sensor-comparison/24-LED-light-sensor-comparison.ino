// bibliotekoj kaj variabloj tutmondaj

#include "MeAuriga.h"
#include "Wire.h"

unsigned long currentTime;
int Nled = 12;
MeRGBLed led(0, Nled); // 0: ĉio, LED: 1->Nled led.setColor(LED_num,R0_255,G0_255,B0_255)
MeLightSensor lightSensor1(12); // lightSensor1.read();
MeLightSensor lightSensor2(11);
int reading_lightSensor1;
int reading_lightSensor2;
int reading_difference;
// kutima header:
float reading_total;
float light_level;
boolean led_mode;


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
  led_mode = 0;
  currentTime = millis() % 16384; // `%`: eviti superfluon
  Serial.print("currentTime: ");
  Serial.print(currentTime);
  delay(500);
  reading_lightSensor1 = lightSensor1.read();
  reading_lightSensor2 = lightSensor2.read();
  led.setColor(0,0,0,0);
  led.show();
//kutima loop()
  Serial.println("sensor 1, sensor 2:");
  Serial.println(reading_lightSensor1);
  Serial.println(reading_lightSensor2);
  reading_difference = reading_lightSensor1 - reading_lightSensor2;
  if (reading_difference == 0){
    led.setColor(0,0,0,0);
    led.show();
    return;
  }
  else if (reading_difference > 0){
    led_mode = 1;
  }
  for (int i = 1; i <= 6; i++) {
    //led.setColor(i,light_level*256,light_level*256,light_level*256);
    led.setColor(i + led_mode * 6,10,10,10);
  }
  led.show();
}
