// Exercice 4 : variable i affichee et incrementee en continu

#include "MeAuriga.h"
#include "Wire.h"

long i = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("i = ");
  Serial.println(i);
  i = i + 1;
  delay(200);
}
