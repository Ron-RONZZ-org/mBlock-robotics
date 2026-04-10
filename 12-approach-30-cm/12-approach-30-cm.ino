// bibliotekoj kaj variabloj tutmondaj

  #include <Arduino.h>
  #include <Wire.h>
  #include <SoftwareSerial.h>
  
  #include <MeAuriga.h>


unsigned long currentTime;
unsigned long lastPassTime = -3000;

int Nled = 12;
MeRGBLed led(0, Nled); // 0: ĉio, LED: 1->Nled led.setColor(LED_num,R0_255,G0_255,B0_255)

MeLightSensor lightSensor1(12); // lightSensor1.read();
MeLightSensor lightSensor2(11);
int reading_lightSensor1, reading_lightSensor2;
float average_lightLevel;

MeUltrasonicSensor ultrasound(10);
int reading_ultraSound,currentDistance;

MeGyro gyroSensor(0, 0x69); // Gyro object from Makeblock (port 0, I2C address 0x69)

MeSoundSensor sound(14);
int soundLevel;

MeEncoderOnBoard motor1(SLOT1);
MeEncoderOnBoard motor2(SLOT2);

void isr_process_encoder1(void)
{
    if (digitalRead(motor1.getPortB()) == 0) {
        motor1.pulsePosMinus();
    } else {
        motor1.pulsePosPlus();
    }
}

void isr_process_encoder2(void)
{
    if (digitalRead(motor2.getPortB()) == 0) {
        motor2.pulsePosMinus();
    } else {
        motor2.pulsePosPlus();
    }
}

int motor1_v, motor2_v;
bool moving=0;

// Struct for gyro readings
struct Gyro {
  float x;
  float y;
  float z;
};

Gyro gyro; // instance to hold current gyro values

int LoopInterval = 3000;

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
// Set PWM 8KHz
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

  attachInterrupt(motor1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(motor2.getIntNum(), isr_process_encoder2, RISING);

  motor1.setPulse(9);
  motor1.setRatio(39.267);
  motor1.setPosPid(1.8, 0, 1.2);
  motor1.setSpeedPid(0.18, 0, 0);

  motor2.setPulse(9);
  motor2.setRatio(39.267);
  motor2.setPosPid(1.8, 0, 1.2);
  motor2.setSpeedPid(0.18, 0, 0);
  delay(500);
  motor1.move(-360,150);
  motor2.move(360,150);
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
 }
}
// utilaj:
// random(min,max)
