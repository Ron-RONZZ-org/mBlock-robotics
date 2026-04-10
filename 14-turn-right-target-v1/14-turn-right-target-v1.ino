// Exercice 14 : tourner en direction, v1 (pilotage temporel)

#include "MeAuriga.h"
#include "Wire.h"

MeGyro gyroSensor(0, 0x69);
MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

float a = 90.0; // Tester aussi 150, 270, 360
const int turnPwm = 120;
const float degPerSecondEstimate = 180.0; // calibration empirique
bool done = false;

void setTurnRight(int pwm) {
  motor1.setMotorPwm(pwm);
  motor2.setMotorPwm(pwm);
}

void stopRobot() {
  motor1.setMotorPwm(0);
  motor2.setMotorPwm(0);
}

void setup() {
  Serial.begin(9600);
  gyroSensor.begin();

  unsigned long turnMs = (unsigned long)(1000.0 * (a / degPerSecondEstimate));
  Serial.print("v1: rotation droite cible a=");
  Serial.print(a);
  Serial.print(" deg, duree estimee(ms)=");
  Serial.println(turnMs);

  setTurnRight(turnPwm);
  delay(turnMs);
  stopRobot();
  done = true;
}

void loop() {
  if (done) {
    gyroSensor.update();
    Serial.print("Angle Z mesure apres rotation: ");
    Serial.println(gyroSensor.getAngleZ());
    delay(1000);
  }
}
