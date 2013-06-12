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

