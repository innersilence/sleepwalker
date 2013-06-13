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

#include <avr/interrupt.h>
#include <util/delay.h>

#include "pin.h"
#include "timer.h"
#include "tsl230.h"



extern volatile uint16_t timer1_overflow_counter;

volatile uint16_t timer1_rising_capture;
volatile uint16_t timer1_falling_capture;
uint8_t tsl230_ready_to_read;


uint16_t tsl230_get(uint16_t wait_poll_interval_millisec) {
   while (!tsl230_ready_to_read) {
       _delay_ms(50);
   }

	return timer1_get();
}


void tsl230_sensitivity(uint8_t s0_pin, uint8_t s1_pin, tsl230_sensitivity_e sensitivity) {
	switch (sensitivity) {
		case POWER_DOWN:
			pin_low(s0_pin);
			pin_low(s1_pin);
			return;
		case X1:
			pin_high(s0_pin);
			pin_low(s1_pin);
			return;
		case X10:
			pin_low(s0_pin);
			pin_high(s1_pin);
			return;
		case X100:
			pin_high(s0_pin);
			pin_high(s1_pin);
			return;
		//default:
			//printf("TLS230: incorrect sensitivity value: %d\n", sensitivity);
	}
}
	

void tsl230_scaling(uint8_t s2_pin, uint8_t s3_pin, tsl230_scaling_e scaling) {
	switch (scaling) {
		case DIV_BY_1:
			pin_low(s2_pin);
			pin_low(s3_pin);
			return;
		case DIV_BY_2:
			pin_high(s2_pin);
			pin_low(s3_pin);
			return;
		case DIV_BY_10:
			pin_low(s2_pin);
			pin_high(s3_pin);
			return;		
		case DIV_BY_100:
			pin_high(s2_pin);
			pin_high(s3_pin);
			return;		
		//default:
		//	printf("TLS230: incorrect scaling value: %d\n", scaling);
	}
}


void tsl230_init(uint8_t s0_pin, uint8_t s1_pin, uint8_t s2_pin, uint8_t s3_pin, uint8_t freq_pin, uint8_t oe_pin, tsl230_sensitivity_e sensitivity, tsl230_scaling_e scaling) {
	pin_output(s0_pin);
	pin_output(s1_pin);
	pin_output(s2_pin);
	pin_output(s3_pin);
	pin_input(freq_pin);
			
	tsl230_sensitivity(s0_pin, s1_pin, sensitivity);
	tsl230_scaling(s2_pin, s3_pin, scaling);
	
	//pin_interrupt_int0(freq_pin, EDGE_BOTH);
}


ISR(TIMER1_CAPT_vect)
{
   // Timer set up to interrupt on rising edge first.
   timer1_rising_capture = ICR1;
}


ISR(TIMER1_OVF_vect)
{
   timer1_overflow_counter ++;
}


