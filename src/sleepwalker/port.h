#ifndef PORT_H_
#define PORT_H_

#include <stdint.h>

void port_bit_set(uint8_t port, uint8_t pin);
void port_bit_clear(uint8_t port, uint8_t pin);


#endif /* PORT_H_ */