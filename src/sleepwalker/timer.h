#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include "pin.h"

void timer0_init(uint16_t initial_vaue);
void timer0_set_capture_edge(pin_interrupt_edge_e edge);
void timer0_enable_input_capture();
void timer0_enable_overflow_interrupt();

void timer1_init(uint16_t initial_vaue);
void timer1_set_capture_edge(pin_interrupt_edge_e edge);
void timer1_enable_input_capture();
void timer1_enable_overflow_interrupt();
uint16_t timer1_get();

#endif /* TIMER_H_ */

