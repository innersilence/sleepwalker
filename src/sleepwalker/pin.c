#include "pin.h"

void pin_low(uint8_t pin) {
	PORTD &= ~(1 << pin);
}


void pin_high(uint8_t pin) {
	PORTD |= (1 << pin);
}


void pin_output(uint8_t pin) {
	DDRD |= (1 << pin);
}


void pin_input(uint8_t pin) {
	//DDRD |= (1 << pin);
}


void pin_interrupt_int0(uint8_t pin, pin_interrupt_edge_e type) {
	//PMSK != (1 << pin); // Set pin to be used for external interrupt.
	// Set edge type.
}


void pin_interrupt_int1(uint8_t pin, pin_interrupt_edge_e type) {
	//PMSK != (1 << pin); // Set pin to be used for external interrupt.
	// Set edge type.
}