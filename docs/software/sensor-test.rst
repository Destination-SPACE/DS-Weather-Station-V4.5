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