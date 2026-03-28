// bibliotekoj kaj tutmondaj variabloj

#include "MeAuriga.h"
#include "Wire.h"

unsigned long currentTime;
unsigned long lastPassTime = 0;

int Nled = 12;
MeRGBLed led(0, Nled); // 0: ĉio, LED: 1->Nled led.setColor(LED_num,R0_255,G0_255,B0_255)

MeLightSensor lightSensor1(12); // legi valoron de lum-sensilo 1
MeLightSensor lightSensor2(11); // legi valoron de lum-sensilo 2
int reading_lightSensor1;
int reading_lightSensor2;
float average_lightLevel;

MeUltrasonicSensor ultrasound(10); // ultrasona sensilo
int reading_ultraSound;

MeGyro gyroSensor(0, 0x69); // gyroskopo de Makeblock (port 0, I2C adreso 0x69)

MeEncoderOnBoard motor1(1); // enkodilo motoro 1
MeEncoderOnBoard motor2(2); // enkodilo motoro 2

// Struct por gyroskopo
struct Gyro {
  float x;
  float y;
  float z;
};

Gyro gyro; // instanco por teni aktualajn gyro valorojn

float v_1 = 0; // rapideco motoro 1
float v_2 = 0; // rapideco motoro 2

int loopInterval = 1000; // intervalo por presado en ms

// efektivigita unufoje ĉe starto
void setup() {
  Serial.begin(9600);

  led.setpin(44);
  led.setColor(0, 0, 0, 0); // ekbrilo de la unua LED

  // iniciigo de gyroskopo
  gyroSensor.begin();

  // iniciigo de motoroj
  motor1.setMotorPwm(v_1);
  motor2.setMotorPwm(v_2);
  v_1=100;
  v_2=-100;
}

// efektivigita en ĉiu buklo
void loop() {
  delay(10);
  currentTime = millis() % 16384; // `%`: eviti superfluon

  // legi valorojn de lum-sensiloj
  reading_lightSensor1 = lightSensor1.read();
  reading_lightSensor2 = lightSensor2.read();
  average_lightLevel = (reading_lightSensor1 + reading_lightSensor2) / 2048.0;

  // legi valoron de ultrasona distanco
  reading_ultraSound = ultrasound.distanceCm();

  // legi valorojn de gyroskopo
  gyroSensor.update();      // necesa antaŭ ĉiu legado
  gyro.x = gyroSensor.getAngleX();
  gyro.y = gyroSensor.getAngleY();
  gyro.z = gyroSensor.getAngleZ();
  // kontroli motorojn (nun simple uzas v_1 kaj v_2)
   motor1.setMotorPwm(v_1);
   motor2.setMotorPwm(v_2);

  // presado ĉe intervalloj
  if (currentTime - lastPassTime >= loopInterval) {
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
}
