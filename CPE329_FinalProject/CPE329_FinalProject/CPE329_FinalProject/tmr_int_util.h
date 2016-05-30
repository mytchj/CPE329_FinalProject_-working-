/*
 * tmr_int_util.h
 *
 * Created: 5/30/2016 10:37:41 AM
 *  Author: mytch
 */ 


#ifndef TMR_INT_UTIL_H_
#define TMR_INT_UTIL_H_

// GPIO
#define HALLEFFECT1 
#define HALLEFFECT2
#define HALLEFFECT3

// constants 
#define TOP_GS 1250
#define GS_DELAY 5

// standard libraries 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// helper functions
void initGPIO();
void initTimers();


#endif /* TMR_INT_UTIL_H_ */