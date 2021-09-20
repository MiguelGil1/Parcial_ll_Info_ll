#include <Adafruit_NeoPixel.h>
#define LED_PIN 2
#define LED_COUNT 200

Adafruit_NeoPixel leds(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// C++ code
//
void setup(){
  leds.begin();
  for(int i = 0; i < LED_COUNT; i+=17){
    leds.setPixelColor(i,20,0,255);    
  }
  //leds.setPixelColor(17,20,0,255);
  leds.show();
}

void loop(){
}