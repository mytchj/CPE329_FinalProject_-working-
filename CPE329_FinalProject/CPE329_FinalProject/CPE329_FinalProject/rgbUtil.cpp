/* rgbUtil.cpp
 * A set of utilites to drive the TI TLC 5946 RGB Led Driver
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/16/2016
 * Revision: 1.0
 */

#include "rgbUtil.h"

//#define NUM_COLOR_CHANNELS 3
#define NUM_LED_CHANNELS 9
#define DIRECTION 1  // A macro to correct the direction of the cycle, depending on the physical setup
#define TOP_GS 1250

#define BRIGHTNESS_LEVELS 16
#define MAX_BRIGHTNESS 15
#define NUM_SAMPS 5

#define R_ENABLE 1
#define G_ENABLE 1
#define B_ENABLE 1

uint8_t bottomLED = -1;
uint8_t currentLED = -1;

uint32_t lastDeltaT = 0;

uint8_t brightnesslevel = MAX_BRIGHTNESS;
uint16_t brightnessSteps[BRIGHTNESS_LEVELS] = {0, TOP_GS / 15, TOP_GS / 14,
   TOP_GS / 13, TOP_GS / 12, TOP_GS / 11, TOP_GS / 10,
   TOP_GS / 9, TOP_GS / 8, TOP_GS / 7, TOP_GS / 6,
   TOP_GS / 5, TOP_GS / 4, TOP_GS / 3, TOP_GS / 2, TOP_GS};

static uint8_t numColorChannels = R_ENABLE + G_ENABLE + B_ENABLE;
static uint8_t numLeds = NUM_LED_CHANNELS / numColorChannels;

color ambientColor = {0,0,0};
color rearLight = {TOP_GS, 0, 0};


void setLED(int ledNum, color color);
void setAllLEDs(color solid);
void setBrakeBrightness(int deltaT);

int nextSensor(uint8_t sensorNum, uint8_t prevSensorVal);
int prevSensor(uint8_t sensorNum, uint8_t prevSensorVal);

void setAllLEDs(int r, int g, int b) {
   color solid = {r, g, b};
   
   setAllLEDs(solid);
}

void setAllLEDs(color solid) {
   int ndx;			// index
   Tlc.clear();		// clear TLC data
 
   // set every LED the same color
   for (ndx = 0; ndx < numLeds; ndx++)
      setLED(ndx, solid);
   
   Tlc.update();     // send GS data to TLC5940
}

/* Something else determines which LED is on the bottom in main */
void setBottomLED(int LED) {
   bottomLED = LED;
}

void setAmbientColor(int r, int g, int b) {
   ambientColor.r = r;
   ambientColor.g = g;
   ambientColor.b = b;
}

/* Overloading nextLED to take in speed and set the brightness based on it */
void nextLED(uint8_t sensorNum, uint32_t deltaT) {
   setBrakeBrightness(deltaT);
   
   rearLight.r = brightnessSteps[brightnesslevel];
   
   nextLED(sensorNum);
}

void nextLED(uint8_t sensorNum) {
   int ndx;
//   static uint8_t prevSensorNum = -1;
   
//   if (nextSensor(sensorNum, prevSensorNum))
//      if ((++currentLED) >= numLeds)
//         currentLED = 0;
//   else if (prevSensor(sensorNum, prevSensorNum))
//      if ((--currentLED) < 0)
//         currentLED = numLeds - 1;
//   prevSensorNum = sensorNum;
   
   currentLED = ++sensorNum;
   currentLED %= 3;
   
   if (currentLED < 0)
      currentLED = bottomLED; // Definitely subject to change, just a placeholder
   
   Tlc.clear();
   
   for (ndx = 0; ndx < numLeds; ndx++) {
      if (ndx == currentLED)
         setLED(ndx, rearLight);
      else
         setLED(ndx, ambientColor);
   }
   
   Tlc.update();
}

void stopped() {
   int ndx;
   
   brightnesslevel = 15;
   
   Tlc.clear();
   
   for (ndx = 0; ndx < numLeds; ndx++) {
      if (ndx == currentLED)
         setLED(ndx, rearLight);
      else
         setLED(ndx, ambientColor);
   }
  
   Tlc.update();
}

void setBrakeBrightness(int deltaT) {
   
   /*
   // slower
   if(deltaT > lastDeltaT){
	   brightnesslevel = MAX_BRIGHTNESS;
   }
   // faster
   else{
		brightnesslevel = 0;
   }
   */
   
   static uint8_t faster = 0; // To avoid lots of minute adjustments
   static uint8_t slower = 0;
   
   if (lastDeltaT < deltaT) {
	  slower++;
      faster = 0;
   }
   else {
      faster++;
      slower = 0;
   }
   
   if (faster >= NUM_SAMPS) {	// Decreased for testing, normally 10
      faster = 0;
      if (brightnesslevel > 0)
         brightnesslevel--;
   }
   
   if (slower >= NUM_SAMPS) {	// Decreased for testing, normally 10
      slower = 0;
      if (brightnesslevel < MAX_BRIGHTNESS) {
         brightnesslevel++;
      }
   }
   
   lastDeltaT = deltaT;
}

void setLED(int ledNum, color color) {
   int offset = -1;
   ledNum *= numColorChannels;
   
   if (R_ENABLE)
      Tlc.set(ledNum + ++offset, color.r);
   if (G_ENABLE)
      Tlc.set(ledNum + ++offset, color.g);
   if (B_ENABLE)
      Tlc.set(ledNum + ++offset, color.b);
}

int nextSensor(uint8_t sensorNum, uint8_t prevSensorVal) {
   int isNextSensor = 0;
   
   if (prevSensorVal == 2)
      isNextSensor = (sensorNum == 0);
   else
      isNextSensor = (sensorNum > prevSensorVal);
   
   return isNextSensor;
}

int prevSensor(uint8_t sensorNum, uint8_t prevSensorVal) {
   int isPrevSensor = 0;
   
   if (prevSensorVal == 2)
      isPrevSensor = (sensorNum == 2);
   else
      isPrevSensor = (sensorNum < prevSensorVal);
   
   return isPrevSensor;
}
