#include "SparkFun_Tlc5940.h"
#include "rgbUtil.h"
#include "tmr_int_util.h"

int GS = TOP_GS; //0   // LED greyscale
int chan = 0; // LED channel
uint32_t dt_us = 0;

int main(void){
   uint32_t speed = 2200;
   uint8_t increment = 256;
   
	_delay_ms(100);			// startup delay
	
	init();					// initializations for Arduino.h
	//Serial.begin(9600);		// set baud rate for serial com
	Tlc.init();				// initialize the TLC chip
	
	initGPIO();
	initTimers();
	initPCINT();
	sei();
   
	// Turn on full, then fade off
	while(GS >= 0){
		setAllLEDs(GS,0,0);
		GS--;					// increment GS
      
		_delay_ms(GS_DELAY);	// delay GS color
	}
   
	// Temporary idea: Determine the bottom/back LED, send it to rgbUtil so that
	//  it knows which led to cycle to next
	setBottomLED(0);
   
	//Infintely cycle an LED around the loop
	while (1) {
		nextLED(speed);
      
      /* Testing speed change */
      if (speed > 2305 || speed < 256)
         increment *= -1;
      speed -= increment;
      
      /* Test Ambient Colors with fade */
//		setAmbientColor(GS, 0, 0);
//		GS++;
//		GS %= (TOP_GS/16);
      
		_delay_ms(100);
	}
   
	return 0;
}

////////////////////////////////ISR////////////////////////////////////////////

// ISR that holds the time between halleffect readings
// timer0 set to overflow every 100us / 0.1ms
ISR(TIMER0_COMPA_vect){
	dt_us = dt_us + 100;
	
	// if dt_us > 1 second bike is probalby stopped 
	if(dt_us > 1000000){
		// tell rgbUtil that bike is stopped
		
		dt_us = 0;		// reset dt_us
	}
}

// ISR for halleffect1 at pin D8
// enters ISR when set from high (from pull-up) to low
ISR(PCINT0_vect){
	dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us
	
	// send dt_us to rgbUtil
	
	dt_us = 0;		// reset dt_us
}

// ISR for halleffect1 at pin D7
// enters ISR when set from high (from pull-up) to low
ISR(PCINT1_vect){
	dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us
	
	// send dt_us to rgbUtil
	
	dt_us = 0;		// reset dt_us
}

// ISR for halleffect1 at pin A0
// enters ISR when set from high (from pull-up) to low
ISR(PCINT2_vect){
	dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us
	
	// send dt_us to rgbUtil
	
	dt_us = 0;		// reset dt_us
}
