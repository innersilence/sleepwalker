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