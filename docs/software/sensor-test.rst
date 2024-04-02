.. Copyright 2024 Destination SPACE Inc.
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

.. _sensor-test:

Sensor Test Sketch
==================

The `Sensor Test <https://gitlab.com/Destination-SPACE/ds-weather-station-v4.5/-/blob/main/software/Sensor_Test/Sensor_Test.ino>`_ sketch is used to make sure the sensors on the weather station are working correctly. Use this sketch as the first program to upload after the `Blink <https://gitlab.com/Destination-SPACE/ds-weather-station-v4.5/-/blob/main/software/Blink/Blink.ino>`_ sketch.

Libraries
---------

For the Sensor Test sketch, many more libraries are required. These can be split into two categories; System libraries and sensor libraries. In this example only one system library is required, which is the `Wire Library <https://docs.arduino.cc/learn/communication/wire/#wire-library>`_. This is a default Arduino library and is used to communicate with sensors on the Inter-Integrated Circuit (I2C) protocol. More details about the protocol can be found `here <https://docs.arduino.cc/learn/communication/wire/>`_.

The libraries required to use all of the sensors on your weather stations and for the classroom expansion sensors have been pre-installed. A list of the libraries are below.

.. code-block:: cpp
   
   //Import system libraries
   #include <Wire.h>

   //Import sensor libraries
   #include <Adafruit_BME280.h>
   #include <Adafruit_LTR390.h>
   #include <Adafruit_Sensor.h>
   #include <Adafruit_VEML7700.h>
   #include <ScioSense_ENS160.h>
   #include <SensirionI2CScd4x.h>

Hardware Definitions
--------------------
Only one hardware definition is required for this example. This defines mean sea-level pressure, which is used to calculate an approximate value for altitude using temperature and pressure. By default, this value is set to 1013.25 hPa. You are welcome to change this value to the current sea-level pressure in your region. Click `here <>`_ to find out more about calculating barometric altitude.

.. code-block:: cpp
   
   #define SEALEVELPRESSURE_HPA (1013.25)

Define Sensor Functions
-----------------------

Several sensor functions need to be defined to get the sensors to work. This ensures that each sensor is communicating to the correct `address <https://learn.adafruit.com/i2c-addresses/overview>`_. These are also used to define which variable you will be using to communicate with the sensor.

.. code-block:: cpp

   Adafruit_BME280 BME280;
   Adafruit_LTR390 LTR390 = Adafruit_LTR390();
   Adafruit_VEML7700 VEML7700 = Adafruit_VEML7700();
   ScioSense_ENS160 ENS160(ENS160_I2CADDR_0);
   SensirionI2CScd4x scd4x;

Define Data Types
-----------------

The next step is to define the data types of each variable. A data type is a way to standardize the formatting of a variable, such as if it is a text value, integer, boolean (True/False), or number with decimal places. Click `here <https://en.cppreference.com/w/cpp/language/types>`_ for the definitions of C++ fundamental types.

Below you can find the data types of the variables used in this example program. The version in the final code file is condensed to save on line-count.

.. code-block:: cpp

   float BME280_TEMP;      // Temperature
   float BME280_PRES;      // Pressure
   float BME280_HUMD;      // Humidity
   float BME280_HI;        // Heat-index
   float BME280_ALT;       // Barometric altitude
   float ENS160_AQI;       // Air Quality Index
   float ENS160_AQI_PREV;  // Previous AQI value
   float ENS160_TVOC;      // Total Volatile Organic Compounds
   float ENS160_eCO2;      // Calculated CO2 concentration
   float LTR390_UVI;       // Ultra-Violet Index
   float LTR390_RAW;       // Raw UV data
   float VEML7700_ALS;     // Ambient light data
   float VEML7700_WHITE;   // How much of the incoming light is white
   float VEML7700_LUX;     // Ambient light intensity
   float SCD40_CO2;        // Measured CO2 concentration
   float SCD40_TEMP;       // Temperature data from the CO2 sensor
   float SCD40_HUMD;       // Humidity data from the CO2 sensor
   
   int clock_timer;        // Time between data recordings
   int hh;                 // hours elapsed
   int mm;                 // minutes elapsed
   int ss;                 // seconds elapsed

   uint16_t SCD40_CO2_RAW; // Raw CO2 data

Setup Function
---------------

The next section is for the setup function. This is where all of the sensors are initialized and confirmed if they are connected or not. Each sensor has a slightly different initialization process, which is determined by the sensor libraries. Essentially, each sensor is checked to see if it is attached; if it is not, then it's status indicator is set to 0/False. Lastly, a header for all of the data parameters is printed to the serial monitor.

.. code-block:: cpp

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

Loop Function
-------------

The loop function is the main portion of the software where the data is collected and displayed. First, the variable for the delay_timer is set to be equal to the current processor clock time (in milliseconds). This is to help the code make sure it is refreshing at the correct rate.

.. code-block:: cpp
   int delay_timer = millis();

The next step is to read from all the individual sensors and preform any relevant calculations. Again, each sensor has it's own method to collect data.

BME280
^^^^^^

The Adafruit library for the BME280 makes it simple to collect data. It is a simple read function where you define the target variable and assign the data value to it.

