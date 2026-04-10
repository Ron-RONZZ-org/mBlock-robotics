// Exercice 13 : arret avant obstacle

#include "MeAuriga.h"
#include "Wire.h"

MeUltrasonicSensor ultrasound(10);
MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

const int speedCmd = 128;
const int stopDistanceCm = 50;
bool stopped = false;

void setDrive(int leftPwm, int rightPwm) {
  motor1.setMotorPwm(-leftPwm);
  motor2.setMotorPwm(rightPwm);
}

void setup() {
  Serial.begin(9600);
  setDrive(speedCmd, speedCmd);
  Serial.println("Robot en avance (v=128)");
}

void loop() {
  int d = ultrasound.distanceCm();

  if (!stopped && d > 0 && d < stopDistanceCm) {
    setDrive(0, 0);
    stopped = true;
    Serial.print("Obstacle detecte a ");
    Serial.print(d);
    Serial.println(" cm -> arret definitif");
  }

  if (!stopped) {
    Serial.print("distance(cm): ");
    Serial.println(d);
  }

  delay(100);
}
