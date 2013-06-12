#include <avr/sfr_defs.h>
#include "port.h"

void port_bit_set(uint8_t port, uint8_t pin) {
	port |= _BV(pin);
}

void port_bit_clear(uint8_t port, uint8_t pin) {
	port &= ~_BV(pin);
}
