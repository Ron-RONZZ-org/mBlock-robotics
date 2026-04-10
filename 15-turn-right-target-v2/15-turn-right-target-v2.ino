// Exercice 15 : tourner en direction, v2 (arret pilote par gyroscope)

#include "MeAuriga.h"
#include "Wire.h"

MeGyro gyroSensor(0, 0x69);
MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

float a = 90.0; // Tester aussi 150, 270, 360
const int turnPwm = 120;
const float toleranceDeg = 3.0;

float zStart = 0.0;
bool finished = false;

void setTurnRight(int pwm) {
  motor1.setMotorPwm(pwm);
  motor2.setMotorPwm(pwm);
}

void stopRobot() {
  motor1.setMotorPwm(0);
  motor2.setMotorPwm(0);
}

float deltaAngle(float current, float start) {
  float d = current - start;
  while (d < 0) d += 360.0;
  while (d >= 360.0) d -= 360.0;
  return d;
}

void setup() {
  Serial.begin(9600);
  gyroSensor.begin();
  delay(200);
  gyroSensor.update();
  zStart = gyroSensor.getAngleZ();

  Serial.print("v2: rotation droite cible a=");
  Serial.println(a);
  setTurnRight(turnPwm);
}

void loop() {
  gyroSensor.update();
  float z = gyroSensor.getAngleZ();
  float turned = deltaAngle(z, zStart);

  if (!finished && turned >= (a - toleranceDeg)) {
    stopRobot();
    finished = true;
    Serial.print("Rotation terminee, angle atteint: ");
    Serial.println(turned);
  }

  if (!finished) {
    Serial.print("turned: ");
    Serial.println(turned);
  }

  delay(20);
}
