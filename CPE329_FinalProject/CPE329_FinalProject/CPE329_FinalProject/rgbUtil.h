/* rgbUtil.h
 * A set of utilites to drive the TI TLC 5946 RGB Led Driver
 * Authors : Mytch Johnson & Erik Miller
 * Class: CPE 329-07 w/ Dr. Oliver
 * Date: 5/16/2016
 * Revision: 1.0
 */

#ifndef rgbUtil_h
#define rgbUtil_h

#include <stdio.h>
#include <Arduino.h>      // this is needed to run the SparkFun library
#include "SparkFun_Tlc5940.h"

// struct for color spectrum red, green, and blue color
typedef struct color{
   uint16_t r;
   uint16_t g;
   uint16_t b;
} color;

/* Sets the ambient color of the wheel to ambient */
void setAmbientColor(int r, int g, int b);



#endif /* rgbUtil_h */
