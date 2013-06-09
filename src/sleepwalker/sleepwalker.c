#include <avr/io.h>

#include "pin.h"
#include "tsl230.h"

#define LED_RED_PIN  5
#define LED_IR_PIN   8
#define POLL_FREQ_HZ 50


uint16_t take_measurement(uint8_t pin) {
	pin_high(pin);
	uint16_t result = tsl230_read();
	pin_low(pin);
	
	return result;
}



void send_data(const uint8_t* data, ) {
	
}


int main(void) {
	tsl230_init();
	
	uint16_t values[2] = {0};
    while(1) {
        value[0] = take_measurement(LED_IR_PIN); 
		value[1] = take_measurement(LED_RED_PIN);
		send_data(values, sizeof(values));
		_delay_ms(1000 / POLL_FREQ_HZ);
    }
}