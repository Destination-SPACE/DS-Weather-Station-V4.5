/*******************************************************************************
DESTINATION WEATHER STATION V4.5 EXAMPLE - SENSOR TEST

This is an example sketch for the Destination Weather Station v4.5 remote
sensing platform to test the BME280 humidity, pressure, & temperature sensor as
well as the other classroom kit sensors.

modified 2024-03-26
by Madison Gleydura

MIT LICENSE AGREEMENT

Copyright © 2024 Destination SPACE Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

//Import system libraries
#include <Wire.h>

//Import sensor libraries
#include <Adafruit_BME280.h>
#include <Adafruit_LTR390.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VEML7700.h>
#include <ScioSense_ENS160.h>
#include <SensirionI2CScd4x.h>

#define SEALEVELPRESSURE_HPA (1013.25) //Define sea-level pressure as 1013.25hPa

//Set sensor functions
Adafruit_BME280 BME280;
Adafruit_LTR390 LTR390 = Adafruit_LTR390();
Adafruit_VEML7700 VEML7700 = Adafruit_VEML7700();
ScioSense_ENS160 ENS160(ENS160_I2CADDR_0);
SensirionI2CScd4x scd4x;

//Define data types
float BME280_TEMP, BME280_PRES, BME280_HUMD, BME280_HI, BME280_ALT, ENS160_AQI, ENS160_AQI_PREV, ENS160_TVOC, ENS160_eCO2, LTR390_UVI, LTR390_RAW, VEML7700_ALS, VEML7700_WHITE, VEML7700_LUX, SCD40_CO2, SCD40_TEMP, SCD40_HUMD;
bool ENS160_STS = 1;
bool LTR390_STS = 1;
bool VEML7700_STS = 1;
bool SCD40_STS = 1;
int clock_timer, hh, mm, ss;
uint16_t SCD40_CO2_RAW;

void setup() {
  Serial.begin(115200); // Set serial stream to 115200bits/s
  while(!Serial); // Wait until serial monitor is open

  //Initialize BME280 sensor
  if(!BME280.begin(0x76, &Wire)){
    Serial.print("\n\nBME280 not found");
  }

  //Initialize ENS160 sensor
  if(ENS160.begin()){
    if(!ENS160.setMode(ENS160_OPMODE_STD)){
      Serial.print("\n\nENS160 failed to init");
      ENS160_STS = 0;
    }
    delay(10);
    if(ENS160.available()){
      ENS160.measure(true);
      ENS160_AQI_PREV = ENS160.getAQI();
    }
  }
  else{
    Serial.print("\n\nENS160 not found");
    ENS160_STS = 0;
  }

  //Initialize LTR390 sensor
  if(!LTR390.begin()){
    Serial.print("\n\nLTR390 not found");
    LTR390_STS = 0;
  }
  else{
    LTR390.setMode(LTR390_MODE_UVS);
    LTR390.setGain(LTR390_GAIN_3);
    LTR390.setResolution(LTR390_RESOLUTION_16BIT);
    LTR390.setThresholds(100,1000);
    LTR390.configInterrupt(true, LTR390_MODE_UVS);
  }

  //Initialize VEML7700 sensor
  if(!VEML7700.begin()){
    Serial.print("\n\nVEML7700 not found");
    VEML7700_STS = 0;
  }
  else{
    VEML7700.setLowThreshold(10000);
    VEML7700.setHighThreshold(20000);
    VEML7700.interruptEnable(true);
  }

  //Initialize SCD40 sensor
  scd4x.begin(Wire);
  if(scd4x.stopPeriodicMeasurement() || scd4x.startPeriodicMeasurement()){
      Serial.print("\n\nSCD40 failed to respond");
      SCD40_STS = 0;
  }

  //Print data table header
  Serial.print("\n\n+==============================================================================+\n|  TIME  | TEMP | HUM |  HI  | PRES | ALT | CO2 | TVOC |  AQI  |  UVI  |  LUX  |\n|hh:mm:ss| (°C) | (%) | (°C) | hPa  | (m) |(ppm)|(ppb.)|(0-300)|(0-+11)|(k-lux)|\n+==============================================================================+");
  
  //Set timer variables to zero
  clock_timer = 0;
  hh = 0;
  mm = 0;
  ss = 0;
}

void loop() {
  int delay_timer = millis(); // Reset delay timer

  //Collect Data from BME280
  BME280_TEMP = BME280.readTemperature();
  BME280_PRES = BME280.readPressure() / 100.0F;
  BME280_HUMD = BME280.readHumidity();
  BME280_ALT = BME280.readAltitude(SEALEVELPRESSURE_HPA);

  float h = (log10(BME280_HUMD)-2.0)/0.4343+(17.62*BME280_TEMP)/(243.12+BME280_TEMP);
  
  //Uncomment to calculate dew point and absolute humidity
  //float BME280_DEW_POINT = 243.12*h/(17.62-h); // Calculate dew point
  //float BME280_ABSOLUTE_HUMIDITY = 216.7*(BME280_HUMD/100.0*6.112*exp(17.62*BME280_TEMP/(243.12+BME280_TEMP))/(275.15+BME280_TEMP)); // Calculate absolute humidity

  float BME280_TEMP_F = (1.8*BME280_TEMP) + 32.0; // Convert Celsius to Fahrenheit

  //Calculate heat-index
  float BME280_HI_F = -42.379 + 2.04901523*BME280_TEMP_F + 10.14333127*BME280_HUMD - 0.22475541*BME280_TEMP_F*BME280_HUMD - 0.00683783*BME280_TEMP_F*BME280_TEMP_F - 0.05481717*BME280_HUMD*BME280_HUMD + 0.00122874*BME280_TEMP_F*BME280_TEMP_F*BME280_HUMD + 0.00085282*BME280_TEMP_F*BME280_HUMD*BME280_HUMD - 0.00000199*BME280_TEMP_F*BME280_TEMP_F*BME280_HUMD*BME280_HUMD; // Initial heat-index value

  if(BME280_HUMD < 13.0 && BME280_TEMP_F > 80.0 && BME280_TEMP_F < 112.0){ // If RH < 13% and 80 < T < 112
    BME280_HI_F = BME280_HI_F + (13.0 - BME280_HUMD)/4.0*sqrtf((17.0 - abs(BME280_TEMP_F - 95.0))/17);
  }
  else if(BME280_HUMD > 85 && BME280_TEMP_F > 80.0 && BME280_TEMP_F < 87.0){ // If RH > 85% and 80 < T < 87
    BME280_HI_F = BME280_HI_F + (BME280_HUMD - 85.0)/10*(87 - BME280_TEMP_F)/5;
  }
  else if(BME280_HI_F < 80.0){ // If HI < 80
    BME280_HI_F = 0.5 * (BME280_HI_F + 61.0 + 1.2*(BME280_HI_F - 68.0) + BME280_HUMD*0.094);
  }

  BME280_HI = (5.0/9.0)*(BME280_HI_F - 32.0); // Convert back to Celsius
  
  // Retrieve data from ENS160 VOC sensor
  if(ENS160_STS && ENS160.available()){
    ENS160.measure(true);
    ENS160_AQI = ENS160.getAQI(); // Get air quality index
    ENS160_TVOC = ENS160.getTVOC(); // Get total volitle organic compond concentration in parts per billion
    ENS160_eCO2 = ENS160.geteCO2(); // Get eCO2 measurment, derived from TVOC
    
    //Calculate better AQI based off of the Environmental Protection Agency
    float TVOC_CONSENTRATION = ENS160_TVOC*(29/24.45); // ug/m^3
    float alpha = 0.5; // Weight factor
    ENS160_AQI = alpha*TVOC_CONSENTRATION + (1-alpha)*ENS160_AQI_PREV; // Calculated from NowCast EPA algorithm
    ENS160_AQI_PREV = ENS160_AQI;
  }
  else{
    ENS160_AQI = 0;
    ENS160_TVOC = 0;
    ENS160_eCO2 = 0;
  }

  //Retrieve data from LTR390 UVA sensor
  if(LTR390_STS && LTR390.newDataAvailable()){
    LTR390_RAW = LTR390.readUVS();
    LTR390_UVI = LTR390_RAW / 2300.00; // Calculate UV-index from raw values
  }
  else{
    LTR390_UVI = 0;
  }

  if(VEML7700_STS){
    VEML7700_LUX = VEML7700.readLux(); // Retrieve data from VEML7700 ALS sensor
  }
  else{
    VEML7700_LUX = 0;
  }

  //Retrieve data from SCD40 CO2 sensors
  if(SCD40_STS){
    bool isDataReady = false; // Reset Data-Ready flag
    if(scd4x.getDataReadyFlag(isDataReady)){ // Check if there is data available to read
    }

    if(isDataReady){ // If data is ready to be read, read data
      if(scd4x.readMeasurement(SCD40_CO2_RAW, SCD40_TEMP, SCD40_HUMD)){
      }
      else if(SCD40_CO2_RAW == 0){ // If CO2 data is zero, keep data
      } 
      else{
        SCD40_CO2 = static_cast<float>(SCD40_CO2_RAW); // Cast CO2 unsigned 16bit-integer to type float
      }
    }
    else{ // If data is not ready, skip measurment
    }
  }
  else{
    SCD40_CO2 = 0;
  }
  
  //Clock timer
  ss = (millis() - clock_timer)/1000; // Set seconds to how much time has elapsed since first data read
  if(ss >= 60){ // If seconds is 60+, add 1 minutes and reset seconds variable
    clock_timer = millis();
    ss = ss - 60;
    mm = mm + 1;
    if(mm >= 60){ // If minutes is 60+, add 1 hours and reset minutes and seconds
      ss = ss - 60;
      mm = mm - 60;
      hh = hh + 1;
    }
  }

  char buffer[1024]; // Create 1024-bit buffer for data output
  sprintf(buffer, "\n|%02d:%02d:%02d| %5.2f|%5.2f| %5.2f|%6.1f|%5.1f| %4.0f| %5.0f|  %5.1f|  %5.2f|%7.2f|", hh, mm, ss, BME280_TEMP, BME280_HUMD, BME280_HI, BME280_PRES, BME280_ALT, SCD40_CO2, ENS160_TVOC, ENS160_AQI, LTR390_UVI, VEML7700_LUX);
  Serial.print(buffer); // Print buffer
  
  //Idle until it is time for next data read
  while(true){
    if(millis() - delay_timer >= 1000) break;
    delay(5);
  }
}