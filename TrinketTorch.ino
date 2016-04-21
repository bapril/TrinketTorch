/*
 * Copyright 2016 Ben April <bapril@gmail.com> 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LEDPIN 0
#define FANPIN 1
#define LED_COUNT 5
#define COLOR_COUNT 10
#define MAXSTATE 2

long randNumber;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LEDPIN, NEO_GRBW + NEO_KHZ800);

//Color set: 
uint32_t colors[] = {
  strip.Color(200, 20 , 0, 0),
  strip.Color(200, 10 , 0, 0),
  strip.Color(200, 0  , 0, 0),
  strip.Color(155, 5  , 0, 0),
  strip.Color(155, 0  , 0, 0),
  strip.Color(100, 0  , 0, 0),
  strip.Color(50 , 0  , 0, 0),
  strip.Color(25 , 0  , 0, 0),
  strip.Color(0  , 0  , 4, 0),
  strip.Color(5  , 0  , 0, 0),};
  
uint32_t color_black = strip.Color(0, 0, 0, 0);

int current_colors[] = {0,0,0,0,0,0};
int *current_color = current_colors;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  pinMode(LEDPIN, OUTPUT);
  pinMode(FANPIN, OUTPUT);
  
  randomSeed(analogRead(2));
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  flameGen(colors, current_color ,COLOR_COUNT,LED_COUNT);
  digitalWrite(FANPIN,1);
}

void flameGen(uint32_t colors[COLOR_COUNT], int current_color[LED_COUNT], int color_count, int led_count) {
  for(uint16_t i=0; i < (int)random(3); i++){
    int led = random(led_count);
    int new_color = genNewColor(current_color[led]);
    strip.setPixelColor(led, colors[new_color]);  
    current_color[led] = new_color;
  }
  strip.show();
  delay(random(10));
}

int genNewColor(int color) {
  int distance = (int)random(2);
  color += distance;
  if (color > COLOR_COUNT) {
    color = 0;
  }
  return color;
}

