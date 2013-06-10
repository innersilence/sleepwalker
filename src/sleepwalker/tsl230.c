#include "tsl230.h"
#include "pin.h"



uint16_t tsl230_read(void) {
	return 58;
}


void tsl230_sensitivity(tsl230_sensitivity_e sensitivity) {
	switch (sensitivity) {
		case POWER_DOWN:
			pin_low(TSL_S0);
			pin_low(TSL_S1);
			return;
		case X1:
			pin_high(TSL_S0);
			pin_low(TSL_S1);
			return;
		case X10:
			pin_low(TSL_S0);
			pin_high(TSL_S1);
			return;
		case X100:
			pin_high(TSL_S0);
			pin_high(TSL_S1);
			return;
		//default:
			//printf("TLS230: incorrect sensitivity value: %d\n", sensitivity);
	}
}
	

void tsl230_scaling(tsl230_scaling_e scaling) {
	switch (scaling) {
		case DIV_BY_1:
			pin_low(TSL_S2);
			pin_low(TSL_S3);
			return;
		case DIV_BY_2:
			pin_high(TSL_S2);
			pin_low(TSL_S3);
			return;
		case DIV_BY_10:
			pin_low(TSL_S2);
			pin_high(TSL_S3);
			return;		
		case DIV_BY_100:
			pin_high(TSL_S2);
			pin_high(TSL_S3);
			return;		
		//default:
		//	printf("TLS230: incorrect scaling value: %d\n", scaling);
	}
}


void tsl230_init(tsl230_sensitivity_e sensitivity, tsl230_scaling_e scaling) {
	tsl230_sensitivity(sensitivity);
	tsl230_scaling(scaling);
}
