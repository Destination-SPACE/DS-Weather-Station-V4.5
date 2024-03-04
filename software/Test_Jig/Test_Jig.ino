#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 BME280;

void setup(){
  Serial.begin(115200);
  if(!BME280.begin()){
    Serial.print("\nBME280 not found...");
    while(true){
      
    }
  }
}

void loop(){

}