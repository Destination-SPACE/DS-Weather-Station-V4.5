#include <Adafruit_NeoPixel.h>

#define RGB_R 17
#define RGB_G 16
#define RGB_B 25
#define NEOPIXEL_PWR 11
#define NEOPIXEL_PIN 12
#define NEOPIXEL_NUM 1

Adafruit_NeoPixel pixels(NEOPIXEL_NUM, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pinMode(NEOPIXEL_PWR, OUTPUT);
  digitalWrite(NEOPIXEL_PWR, HIGH);

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

void setColor(int VAL_GRN, int VAL_RED, int VAL_BLU){
  analogWrite(RGB_R, 255 - VAL_RED);
  analogWrite(RGB_G, 255 - VAL_GRN);
  analogWrite(RGB_B, 255 - VAL_BLU);
}