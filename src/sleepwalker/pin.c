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