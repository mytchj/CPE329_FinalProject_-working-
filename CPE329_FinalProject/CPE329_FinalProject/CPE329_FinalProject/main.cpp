#include "SparkFun_Tlc5940.h"
#include "rgbUtil.h"
#include "tmr_int_util.h"

int GS = TOP_GS; //0   // LED greyscale
int chan = 0; // LED channel
uint32_t dt_us = 0;

int main(void){
   uint32_t speed = 999999;
   uint32_t increment = 256;
   
	_delay_ms(100);			// startup delay
	
	init();					// initializations for Arduino.h
	Tlc.init();				// initialize the TLC chip
	initGPIO();				// initialize GPIO and pull-ups
	_delay_ms(100);			// GPIO stability delay
	initTimers();			// initialize timer0 (CTC, T~100us)
	initPCINT();			// initialize pin change interrupts (2:0)
	sei();					// set interrupts
   
	//// Turn on full, then fade off
	//while(GS >= 0){
		//setAllLEDs(GS,0,0);
		//GS--;					// increment GS
      //
		//_delay_ms(GS_DELAY);	// delay GS color
	//}
   
	// Temporary idea: Determine the bottom/back LED, send it to rgbUtil so that
	//  it knows which led to cycle to next
	setBottomLED(0);
	setAmbientColor(0, 0, TOP_GS/15);
   
	//Infintely cycle an LED around the loop
	while (1) {
		nextLED(speed);
      
      /* Testing speed change */
      //if (speed > 10000 || speed < 256)
      if(speed > 0)
	    speed--;
		// increment *= -1;
      //speed += increment;
      
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
	cli();
	
	dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us
	
	// send dt_us to rgbUtil
	
	dt_us = 0;		// reset dt_us
	
	sei();
}

// ISR for halleffect1 at pin D7
// enters ISR when set from high (from pull-up) to low
ISR(PCINT1_vect){
	cli();
	
	dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us
	
	// send dt_us to rgbUtil
	
	dt_us = 0;		// reset dt_us
	
	sei();
}

// ISR for halleffect1 at pin A0
// enters ISR when set from high (from pull-up) to low
ISR(PCINT2_vect){
	cli();
	
	dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us
	
	// send dt_us to rgbUtil
	
	dt_us = 0;		// reset dt_us
	
	sei();
}
