// bibliotekoj kaj variabloj tutmondaj

#include "MeAuriga.h"
#include "Wire.h"

unsigned long currentTime;
unsigned long lastPassTime = 0;

int Nled = 12;
MeRGBLed led(0, Nled); // 0: ĉio, LED: 1->Nled led.setColor(LED_num,R0_255,G0_255,B0_255)

MeLightSensor lightSensor1(12); // lightSensor1.read();
MeLightSensor lightSensor2(11);
int reading_lightSensor1, reading_lightSensor2;
float average_lightLevel;

MeUltrasonicSensor ultrasound(10);
int reading_ultraSound;

MeGyro gyroSensor(0, 0x69); // Gyro object from Makeblock (port 0, I2C address 0x69)

MeSoundSensor sound(14);
int soundLevel;

MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

int motor1_v, motor2_v;


// Struct for gyro readings
struct Gyro {
  float x;
  float y;
  float z;
};

Gyro gyro; // instance to hold current gyro values

int LoopInterval = 1000;

// efektivigita unufoje
void setup() {
  Serial.begin(9600);

  led.setpin(44);
  led.setColor(0, 255, 255, 255); // ekbrilo de la unua LED
  led.show();
  delay(500);
  led.setColor(0,0,0,0);
  led.show();
  // Iniciigo de gyroskopo
  gyroSensor.begin();
  motor1_v=128,motor2_v=128;
  motor1.setMotorPwm(-motor1_v);
  motor2.setMotorPwm(motor2_v);
  delay(1000);
  motor1_v=0,motor2_v=0;
  motor1.setMotorPwm(-motor1_v);
  motor2.setMotorPwm(motor2_v);

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
  soundLevel=sound.strength();
  // Presado ĉe intervalloj
  if (currentTime - lastPassTime >= LoopInterval) {
    Serial.print("currentTime: ");
    Serial.print(currentTime);
    Serial.print(" light level(0 dark 1 light): ");
    Serial.print(average_lightLevel);
    Serial.print(" obstacleDistance: ");
    Serial.println(reading_ultraSound);
    Serial.print(" sound level:");
    Serial.print(soundLevel);
    Serial.print(" gyro (X,Y,Z): (");
    Serial.print(gyro.x);
    Serial.print(", ");
    Serial.print(gyro.y);
    Serial.print(", ");
    Serial.print(gyro.z);
    Serial.println(")");
    lastPassTime = currentTime;

    // kutima loop()


  }

  // kutima loop(): simple LED off
  led.setColor(0,0,0,0);
  led.show();
}

// utilaj:
// random(min,max)
