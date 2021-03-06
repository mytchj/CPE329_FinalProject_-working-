/*
 * tmr_int_util.h
 *
 * Created: 5/30/2016 10:37:41 AM
 *  Author: mytch
 */ 


#ifndef TMR_INT_UTIL_H_
#define TMR_INT_UTIL_H_

// GPIO
#define HALLEFFECT1 PB0		// digital pin D8
#define HALLEFFECT2 PD7		// digital pin D7
#define HALLEFFECT3 PC0		// analog pin A0
#define DEBUGLED PD4		// digital pin D2

// constants 
#define TOP_GS 1250			// highest noticeable GS value
#define OCR0A_OVR 200		// timer0 overflow value
#define STOP_TIME 100000	// 1 second in us

// standard libraries 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// helper functions
void initGPIO();
void initTimers();
void initPCINT();


#endif /* TMR_INT_UTIL_H_ */