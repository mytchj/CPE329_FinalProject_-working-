/* rgbUtil.cpp
 * A set of utilites to drive the TI TLC 5946 RGB Led Driver
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/16/2016
 * Revision: 1.0
 */

#include "rgbUtil.h"

#define NUM_COLOR_CHANNELS 1
#define NUM_LED_CHANNELS 16
#define DIRECTION 1  // A macro to correct the direction of the cycle, depending on the physical setup
#define TOP_GS 1250

int bottomLED = -1;
int currentLED = -1;

void setAllLEDs(int gs) {
   Serial.println(gs);   // print GS data to Serial window (BAUD =9600)
   Tlc.clear();      // clear TLC data
   Tlc.setAll(gs);     // set all TLC channel (15:0) to GS value
   Tlc.update();     // send GS data to TLC5940
}

/* Something else determines which LED is on the bottom in main */
void setBottomLED(int LED) {
   bottomLED = LED;
}

void nextLED() {
   if (currentLED < 0)
      currentLED = bottomLED; // Definitely subject to change, just a placeholder
   
   Serial.println(TOP_GS);
   Tlc.clear();
   Tlc.set(currentLED, TOP_GS);
   Tlc.update();
   
   currentLED += DIRECTION * NUM_COLOR_CHANNELS;
   currentLED %= NUM_LED_CHANNELS;
}