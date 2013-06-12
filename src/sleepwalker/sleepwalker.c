#include "sleepwalker.h"

//#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "tsl230.h"


void init_platform() {
   tsl230_init(TSL_S0, TSL_S1, TSL_S2, TSL_S3, TSL_FREQ, TSL_OE, X1, DIV_BY_1);
   sei(); // Enable interrupts and start sampling.
}


uint16_t take_measurement(uint8_t pin) {
	pin_high(pin);
	uint16_t result = tsl230_get();
	pin_low(pin);	
	return result;
}


void send_data(const uint8_t* data, uint16_t size) {
	
}


int main(void) {
   init_platform();
   
   uint16_t values[2] = {0};
   while(1) {
      values[0] = take_measurement(LED_IR_PIN);
      values[1] = take_measurement(LED_RED_PIN);
      send_data((uint8_t*)values, sizeof(values));
      _delay_ms(1000 / POLL_FREQ_HZ);
   }
}


