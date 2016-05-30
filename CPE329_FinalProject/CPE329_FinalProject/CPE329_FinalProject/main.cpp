#include "SparkFun_Tlc5940.h"
#include "rgbUtil.h"
#include "tmr_int_util.h"

int GS = TOP_GS; //0   // LED greyscale
int chan = 0; // LED channel

int main(void){
  init();         // initializations for Arduino.h
  Serial.begin(9600);   // set baud rate for serial com
  Tlc.init();       // initialize the TLC chip
   
   // Turn on full, then fade off
   while(GS >= 0){
	  setAllLEDs(GS,0,0);
      GS--;         // increment GS
      
      _delay_ms(GS_DELAY);  // delay GS color
   }
   
   // Temporary idea: Determine the bottom/back LED, send it to rgbUtil so that
   //  it knows which led to cycle to next
   setBottomLED(0);
   
   //Infintely cycle an LED around the loop
   while (1) {
      nextLED();
      setAmbientColor(GS, 0, 0);
      GS++;
      GS %= TOP_GS/2;
   }
   
  return 0;
}
