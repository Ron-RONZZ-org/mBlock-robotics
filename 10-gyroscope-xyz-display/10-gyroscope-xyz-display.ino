// Exercice 10 : gyroscope (afficher X, Y, Z en meme temps)

#include "MeAuriga.h"
#include "Wire.h"

MeGyro gyroSensor(0, 0x69);

void setup() {
  Serial.begin(9600);
  gyroSensor.begin();
}

void loop() {
  gyroSensor.update();

  float x = gyroSensor.getAngleX();
  float y = gyroSensor.getAngleY();
  float z = gyroSensor.getAngleZ();

  Serial.print("gyro X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.println(z);

  delay(200);
}
