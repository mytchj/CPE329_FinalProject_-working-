#include "SparkFun_Tlc5940.h"
#include "rgbUtil.h"
#include "tmr_int_util.h"

int GS = TOP_GS; //0   // LED greyscale
int chan = 0; // LED channel
uint32_t dt = 0;

int main(void){
	_delay_ms(100);			// startup delay
	
	init();					// initializations for Arduino.h
	//Serial.begin(9600);		// set baud rate for serial com
	Tlc.init();				// initialize the TLC chip
	
	initGPIO();
	initTimers();
	//initPCINT();
	//sei();
   
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
		nextLED();
		setAmbientColor(GS, 0, 0);
		GS++;
		GS %= (TOP_GS/16);
		_delay_ms(100);
	}
   
	return 0;
}


ISR(TIMER0_COMPA_vect){
	dt = dt + 100;
}

// ISR for halleffect1 at pin D8
// enters ISR when set from high (from pull-up) to low
ISR(PCINT0_vect){
	
}

// ISR for halleffect1 at pin D7
// enters ISR when set from high (from pull-up) to low
ISR(PCINT1_vect){
	
}

// ISR for halleffect1 at pin A0
// enters ISR when set from high (from pull-up) to low
ISR(PCINT2_vect){
	
}
