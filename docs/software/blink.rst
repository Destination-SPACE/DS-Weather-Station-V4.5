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

.. _blink-sketch:

Blink Sketch
============

The `Blink <https://gitlab.com/Destination-SPACE/ds-weather-station-v4.5/-/blob/main/software/Blink/Blink.ino>`_ sketch is used as a beginners program and to test the on-board RGB LED and NeoPixel.

Libraries
---------

.. code-block:: cpp
   
   #include <Adafruit_NeoPixel.h>

The Blink Sketch has only one required library. This library is the `Adafruit NeoPixel Library <https://github.com/adafruit/Adafruit_NeoPixel>`_. This is used to send commands to the NeoPixel RGB LED on the Seeeduino XIAO.

Hardware Definitions
--------------------

Several hardware definitions need to be defined to use the RBG LED and the NeoPixel. These are defined by assigning each variable a General Purpose Input-Output (GPIO) pin on the XIAO and any other criteria specified by the NeoPixel library. What these definitions do is define the red, green, and blue pins of the normal RGB LED a GPIO pin, define the power and signal pin for the NeoPixel, and define the number of NeoPixels on the board.

.. code-block:: cpp

   #define RGB_R 17
   #define RGB_G 16
   #define RGB_B 25
   #define NEOPIXEL_PWR 11
   #define NEOPIXEL_PIN 12
   #define NEOPIXEL_NUM 1

Following the hardware definitions, the information specified above needs to be defined in the NeoPixel definition function

.. code-block:: cpp

   Adafruit_NeoPixel pixels(NEOPIXEL_NUM, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

Setup Function
--------------

The next step is to initialize the LEDs for the primary loop function. This is done by starting the NeoPixel function, initializing the power and signal pins, and defining the RGB LEDs pins as outputs.

.. code-block:: cpp

   void setup() {
      //Initialize NeoPixel
      pixels.begin();
      pinMode(NEOPIXEL_PWR, OUTPUT);
      digitalWrite(NEOPIXEL_PWR, HIGH);

      //Initialize RGB LED
      pinMode(RGB_R, OUTPUT);
      pinMode(RGB_G, OUTPUT);
      pinMode(RGB_B, OUTPUT);
   }

Loop Function
-------------

The final step is to send the commands to the NeoPixel and RGB LED. This is done by first clearing the NeoPixel's stored data, defining the color, and sending the neopixel the data. Additionally, there is a custom function to easily control the color of the RGB LED. This works by passing the red, green, and blue values to the function ``setColor()``. An example of the NeoPixel code and the RGB LED can be found below

.. code-block:: cpp
   
   pixels.clear();
   pixels.setPixelColor(0, pixels.Color(15, 25, 205));
   delay(400); // How long the NeoPixel stays on
   pixels.show();

.. code-block:: cpp
   setColor(15, 25, 205);

   void setColor(int VAL_GRN, int VAL_RED, int VAL_BLU){
      analogWrite(RGB_R, 255 - VAL_RED);
      analogWrite(RGB_G, 255 - VAL_GRN);
      analogWrite(RGB_B, 255 - VAL_BLU);
   }

Full Code
--------- 

Below is the full Blink example sketch

.. code-block:: cpp
   #include <Adafruit_NeoPixel.h> // Import Adafruit NeoPixel library

   //Define Hardware
   #define RGB_R 17
   #define RGB_G 16
   #define RGB_B 25
   #define NEOPIXEL_PWR 11
   #define NEOPIXEL_PIN 12
   #define NEOPIXEL_NUM 1

   Adafruit_NeoPixel pixels(NEOPIXEL_NUM, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); // Define NeoPixel

   void setup() {
      //Initialize NeoPixel
      pixels.begin();
      pinMode(NEOPIXEL_PWR, OUTPUT);
      digitalWrite(NEOPIXEL_PWR, HIGH);

      //Initialize RGB LED
      pinMode(RGB_R, OUTPUT);
      pinMode(RGB_G, OUTPUT);
      pinMode(RGB_B, OUTPUT);
   }

   void loop() { 
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(15, 25, 205));
      setColor(15, 25, 205);
      delay(400);

      pixels.show();
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(103, 25, 205));
      setColor(15, 25, 205);
      delay(400);

      pixels.show();
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(233, 242, 205));
      setColor(233, 242, 205);
      delay(400);

      pixels.show();
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(233, 23, 23));
      setColor(233, 23, 23);
      delay(400);

      pixels.show();
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(12, 66, 101));
      setColor(12, 66, 101);
      delay(400);

      pixels.show();
      delay(500);
   }

   //Function to change color of RGB LED
   void setColor(int VAL_GRN, int VAL_RED, int VAL_BLU){
      analogWrite(RGB_R, 255 - VAL_RED);
      analogWrite(RGB_G, 255 - VAL_GRN);
      analogWrite(RGB_B, 255 - VAL_BLU);
   }