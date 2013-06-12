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