.. code-block:: cpp
   BME280_TEMP = BME280.readTemperature();
   BME280_PRES = BME280.readPressure() / 100.0F;
   BME280_HUMD = BME280.readHumidity();
   BME280_ALT = BME280.readAltitude(SEALEVELPRESSURE_HPA);

Now, the data can be interpreted to get the desired weather parameters. With the BME280 weather sensor several parameters can be calculated. The ones featured in this program are `dew point <https://en.wikipedia.org/wiki/Dew_point>`_, `absolute humidity <https://en.wikipedia.org/wiki/Humidity>`_, and `heat index <https://en.wikipedia.org/wiki/Heat_index>`_. Only the calculation for heat index is active by default, but you can uncomment the dew point and absolute humidity calculations to include them. 

Heat index is calculated using `dry-bulb temperature <https://en.wikipedia.org/wiki/Dry-bulb_temperature>`_ and relative humidity. The formula used to calculate heat index was first derived in `The Assessment of Sultriness. Part I: A Temperature-Humidity Index Based on Human Physiology and Clothing Science <https://journals.ametsoc.org/view/journals/apme/18/7/1520-0450_1979_018_0861_taospi_2_0_co_2.xml>`_ by R.G. Steadman in 1979. His results were then interpreted by the National Weather Service in technical report `SR 90-23 <https://www.weather.gov/media/ffc/ta_htindx.PDF>`_ in 1990 to be approximated into an equation.

.. math:: HI = -42.379 + 2.04901523*T + 10.14333127*RH - 0.22375541*T*RH - 6.83783*10^(-3)*T^2 - 5.481717*10^(-2)*RH^2 + 1.22874*10^(-3)*T^2*RH + 8.5282*10*(-4)*T*RH^2 - 1.99*10^(-6)*T^2*RH^2
   :label: Heat-index equation
   :nowrap:


Where T is temperature in Fahrenheit and RH is relative humidity.

Because this is a regression fit, the equation has an error of ±1.3°F.

.. code-block:: cpp
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

ENS160
^^^^^^

The data collecting method for the ENS160 is very similar to the BME280. The parameters being collected are Air Quality Index (AQI) calculated from the German Federal Environmental Agency model, which is on a scale from 1 - 5, total volatile organic compounds (TVOC), and a calculated measurement of approximate Carbon-Dioxide concentration (eCO2).

.. code-block:: cpp
   ENS160.measure(true);
   ENS160_AQI = ENS160.getAQI();
   ENS160_TVOC = ENS160.getTVOC();
   ENS160_eCO2 = ENS160.geteCO2();

No further calculations need to be completed for this sensor.

LTR390
^^^^^^

Just like before, only the data needs to be pulled from the sensor with minimal calculations.

.. code-block:: cpp
   LTR390_RAW = LTR390.readUVS();
   LTR390_UVI = LTR390_RAW / 2300.00;

VEML7700
^^^^^^^^

.. code-block:: cpp
   VEML7700_LUX = VEML7700.readLux();

SCD40
^^^^^

.. code-block:: cpp
   bool isDataReady = false; // Reset Data-Ready flag
   if(scd4x.getDataReadyFlag(isDataReady)){
   }

   if(isDataReady){
      if(scd4x.readMeasurement(SCD40_CO2_RAW, SCD40_TEMP, SCD40_HUMD)){
      }
      else if(SCD40_CO2_RAW == 0){
      } 
      else{
         SCD40_CO2 = static_cast<float>(SCD40_CO2_RAW);
      }
   }
   else{
   }

Full Code
--------- 

Below is the full Sensor Test example sketch

.. code-block:: cpp
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

   float TVOC_CONCENTRATION_MIN = 5000;
   float TVOC_CONCENTRATION_MAX = 0;

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
   Serial.print("\n\n+==============================================================================+\n|  TIME  | TEMP | HUM |  HI  | PRES | ALT | CO2 | TVOC |  AQI  |  UVI  |  LUX  |\n|hh:mm:ss| (°C) | (%) | (°C) | hPa  | (m) |(ppm)|(ppb.)| (1-5) |(0-+11)|(k-lux)|\n+==============================================================================+");
   
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
      ENS160_TVOC = ENS160.getTVOC(); // Get total volatile organic compound concentration in parts per billion
      ENS160_eCO2 = ENS160.geteCO2(); // Get eCO2 measurement, derived from TVOC
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
      else{ // If data is not ready, skip measurement
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
   sprintf(buffer, "\n|%02d:%02d:%02d| %5.2f|%5.2f| %5.2f|%6.1f|%5.1f| %4.0f| %5.0f|  %5.0f|  %5.2f|%7.2f|", hh, mm, ss, BME280_TEMP, BME280_HUMD, BME280_HI, BME280_PRES, BME280_ALT, SCD40_CO2, ENS160_TVOC, ENS160_AQI, LTR390_UVI, VEML7700_LUX);
   Serial.print(buffer); // Print buffer
   
   //Idle until it is time for next data read
   while(true){
      if(millis() - delay_timer >= 1000) break;
      delay(5);
      }
   }
