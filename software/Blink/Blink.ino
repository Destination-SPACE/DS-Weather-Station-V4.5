/*******************************************************************************
DESTINATION WEATHER STATION V4.5 EXAMPLE - Blink

This is an example sketch for the Destination Weather Station v4.5 in-situ
sensing platform to test the LEDs on the weather station.

modified 2024-03-13
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