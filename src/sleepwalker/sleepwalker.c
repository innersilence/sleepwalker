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

#include <util/delay.h>
#include <avr/interrupt.h>

#include "led.h"
#include "tsl230.h"
#include "usart.h"
#include "hc04.h"
#include "error.h"


int main(void) {  
   usart0_init(9600);
   
   sei();
   
   if (0 > hc04_at_command("NAME", "baboom.me")) // Test communication with BT module by changing its name.
      error_hc04_command_failed();       
   
   /*usart0_init(38400);
     
   if (0 >  hc04_at_command("BAUD", "6")) // Try to set baud rate to 34000
      usart0_init(9600); // Failed. Use defaults (9600 baud to communicate with BT module)
    
   if (0 <  hc04_at_command("BAUD", "6")) // Set baud rate to 38400.
      usart0_init(38400); // Configure USART to use 38400 too.
      
   if (0 > hc04_at_command("NAME", "baboom.me")) { // Test communication with BT module by changing its name.
      error_hc04_command_failed(); // Never exits, blinks diagnostics.
   }*/      
      
   
   
   /*led_ir_pin_output();
   led_red_pin_output();

   tsl230_init();
   tsl230_sensitivity(X1);
   tsl230_scaling(DIV_BY_1);
   
   //sei();
   
   uint16_t values[2] = {0};
   while(1) {
      // Measure IR LED.
      led_ir_on();
      tsl230_start();
      while(0 != tsl230_ready()) {}
      values[0] = tsl230_read();
      led_ir_off();
      
      // Measure red LED.
      led_red_on();
      tsl230_start();
      while(0 != tsl230_ready()) {}
      values[1] = tsl230_read();
      led_red_off();
      
      // Send measurements to collector.
      usart0_write((uint8_t*)values, sizeof(values));
      _delay_ms(1000 / POLL_FREQ_HZ);
   }*/      
}
