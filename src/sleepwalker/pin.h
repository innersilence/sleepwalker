#ifndef PIN_H_
#define PIN_H_

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