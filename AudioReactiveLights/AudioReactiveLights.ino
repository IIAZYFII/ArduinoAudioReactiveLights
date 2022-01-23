#include <FastLED.h>

#define NUM_LEDS 100
#define LED_PIN 2
#define updateLEDS 3 //The amount of LEDS to update and move every loop

CRGB leds[NUM_LEDS]; 

int const micPin = A0;

int sensorValue = 0;
int highestSensorValue = -1000; //setting the highestSensorValue to an extreme low
int lowestSensorValue = 1000;  //setting the lowestSensorValue to an extreme high




void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);

}

void loop() {
  sensorValue = analogRead(micPin);

  if (sensorValue > high) {
      high = sensorValue;
    }
    
  if (sensorValue < low) {
      low = sensorValue;
    } 

}
