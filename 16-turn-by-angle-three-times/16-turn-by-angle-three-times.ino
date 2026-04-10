// Exercice 16 : tourner par angle a, trois fois (avec gyroscope)

#include "MeAuriga.h"
#include "Wire.h"

const int Nled = 12;
MeRGBLed led(0, Nled);
MeGyro gyroSensor(0, 0x69);
MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

float a = 90.0; // Tester ensuite 150
const int turnPwm = 120;
const float toleranceDeg = 3.0;

float zStart = 0.0;
int stepIndex = 0;
bool turning = false;
bool done = false;

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

void startTurnStep() {
  gyroSensor.update();
  zStart = gyroSensor.getAngleZ();
  setTurnRight(turnPwm);
  turning = true;
  Serial.print("Demarrage rotation #");
  Serial.println(stepIndex + 1);
}

void markStepWithLed() {
  led.setColor(0, 0, 0, 0);
  led.setColor(0, 20, 20, 20);
  led.show();
  delay(1000);
  led.setColor(0, 0, 0, 0);
  led.show();
}

void setup() {
  Serial.begin(9600);
  led.setpin(44);
  led.setColor(0, 0, 0, 0);
  led.show();

  gyroSensor.begin();
  delay(200);

  stepIndex = 0;
  startTurnStep();
}

void loop() {
  if (done) {
    delay(200);
    return;
  }

  gyroSensor.update();
  float turned = deltaAngle(gyroSensor.getAngleZ(), zStart);

  if (turning && turned >= (a - toleranceDeg)) {
    stopRobot();
    turning = false;

    Serial.print("Rotation #");
    Serial.print(stepIndex + 1);
    Serial.print(" terminee, angle ~= ");
    Serial.println(turned);

    markStepWithLed();
    stepIndex++;

    if (stepIndex >= 3) {
      done = true;
      Serial.println("Exercice termine: 3 rotations effectuees.");
    } else {
      startTurnStep();
    }
  }

  delay(20);
}
