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

#include "timer.h"
#include "port.h"

volatile uint16_t timer1_overflow_counter;


void timer1_init(uint16_t initial_vaue) {

}


void timer1_set_capture_edge(pin_interrupt_edge_e edge) {
   switch (edge) {
      case EDGE_BOTH:
         // Not implemented.
         break;
      case EDGE_FALLING:
         port_bit_clear(TCCR1B, ICES1);
         break;
      case EDGE_LOW:
         // Not implemented.
         break;
      case EDGE_RISING:
         port_bit_set(TCCR1B, ICES1);
         break;
   }
}


void timer1_enable_input_capture() {
   port_bit_set(TIMSK1, ICIE1);
}


void timer1_enable_overflow_interrupt() {
   port_bit_set(TIMSK1, TOIE1);
}


uint16_t timer1_get() {
   return 58;
}

