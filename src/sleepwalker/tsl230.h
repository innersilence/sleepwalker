#ifndef TSL230_H_
#define TSL230_H_

#include <stdint.h>

#define TSL_FREQ 2 // Interupt pin.
#define TSL_S0 4 // Sensitivity pin 0.
#define TSL_S1 5 // Sensitivity pin 1.
#define TSL_S2 6 // Scaling pin 0.
#define TSL_S3 7 // Scaling pin 1.
#define TSL_OE 8 // Output Enabled.

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

void tsl230_init(tsl230_sensitivity_e sensitivity, tsl230_scaling_e scaling);
uint16_t tsl230_read(void);
void tsl230_sensitivity(tsl230_sensitivity_e sensitivity);
void tsl230_scaling(tsl230_scaling_e scaling);

#endif /* TSL230_H_ */