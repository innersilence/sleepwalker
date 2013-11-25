/*
The MIT License (MIT)

Copyright (c) 2013 Dmitry Mukhin <zxorro@gmail.com>

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

#include "tsl230.h"


volatile uint16_t timer1_overflow_counter = 0;
volatile uint16_t timer1_rising_capture = 0;
volatile uint16_t timer1_falling_capture = 0;
volatile lsl230_interrupt_edge_e timer1_edge = 0;


void tls230_timer1_disable(void);
void tls230_timer1_init(void);
void tls230_timer1_enable(void);
void tsl230_capture_raising_edge(void);


void tsl230_start(void) {
   timer1_overflow_counter = 0;
   timer1_rising_capture = 0;
   timer1_falling_capture = 0;
   timer1_edge = EDGE_RISING;
   
   tls230_timer1_init();
   tls230_timer1_enable();
   tsl230_capture_raising_edge();
   
   sei(); // Enable interrupts.
}

void tsl230_stop(void) {
   cli(); // Disable interrupts.
}

// When a capture is triggered, the 16-bit value of the counter (TCNT1) is written to the Input Capture Register (ICR1) (p.120)
uint32_t tsl230_read(void) {
   uint32_t result = timer1_overflow_counter * INT16_MAX + timer1_rising_capture + timer1_falling_capture;
   return result;
}

short tsl230_ready(void) {
   return EDGE_DONE - timer1_edge;
}

void tsl230_capture_falling_edge(void) {
   TCCR1B &= ~_BV(ICES1);
}

void tsl230_capture_raising_edge(void) {
   TCCR1B |= _BV(ICES1);
}

// http://www.embedds.com/programming-16-bit-timer-on-atmega328/
ISR(TIMER1_CAPT_vect) { // Timer interrupt vector.
   if (timer1_edge == EDGE_RISING) {
      timer1_rising_capture = ICR1;
      tsl230_capture_falling_edge();
   } else if (timer1_edge == EDGE_FALLING) {
      timer1_falling_capture = ICR1;
      tls230_timer1_disable();
   }

   timer1_edge ++;
}

ISR(TIMER1_OVF_vect) {
   timer1_overflow_counter ++;
}

// TCCR1A, TCCR1B, ICRH1H, ICR1L
// http://www.embedds.com/programming-16-bit-timer-on-atmega328/
void tls230_timer1_init(void) {
   TCNT1 = 0; // Initial value.
   TCCR1B |= _BV(ICES1); // First capture on rising edge.
   TCCR1B |= _BV(CS10); // Start timer without prescaler.
}

void tls230_timer1_enable(void) {
   TIMSK1 |= _BV(ICIE1); // Enable Input Capture Interrupt. (p.139)
   TIMSK1 |= _BV(TOIE1); // Enable overflow (p.139)
   
   TIFR1 |= _BV(ICF1); // Event Capture enabled on ICP1 pin. (p.140)
   TIFR1 |= _BV(TOV1); // ??
}

void tls230_timer1_disable(void) {
   TIMSK1 &= ~_BV(ICIE1); // Enable Input Capture Interrupt. (p.139)
   TIMSK1 &= ~_BV(TOIE1); // Enable overflow (p.139)
   
   TIFR1 &= ~_BV(ICF1); // Event Capture enabled on ICP1 pin. (p.140)
   TIFR1 &= ~_BV(TOV1); // ??
}

// TLS230 S0, S1, S2, S3 pins (PD.4, PD.5, PD.6 and PD.7)
void tsl230_s0_pin_output() {
   DDRD |= _BV(PORTD4);
}

void tsl230_s0_low() {
   PORTD &= ~_BV(PORTD4);
}

void tsl230_s0_high() {
   PORTD |= _BV(PORTD4);
}

void tsl230_s1_pin_output() {
   DDRD |= _BV(PORTD5);
}

void tsl230_s1_low() {
   PORTD &= ~_BV(PORTD5);
}

void tsl230_s1_high() {
   PORTD |= _BV(PORTD5);
}

void tsl230_s2_pin_output() {
   DDRD |= _BV(PORTD6);
}

void tsl230_s2_low() {
   PORTD &= ~_BV(PORTD6);
}

void tsl230_s2_high() {
   PORTD |= _BV(PORTD6);
}

void tsl230_s3_pin_output() {
   DDRD |= _BV(PORTD7);
}

void tsl230_s3_low() {
   PORTD &= ~_BV(PORTD7);
}

void tsl230_s3_high() {
   PORTD |= _BV(PORTD7);
}

// TSL230 Output Enable pin (PB.1)
void tsl230_oe_pin_output() {
   DDRB |= _BV(PORTB1);
}

void tsl230_oe_low() {
   PORTB &= ~_BV(PORTB1);
}

void tsl230_oe_high() {
   PORTB |= _BV(PORTB1);
}

void tsl230_init(void) {     
  tsl230_s0_pin_output();
  tsl230_s1_pin_output();
  tsl230_s2_pin_output();
  tsl230_s3_pin_output();
  tsl230_oe_pin_output();
  
  tls230_timer1_init();
  tls230_timer1_enable();
}

void tsl230_sensitivity(tsl230_sensitivity_e sensitivity) {
   switch (sensitivity) {
      case POWER_DOWN:
         tsl230_s0_low();
         tsl230_s1_low();
         return;
      case X1:
          tsl230_s0_high();
          tsl230_s1_low();
         return;
      case X10:
         tsl230_s0_low();
         tsl230_s1_high();
         return;
      case X100:
         tsl230_s0_high();
         tsl230_s1_high();
         return;
   }
}

void tsl230_scaling(tsl230_scaling_e scaling) {
   switch (scaling) {
      case DIV_BY_1:
         tsl230_s2_low();
         tsl230_s3_low();
         return;
      case DIV_BY_2:
         tsl230_s2_high();
         tsl230_s3_low();
         return;
      case DIV_BY_10:
         tsl230_s2_low();
         tsl230_s3_high();
         return;
      case DIV_BY_100:
         tsl230_s2_high();
         tsl230_s3_high();
         return;
   }
}


