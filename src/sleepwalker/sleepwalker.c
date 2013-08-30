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
   // After reset BT module communicates at 9600 baud, no parity, 8 data and 1 stop bit.
   // Set USART to these settings.
   if (0 != usart0_baud_rate(9600)) 
      blink_error(".");
   
   // Change BT module name to baboom.me.  
   if (0 != hc04_device_name("fingr.baboom.me"))
      blink_error("..");
   
   // Change BT module to 38400.   
   if (0 != hc04_baud_rate(38400))
      blink_error("...");
   
   // Set USART to 38400      
   if (0 != usart0_baud_rate(38400))
      blink_error("....");
      
   while (1) {
      blink_error("-");
      usart0_send_line("red[0000]");
      usart0_send_line("ir[0000]");
      //blink_error("-");
   }     
   
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


