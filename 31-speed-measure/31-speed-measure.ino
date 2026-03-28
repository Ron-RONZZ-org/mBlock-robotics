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

MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

int motor1_v, motor2_v;
float currentDistance,timeLapsed,lastDistance,speedLevel,speed_in_m_s,distance_change,i;

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
}

// efektivigita en buklo
void loop() {
  delay(10);
  currentTime = millis() % 16384; // `%`: eviti superfluon
  timeLapsed=currentTime-lastPassTime;
  if (timeLapsed > 500){
    lastPassTime=currentTime;
    currentDistance=reading_ultraSound;
    Serial.print("last mesured distance: ");
    Serial.print(lastDistance);
    Serial.print(" current distance: ");
    Serial.print(currentDistance);
    distance_change=currentDistance-lastDistance;
    lastDistance=currentDistance;
    speed_in_m_s=distance_change/timeLapsed*10;
    Serial.print("speed measured (m/s):");
    Serial.println(speed_in_m_s);
    speedLevel= min(abs(speed_in_m_s)/3,1);
    led.setColor(0,0,0,0);
    for (i=1; i<Nled*speedLevel+1; i++){
    led.setColor(i,100*speed_in_m_s,100*(1-speed_in_m_s),0);
    }
    led.show();
  }
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
  if (currentTime - lastPassTime >= LoopInterval) {
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

    // kutima loop()


  }

  // kutima loop(): simple LED off
  led.setColor(0,0,0,0);
  led.show();
}

// utilaj:
// random(min,max)
