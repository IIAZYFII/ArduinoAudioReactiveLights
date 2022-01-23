#include <FastLED.h>

#define NUM_LEDS 100
#define LED_PIN 2
#define updateLEDS 3 //The amount of LEDS to update and move every loop

CRGB leds[NUM_LEDS]; 

int const micPin = A0;

int sensorValue = 0;
int highestSensorValue = -1000; //setting the highestSensorValue to an extreme low
int lowestSensorValue = 1000;  //setting the lowestSensorValue to an extreme high
int averageSensorValue = 0;
int lastSensorValue;




void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);

}

void loop() {
  sensorValue = analogRead(micPin);

  if (sensorValue > highestSensorValue) {
      highestSensorValue = sensorValue;
    }
    
  if (sensorValue < lowestSensorValue) {
      lowestSensorValue = sensorValue;
    } 

  averageSensorValue = (sensorValue + lastSensorValue) / 2;

  EVERY_N_MILLISECONDS(50) {
      for(int i = NUM_LEDS -1; i >= updateLEDS; i--) {
          if(i == 50 || i == 51) {
              leds[i] = CRGB::Black; //Turns the led off
            } else if (i > 49) {
              leds[i] = leds[i - updateLEDS]; // moves the leds along the strip from the middle in one direction
            }
        
        }
    
    
    }
  FastLED.show();



  lastSensorValue = sensorValue;


     EVERY_N_MILLISECONDS(50) { //Turns on 6 leds from the middle if below or above specific frequency
      if (sensorValue > (averageSensorValue + 5) || sensorValue < (averageSensorValue - 5)) {
         leds[50] =  CHSV(index, 255, 255);
         leds[51] = CHSV(index, 255, 255);
         leds[52] = CHSV(index, 255, 255);

         leds[48] =  CHSV(index, 255, 255);
         leds[47] = CHSV(index, 255, 255);
         leds[46] = CHSV(index, 255, 255);
    
        
      }
      
     }
      

     
   

}
