// Exercice 17 : distance vs orientation (scan 360 par pas de a)

#include "MeAuriga.h"
#include "Wire.h"

const int Nled = 12;
const int maxDistanceCm = 120;

MeRGBLed led(0, Nled);
MeGyro gyroSensor(0, 0x69);
MeUltrasonicSensor ultrasound(10);
MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

float a = 10.0; // Tester aussi 15
const int turnPwm = 120;
const float toleranceDeg = 2.0;

float zStart = 0.0;
float turnedTotal = 0.0;
float turnedStepStart = 0.0;
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

void showDistanceOnLeds(int distanceCm) {
  int clampedDistance = constrain(distanceCm, 0, maxDistanceCm);
  int ledsOn = map(clampedDistance, 0, maxDistanceCm, 0, Nled);

  led.setColor(0, 0, 0, 0);
  for (int i = 1; i <= ledsOn; i++) {
    led.setColor(i, 6, 6, 6); // faible intensite
  }
  led.show();
}

void setup() {
  Serial.begin(9600);
  led.setpin(44);
  led.setColor(0, 0, 0, 0);
  led.show();

  gyroSensor.begin();
  delay(200);
  gyroSensor.update();
  zStart = gyroSensor.getAngleZ();
  turnedStepStart = 0.0;

  setTurnRight(turnPwm);
}

void loop() {
  if (finished) {
    delay(200);
    return;
  }

  gyroSensor.update();
  float turnedNow = deltaAngle(gyroSensor.getAngleZ(), zStart);

  if ((turnedNow - turnedStepStart) >= (a - toleranceDeg)) {
    stopRobot();

    int d = ultrasound.distanceCm();
    showDistanceOnLeds(d);

    Serial.print("orientation(deg): ");
    Serial.print(turnedNow);
    Serial.print(" distance(cm): ");
    Serial.println(d);

    turnedStepStart = turnedNow;
    turnedTotal = turnedNow;

    if (turnedTotal >= (360.0 - a)) {
      finished = true;
      stopRobot();
      Serial.println("Scan 360 termine.");
      return;
    }

    delay(80);
    setTurnRight(turnPwm);
  }

  delay(10);
}
