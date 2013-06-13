#ifndef PIN_H_
#define PIN_H_
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

#include <stdint.h>
#include <avr/io.h>

void pin_low(uint8_t pin);
void pin_high(uint8_t pin);

void pin_output(uint8_t pin); // Set pin as OUT.
void pin_input(uint8_t pin); // Set pin as INPUT.

typedef enum {
	EDGE_LOW = 0,
	EDGE_BOTH,
	EDGE_FALLING,
	EDGE_RISING
} pin_interrupt_edge_e;

void pin_interrupt_int0(uint8_t pin, pin_interrupt_edge_e type);
void pin_interrupt_int1(uint8_t pin, pin_interrupt_edge_e type);

#endif /* PIN_H_ */