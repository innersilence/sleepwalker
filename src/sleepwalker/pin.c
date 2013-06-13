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

#include "pin.h"
#include "port.h"


void pin_low(uint8_t pin) {
	port_bit_clear(PORTD, pin);
}


void pin_high(uint8_t pin) {
	port_bit_set(PORTD, pin);
}


void pin_output(uint8_t pin) {
	port_bit_set(DDRD, pin);
}


void pin_input(uint8_t pin) {
	port_bit_clear(DDRD, pin);
}


void pin_interrupt0_edge(uint8_t pin, pin_interrupt_edge_e type) {
	switch (type) {
		case EDGE_LOW:
			port_bit_clear(EICRA, ISC00);
			port_bit_clear(EICRA, ISC01);
			break;
		case EDGE_BOTH:
			port_bit_set(EICRA, ISC00);
			port_bit_clear(EICRA, ISC01);
			break;	
		case EDGE_FALLING:
			port_bit_clear(EICRA, ISC00);
			port_bit_set(EICRA, ISC01);	
			break;	
		case EDGE_RISING:
			port_bit_set(EICRA, ISC00);
			port_bit_set(EICRA, ISC01);
		//default:
		//	pribtf();			
	}
}


void pin_interrupt0(uint8_t pin, pin_interrupt_edge_e type) {
	//PMSK != (1 << pin); // Set pin to be used for external interrupt.
	// Set edge type.
	
	// EISRA - controls edge.
	EICRA = _BV(ISC00); // interrupt on both edges
	EIMSK |= _BV(INT0); // enable int0 interrupts
}


void pin_interrupt1_edge(uint8_t pin, pin_interrupt_edge_e type) {
	switch (type) {
		case EDGE_LOW:
		port_bit_clear(EICRA, ISC10);
		port_bit_clear(EICRA, ISC11);
		break;
		case EDGE_BOTH:
		port_bit_set(EICRA, ISC10);
		port_bit_clear(EICRA, ISC11);
		break;
		case EDGE_FALLING:
		port_bit_clear(EICRA, ISC10);
		port_bit_set(EICRA, ISC11);
		break;
		case EDGE_RISING:
		port_bit_set(EICRA, ISC10);
		port_bit_set(EICRA, ISC11);
		//default:
		//	pribtf();
	}
}

void pin_interrupt1(uint8_t pin, pin_interrupt_edge_e type) {
	// Not implemented.
}