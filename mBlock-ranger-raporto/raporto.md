# Raport de TP: Informatique industrielle UE 223
#### Par Rong ZHOU 
#### rong.zhou6@etu.univ-lorraine.fr
#### Université de Lorraine 

## Introduction

Pendant les TPs d'informatique industrielle UE223, nous avons programmé un petit robot arduino pour effectuer plusieurs tâches autonomes, y compris la detection de distance, son, et lumière, ainsi l'action motorielle ou lumineuse correspondante.

## mBlock Ranger

Dans ce TP, nous avons utilisé mBlock ranger, un robot éducatif fabriqué par l'entreprise chinoise makerBlock, qui peut être construit soit comme char, soit comme véhicule de course à trois roue, soit comme véhicle auto-équilibrant. Notre robot est assemblé comme char.

Le documentation officielle sur cette robot peut-être retrouvé [ici](https://qiniu.makeblock.com/makeblock-download/mBot-Ranger_Blue_STD_User%20%20Manual_Fr_D1.1.14_7.40.4620_View.pdf)

## programmation

Le mBlock ranger comprend le langage de programmation C++, plus précisement dans le context d'Arduino, qui nous permet d'utiliser des boucles pour répéter des instructions pour un certain nombre de répétitions voire vers l'infini, notamment, tous les programmes arduino comprend une partie `loop()`, qui s'agit d'une boucle infinie. (Q2) Les boucles nous permets de faire marcher le robot de manière autonome dans un contexte défini.

### Utilisation des capteurs

Le robot mBlock ranger que nous avons manipulé possède plusieurs capteurs:

- capteurs de lumière (2)
- capteurs de son
- capteurs de distance ultrasonic
- gyroscope

Les capteurs de lumière et son capturent des signals analogues, puis les convetissent en signals numériques par approximation. Plus précisement, le capteur de lumière capture le niveau de luminosité, puis le convetit en integer 0-1024.(Q1), où le capteur de bruit suit le même processus pour niveau de bruit. Empiriquement, nous trouvons que en silence, le mésure numérique est en-dessous de 100, où avec un fond de bruit léger dans la salle de TP la valeur est alentours de 200, et le fait de parler au robot augment la valeur à l'alentour de 500. (Q6)

Le capteur de distance ultrasonic, qui calcule la distance d'obstacle en face par mésure du temps entre l'émission d'un signal ultrasound et la réception de la réflexion de l'obstacle. Empiriquement, nous avons identifié le domaine de mésurement à 0-4000mm. La sensitivité est 10mm (Q9).

Le gyroscope mésure l'orientation du robot dans toutes les trois dimensions. Alors que le robot est dans l'orientation naturelle par terre, les valeurs y et x sont 0. La valeur 0 pour z est simplement l'orientation horizonal à l'initiation. La valeur z donc mésure l'angle entre l'orientation actuel du robot par rapport de l'initial, dans la limite de -180 et 180 degrés.

<img style="width: 300px;" src="mBlock-ranger.svg" alt="gyroscope orientation">

### sorties/retours

Le mBlock ranger est équipé d'un panneau de 12 LED et 2 moteurs. Cela signifie qu'on peut avoir des retours visuels en plus des retours automotifs.

#### LEDs

Les 12 LEDs sont contrôlée par la classe `MeRGBLed`, qui nous permet de contrôler tous les LEDs à la fois par `{instance}.setColor(0,R,G,B);`, ou `{instance}.setColor(i,R,G,B);`, où i est un entier entre 1 et 12, et R,G,B sont des valeurs de luminosité pour les couleurs rouge, vert et bleu respectivement. Tous couleurs peuvent être affiché par une combination de rouge, vert, bleu. Jaune, par exemple, a une valeur RGB de (255,255,0) (Q5).

#### Motors

Les moteurs de mBlock ranger sont controlés par la classe `MeEncoderOnBoard`, qui nous permet de régler la vitesse des moteurs par `motor.setMotorPwm(v);`, where `v`doit être un entier entre 0 et 255. 255 correspond à plein vitesse, et 0 correspond à l'arrêt complet.

Comme les moteurs sont des moteurs pas à pas, il est également possible de faire marcher les moteurs pour une certaine distance avec `
move(degrees,speed)`, où `degrees` est le degrés en rotation (360°/tour) pour les moteurs. (Q12) L'utilisation de cette méthode permet du contrôle plus affiné sur la motion de robot, qui peut être utile dans les routines préprogrammée, où la précision est importante (Q14-15)

### specimen de code

```ino
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

    // custom code

  }

```

