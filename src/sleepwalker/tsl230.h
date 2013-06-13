/*
The MIT License (MIT)

Copyright (c) 2013 Dmitry Mukhin <dmukhin.work@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef TSL230_H_
#define TSL230_H_

#include <stdint.h>

typedef enum {
	POWER_DOWN = 0,
	X1,
	X10,
	X100
} tsl230_sensitivity_e;

typedef enum {
	DIV_BY_1 = 0,
	DIV_BY_2,
	DIV_BY_10,
	DIV_BY_100
} tsl230_scaling_e;


void tsl230_init(uint8_t s0_pin, uint8_t s1_pin, uint8_t s2_pin, uint8_t s3_pin, uint8_t freq_pin, uint8_t oe_pin, tsl230_sensitivity_e sensitivity, tsl230_scaling_e scaling);
uint16_t tsl230_get();
void tsl230_sensitivity(uint8_t s0_pin, uint8_t s1_pin, tsl230_sensitivity_e sensitivity);
void tsl230_scaling(uint8_t s2_pin, uint8_t s3_pin, tsl230_scaling_e scaling);

#endif /* TSL230_H_ */