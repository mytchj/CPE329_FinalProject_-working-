#define TOP_GS 1250
#define GS_DELAY 5

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "rgbUtil.h"

int GS = TOP_GS; //0   // LED greyscale
int chan = 0; // LED channel

int main(void){
  init();         // initializations for Arduino.h
  Serial.begin(9600);   // set baud rate for serial com
  Tlc.init();       // initialize the TLC chip
  
//  // stuck here forever
//  while(1){
//     setAllLEDs(GS);
//     GS++;         // increment GS
//    
//    // if GS is larger than TOP_GS, reset GS value
//    if(GS > TOP_GS)
//      GS = 0;
//    _delay_ms(GS_DELAY);  // delay GS color
//  }
   
   // Turn on full, then fade off
   while(GS >= 0){
      setAllLEDs(GS);
      GS--;         // increment GS
      
      _delay_ms(GS_DELAY);  // delay GS color
   }
   
   // Temporary idea: Determine the bottom/back LED, send it to rgbUtil so that
   //  it knows which led to cycle to next
   setBottomLED(0);
   
   //Infintely cycle an LED around the loop
   while (1) {
      nextLED();
   }
   
  return 0;
}
