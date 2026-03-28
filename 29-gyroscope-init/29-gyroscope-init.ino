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

MeGyro gyroSensor(0, 0x69); // Gyro object from Makeblock (port 0, I2C address 0x69)

// Struct for gyro readings
struct Gyro {
  float x;
  float y;
  float z;
};

Gyro gyro; // instance to hold current gyro values

// efektivigita unufoje
void setup() {
  Serial.begin(9600);

  led.setpin(44);
  led.setColor(0, 0, 0, 0); // ekbrilo de la unua LED

  // Iniciigo de gyroskopo
  gyroSensor.begin();
}

// efektivigita en buklo
void loop() {
  delay(10);
  currentTime = millis() % 16384; // `%`: eviti superfluon

  // Legado de lum-sensiloj
  reading_lightSensor1 = lightSensor1.read();
  reading_lightSensor2 = lightSensor2.read();
  average_lightLevel = (reading_lightSensor1 + reading_lightSensor2) / 2048.0;

  // Legado de ultrasona distanco
  reading_ultraSound = ultrasound.distanceCm();

  // Legado de gyroskopo
  gyroSensor.update();      // necesa antaŭ ĉiu legado
  gyro.x = gyroSensor.getAngleX();
  gyro.y = gyroSensor.getAngleY();
  gyro.z = gyroSensor.getAngleZ();

  // Presado ĉe intervalloj
  if (currentTime - lastPassTime >= printLoopInterval) {
    Serial.print("currentTime: ");
    Serial.print(currentTime);
    Serial.print(" light level(0 dark 1 light): ");
    Serial.print(average_lightLevel);
    Serial.print(" obstacleDistance: ");
    Serial.print(reading_ultraSound);
    Serial.print(" gyro (X,Y,Z): (");
    Serial.print(gyro.x);
    Serial.print(", ");
    Serial.print(gyro.y);
    Serial.print(", ");
    Serial.print(gyro.z);
    Serial.println(")");
    lastPassTime = currentTime;
  }

  // kutima loop(): simple LED off
  led.setColor(0,0,0,0);
  led.show();
}

// utilaj:
// random(min,max)
