/*
The MIT License (MIT)

Copyright (c) 2013 Dmitry Mukhin <dmukhin.work@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "sleepwalker.h"

#include <util/delay.h>
#include <avr/interrupt.h>

#include "pin.h"
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
