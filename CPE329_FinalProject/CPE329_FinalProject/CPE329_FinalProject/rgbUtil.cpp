/* rgbUtil.cpp
 * A set of utilites to drive the TI TLC 5946 RGB Led Driver
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/16/2016
 * Revision: 1.0
 */

#include "rgbUtil.h"

//#define NUM_COLOR_CHANNELS 3
#define NUM_LED_CHANNELS 16
#define DIRECTION 1  // A macro to correct the direction of the cycle, depending on the physical setup
#define TOP_GS 1250

#define R_ENABLE 1
#define G_ENABLE 1
#define B_ENABLE 1

uint8_t bottomLED = -1;
uint8_t currentLED = -1;

static uint8_t numColorChannels = R_ENABLE + G_ENABLE + B_ENABLE;
static uint8_t numLeds = NUM_LED_CHANNELS / numColorChannels;

color ambientColor = {0,0,0};
color rearLight = {TOP_GS, 0, 0};


void setLED(int ledNum, color color);
void setAllLEDs(color solid);

void setAllLEDs(int r, int g, int b) {
   color solid = {r, g, b};
   
   setAllLEDs(solid);
}

void setAllLEDs(color solid) {
   int ndx;
   Serial.println(solid.r);   // print GS data to Serial window (BAUD =9600)
   Tlc.clear();      // clear TLC data
   //   Tlc.setAll(r);     // set all TLC channel (15:0) to GS value
   
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

void nextLED() {
   int ndx;
   
   if (currentLED < 0)
      currentLED = bottomLED; // Definitely subject to change, just a placeholder
   
   Serial.println(TOP_GS);
   Tlc.clear();
   
   for (ndx = 0; ndx < numLeds; ndx++) {
      if (ndx == currentLED)
         setLED(ndx, rearLight);
      else
         setLED(ndx, ambientColor);
   }
   
   Tlc.update();
   
   currentLED++;
   currentLED %= numLeds;
}

void stopped() {
   int ndx;
   
   Tlc.clear();
   
   for (ndx = 0; ndx < numLeds; ndx++) {
      if (ndx == currentLED)
         setLED(ndx, rearLight);
      else
         setLED(ndx, ambientColor.);
   }
   
   Tlc.update();
}

void setLED(int ledNum, color color) {
   int offset = -1;
   ledNum *= numLeds;
   
   if (R_ENABLE)
      Tlc.set(ledNum + ++offset, color.r);
   if (G_ENABLE)
      Tlc.set(ledNum + ++offset, color.g);
   if (B_ENABLE)
      Tlc.set(ledNum + ++offset, color.b);
}