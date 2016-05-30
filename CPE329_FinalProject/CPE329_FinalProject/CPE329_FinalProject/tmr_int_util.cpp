/*
 * tmr_int_util.cpp
 *
 * Created: 5/30/2016 10:36:23 AM
 *  Author: mytch
 */ 

// sets up the inputs, outputs and internal pull-ups 
void initGPIO(){
	// all hall effect sensors are outputs
	DDRB |= (1<<HALLEFFECT1);
	DDRD |= (1<<HALLEFFECT2);
	DDRC |= (1<<HALLEFFECT3);
	
	// turn on internal pull-up for hall effects
	PORTB |= (1<<HALLEFFECT1);
	PORTD |= (1<<HALLEFFECT2);
	PORTC |= (1<<HALLEFFECT3);
	
}

// sets up the timers
void initTimers(){
	// timer1 and timer2 are used in SparkFun library
	
	// timer0 (8bit) 0->255
	TCCR0A = 0x02;		// set timer to CTC mode
	TCCR0B = 0x01;		// set prescaler to 1
	OCR0A = 250;		// overflow set to 250
	TIMSK0 = 0x02;		// timer mask interrupt on OCR0A overflow
	TIFR0 = 0x02;		// set overflow to OCR0A value (250)
}

