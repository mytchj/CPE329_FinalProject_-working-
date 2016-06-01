/*
 * tmr_int_util.cpp
 *
 * Created: 5/30/2016 10:36:23 AM
 *  Author: mytch
 */ 

#include "tmr_int_util.h"

// sets up the inputs, outputs and internal pull-ups 
void initGPIO(){
	// all hall effect sensors are inputs
	DDRB &= ~(1<<HALLEFFECT1);
	DDRD &= ~(1<<HALLEFFECT2);
	DDRC &= ~(1<<HALLEFFECT3);
	
	// Debug LED is an output
	PORTD |= (1<<DEBUGLED);
	PORTD &= ~(1<<DEBUGLED);		// initially off
	
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
	TCCR0B = 0x02;		// set pre-scaler to 8
	OCR0A = OCR0A_OVR;	// overflow value 
	TIMSK0 = 0x02;		// timer mask interrupt on OCR0A overflow
	TIFR0 = 0x02;		// set overflow to OCR0A value
}

// sets up all three PCINT vectors for each hall effect sensor
void initPCINT(){
	cli();		// clear interrupts
	
	// enable PCINT (2:0)
	PCICR = 0b00000111;
	
	// PCINT0 -> D8 (halleffect sensor 1)
	PCMSK0 = (1<<HALLEFFECT1);
	// PCINT1 -> A0 (halleffect sensor 3)
	PCMSK1 = (1<<HALLEFFECT3);
	// PCINT2 -> D7 (halleffect sensor 2)
	PCMSK2 = (1<<HALLEFFECT2);
	
	// set the PCINT flag register for all 3 PCINTs
	PCIFR = 0b00000111;
	
	sei();		// set interrupts 
}

