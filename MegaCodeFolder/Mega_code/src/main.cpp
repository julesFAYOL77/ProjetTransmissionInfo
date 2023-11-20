#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3DH.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (!lis.begin(0x18)) {   // Changer 0x18 par l'adresse I2C de votre accéléromètre si différente
    Serial.println("LIS3DH introuvable");
    while (1);
  }

  lis.setRange(LIS3DH_RANGE_4_G);   // Changer le range si nécessaire
}

void loop() {
  lis.read();   // lire les données

  Serial.print("X: "); Serial.print(lis.x); 
  Serial.print(" Y: "); Serial.print(lis.y);
  Serial.print(" Z: "); Serial.println(lis.z);

  delay(100);
}
