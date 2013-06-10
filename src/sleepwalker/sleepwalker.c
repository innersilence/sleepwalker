#include "sleepwalker.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "pin.h"
#include "tsl230.h"

#define LED_RED_PIN  5
#define LED_IR_PIN   8
#define POLL_FREQ_HZ 50


void init_platform() {
	pin_output(TSL_S0);
	pin_output(TSL_S1);
	pin_output(TSL_S2);
	pin_output(TSL_S3);
	pin_input(TSL_FREQ);
	pin_interrupt_int0(TSL_FREQ, EDGE_BOTH);
	
	tsl230_init(X1, DIV_BY_1);
	
	sei(); // Enable interrupts.	
}


uint16_t take_measurement(uint8_t pin) {
	pin_high(pin);
	uint16_t result = tsl230_read();
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