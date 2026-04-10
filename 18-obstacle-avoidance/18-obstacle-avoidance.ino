// Exercice 18 : contourner un obstacle

#include "MeAuriga.h"
#include "Wire.h"

const int Nled = 12;
const int maxDistanceCm = 120;

MeRGBLed led(0, Nled);
MeGyro gyroSensor(0, 0x69);
MeUltrasonicSensor ultrasound(10);
MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

const int forwardPwm = 128;
const int turnPwm = 120;
const int stopDistanceCm = 30;
const float scanStepDeg = 15.0;
const float toleranceDeg = 2.0;

enum Mode { DRIVE, SCAN_TURN, SCAN_MEASURE, TURN_TO_BEST, STOPPED };
Mode mode = DRIVE;

float zScanStart = 0.0;
float turnedStepStart = 0.0;
float bestAngle = 0.0;
int bestDistance = -1;

void setForward(int pwm) {
  motor1.setMotorPwm(-pwm);
  motor2.setMotorPwm(pwm);
}

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

void startScan() {
  gyroSensor.update();
  zScanStart = gyroSensor.getAngleZ();
  turnedStepStart = 0.0;
  bestAngle = 0.0;
  bestDistance = -1;
  mode = SCAN_TURN;
  setTurnRight(turnPwm);
  Serial.println("Obstacle proche: scan 360 en cours...");
}

void setup() {
  Serial.begin(9600);

  led.setpin(44);
  led.setColor(0, 0, 0, 0);
  led.show();

  gyroSensor.begin();
  delay(200);

  setForward(forwardPwm);
  Serial.println("Mode DRIVE: avance v=128");
}

void loop() {
  gyroSensor.update();
  int d = ultrasound.distanceCm();

  if (mode == DRIVE) {
    if (d > 0 && d < stopDistanceCm) {
      stopRobot();
      delay(200); // arret provisoire
      startScan();
      return;
    }

    Serial.print("DRIVE distance(cm): ");
    Serial.println(d);
    delay(80);
    return;
  }

  float turnedNow = deltaAngle(gyroSensor.getAngleZ(), zScanStart);

  if (mode == SCAN_TURN) {
    if ((turnedNow - turnedStepStart) >= (scanStepDeg - toleranceDeg)) {
      stopRobot();
      mode = SCAN_MEASURE;
    }
    delay(10);
    return;
  }

  if (mode == SCAN_MEASURE) {
    int measure = ultrasound.distanceCm();
    showDistanceOnLeds(measure);

    Serial.print("SCAN angle=");
    Serial.print(turnedNow);
    Serial.print(" distance=");
    Serial.println(measure);

    if (measure > bestDistance) {
      bestDistance = measure;
      bestAngle = turnedNow;
    }

    turnedStepStart = turnedNow;

    if (turnedNow >= (360.0 - scanStepDeg)) {
      mode = TURN_TO_BEST;
      setTurnRight(turnPwm);
      Serial.print("Best angle=");
      Serial.print(bestAngle);
      Serial.print(" best distance=");
      Serial.println(bestDistance);
    } else {
      mode = SCAN_TURN;
      setTurnRight(turnPwm);
    }

    delay(50);
    return;
  }

  if (mode == TURN_TO_BEST) {
    if (turnedNow >= (bestAngle - toleranceDeg)) {
      stopRobot();
      mode = STOPPED;
      Serial.println("Robot oriente vers premiere zone la plus degagee.");
    }

    delay(10);
    return;
  }

  if (mode == STOPPED) {
    delay(200);
  }
}
