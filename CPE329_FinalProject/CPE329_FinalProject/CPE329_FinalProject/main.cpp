#include "SparkFun_Tlc5940.h"
#include "rgbUtil.h"
#include "tmr_int_util.h"

uint32_t dt_us = 0;			// time between sensor readings

uint8_t foobar = 0;

int main(void){
   _delay_ms(100);			// startup delay
	
	init();					// initializations for Arduino.h
	Tlc.init();				// initialize the TLC chip
	initGPIO();				// initialize GPIO and pull-ups
	_delay_ms(100);			// GPIO stability delay
	initTimers();			// initialize timer0 (CTC, T~100us)
	initPCINT();			// initialize pin change interrupts (2:0)
   
	// Temporary idea: Determine the bottom/back LED, send it to rgbUtil so that
	//  it knows which led to cycle to next
	setBottomLED(0);
	setAmbientColor(0, 0, 0 );
	
	Serial.begin(9600);
   
	//Infinitely cycle an LED around the loop
	while (1) {
      if (dt_us > 1000000)
         stopped()
	}
	return 0;
}


////////////////////////////////ISR////////////////////////////////////////////

// ISR that holds the time between hall effect readings
// timer0 set to overflow every 100us / 0.1ms
ISR(TIMER0_COMPA_vect){
	dt_us = dt_us + 100;
	
	PORTD ^= (1<<DEBUGLED);
}

// ISR for halleffect1 at pin D8
// enters ISR when set from high (from pull-up) to low
ISR(PCINT0_vect){
	if(foobar){
		//cli();						// disable interrupts
		dt_us = dt_us + TCNT0;	// add remaining TCNT time to dt_us
		nextLED(2, dt_us);			// send dt_us to rgbUtil
	
		Serial.println("time reading in ms is:");
		Serial.println((dt_us));
	
		dt_us = 0;					// reset dt_us
		foobar = 0;
		//sei();						// enable interrupts
	}
	else foobar = 1;
}

// ISR for halleffect1 at pin D7
// enters ISR when set from high (from pull-up) to low
ISR(PCINT1_vect){
	if(foobar){
		//cli();						// disable interrupts 
		dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us	
		nextLED(0, dt_us);			// send dt_us to rgbUtil	
	
		Serial.println("time reading in ms is:");
		Serial.println((dt_us));
	
		dt_us = 0;					// reset dt_us	
		foobar = 0;
		//sei();						// enable interrupts 
	}
	else
		foobar = 1;
}

// ISR for halleffect1 at pin A0
// enters ISR when set from high (from pull-up) to low
ISR(PCINT2_vect){
	//cli();	
	if(foobar){					// disable interrupts
		PORTD ^= (1<<DEBUGLED);		// turn debug LED on
		dt_us = dt_us + TCNT0;		// add remaining TCNT time to dt_us
		nextLED(1, dt_us);			// send dt_us to rgbUtil
	
		Serial.println("time reading in ms is:");
		Serial.println((dt_us));
	
		dt_us = 0;					// reset dt_us
		foobar = 0;
	}
	else
		foobar = 1;
	//sei();						// enable interrupts 
}
