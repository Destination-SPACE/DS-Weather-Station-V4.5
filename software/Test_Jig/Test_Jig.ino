#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define LED_RED 28
#define LED_GRN 24
#define LED_AMB 29

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 BME280;

void setup(){
  Serial.begin(115200);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GRN, OUTPUT);
  pinMode(LED_AMB, OUTPUT);

  if(!BME280.begin(0x76, &Wire)){
    if(!BME280.begin(0x77, &Wire)){
      Serial.print("\nBME280 found on 0x77...");
      while(true){
        digitalWrite(LED_AMB, HIGH);
        delay(100);
        digitalWrite(LED_AMB, LOW);
        delay(100);
        digitalWrite(LED_AMB, HIGH);
        delay(100);
        digitalWrite(LED_AMB, LOW);
        delay(100);
        digitalWrite(LED_AMB, HIGH);
        delay(100);
        digitalWrite(LED_AMB, LOW);
        delay(1000);
      }
    }
    else{
      Serial.print("\nBME280 not found...");
      digitalWrite(LED_RED, HIGH);
      while(true);      
    }
  }
  else{
    Serial.print("\nBME280 found on 0x76...");
    digitalWrite(LED_GRN, HIGH);
    delay(100);
    digitalWrite(LED_GRN, LOW);
    delay(100);
    digitalWrite(LED_GRN, HIGH);
    delay(100);
    digitalWrite(LED_GRN, LOW);
  }
}

void loop(){
  float BME280_TEMP = 0;
  for(int i = 0; i < 50; i++){
    float BME280_TEMP = BME280.readTemperature(); + BME280_TEMP;
  }
  BME280_TEMP = BME280_TEMP / 50;

  if(BME280_TEMP > 10.0 && BME280_TEMP < 50.0){
    Serial.print("\n\nPASS!");
    digitalWrite(LED_GRN, HIGH);
    while(true);
  }
  else{
    Serial.print("\n\nTemperature out of range...");
    while(true){
      digitalWrite(LED_AMB, HIGH);
      delay(100);
      digitalWrite(LED_AMB, LOW);
      delay(100);
      digitalWrite(LED_AMB, HIGH);
      delay(100);
      digitalWrite(LED_AMB, LOW);
      delay(100);
      digitalWrite(LED_AMB, HIGH);
      delay(100);
      digitalWrite(LED_AMB, LOW);
      delay(1000);
    }
  }
}