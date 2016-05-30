#define TOP_GS 1250
#define GS_DELAY 5

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Arduino.h>      // this is needed to run the SparkFun library
#include "SparkFun_Tlc5940.h"

int GS = 0;   // LED greyscale 
int chan = 0; // LED channel

int main(void){
  init();         // initializations for Arduino.h
  Serial.begin(9600);   // set baud rate for serial com
  Tlc.init();       // initialize the TLC chip
  
  // stuck here forever
  while(1){
    Serial.println(GS);   // print GS data to Serial window (BAUD =9600)
    Tlc.clear();      // clear TLC data
    Tlc.setAll(GS);     // set all TLC channel (15:0) to GS value
    Tlc.update();     // send GS data to TLC5940
    GS++;         // increment GS
    
    // if GS is larger than TOP_GS, reset GS value
    if(GS > TOP_GS)
      GS = 0;
    _delay_ms(GS_DELAY);  // delay GS color
  } 
  return 0;
}
