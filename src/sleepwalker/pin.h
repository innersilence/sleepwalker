#ifndef PIN_H_
#define PIN_H_

#include <stdint.h>
#include <io.h>

void pin_low(uint8_t pin);
void pin_high(uint8_t pin);
void pin_output(uint8_t pin); // Set pin as OUT.

#endif /* PIN_H_ */