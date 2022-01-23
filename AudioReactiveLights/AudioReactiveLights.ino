#include <FastLED.h>

#define NUM_LEDS 100
#define LED_PIN 2
#define updateLEDS 3 //The amount of LEDS to update and move every loop

void gridForm(int upper, int lower, int interval);

int const micPin = A0;
int const potPin = A1;

CRGB leds[NUM_LEDS]; 
int hueColours[] = {0, 130, 230, 275, 300}; //hue values for colour pallete
int grid[6]; //Sections that the frequencies fall in

int sensorValue = 0;
int highestSensorValue = -1000; //setting the highestSensorValue to an extreme low
int lowestSensorValue = 1000;  //setting the lowestSensorValue to an extreme high
int averageSensorValue = 0;
int lastSensorValue;
int potValue = 0;




void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);

}

void loop() {
  sensorValue = analogRead(micPin);
  potValue = analogRead(potPin);

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
      for(int i = 0; i <= NUM_LEDS - updateLEDS; i++) {
          if(i < 49) {
              leds[i] = leds[i + updateLEDS];
          }
        }
     FastLED.show();
    }

    gridForm(highestSensorValue, lowestSensorValue, 6); //splits the frequencies into 6 sections
    int index = 0;

    //Selects the colour/hue depending on the sections that the sensorValue falls in
    for(int i = 0; i < 6; i++) {
        if(sensorValue > grid[i] && sensorValue <= grid[i + 1]) {
            index = hueColours[i];
          }
      
      
      }
 
  
     int envelopeBoundary = map(potValue, 0, 1023, 0, 20);
     EVERY_N_MILLISECONDS(50) { //Turns on 6 leds from the middle if below or above specific frequency
      if (sensorValue > (averageSensorValue + envelopeBoundary) || sensorValue < (averageSensorValue - envelopeBoundary)) {
         leds[50] =  CHSV(index, 255, 255);
         leds[51] = CHSV(index, 255, 255);
         leds[52] = CHSV(index, 255, 255);
         
         leds[48] =  CHSV(index, 255, 255);
         leds[47] = CHSV(index, 255, 255);
         leds[46] = CHSV(index, 255, 255);
      }
      FastLED.show();
     }

     
  
  EVERY_N_SECONDS(5) {
      highestSensorValue = (highestSensorValue + averageSensorValue ) / 2; //dynamically changes and rests highestSensorValue
      lowestSensorValue = (lowestSensorValue + averageSensorValue ) / 2;  //dynamically changes and rests lowestSensorValue
    } 



    lastSensorValue = sensorValue;
}

//splits the frequencies into different catergories/bands
void gridForm(int upper, int lower, int interval) {
    int stepSize = (upper-lower) / (interval - 1); 
    for(int i = 0; i < interval; i++) {
        grid[i] = lower + (i * stepSize);
      }
  
  }
