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
#include <string.h>
#include <stdio.h>

#include "led.h"
#include "tsl230.h"
#include "usart.h"
#include "hc04.h"
#include "error.h"


char buffer_16_bytes[16];

// http://dronecolony.com/2008/11/13/arduino-and-the-taos-tsl230r-light-sensor-getting-started/



uint32_t led_ir_take_measurement() {
   uint32_t val = 0;
   
   blink();
   
   /*led_ir_on();
   sei(); // Enable interrupts.
   
   tsl230_start();
   while(0 != tsl230_ready()) {}
   val = tsl230_read();
   
   cli(); // Disable interrupts.
   led_ir_off();*/
   
   return val;
}


uint32_t led_red_take_measurement() {
   uint32_t val = 0;
   
   blink();
   
   /*led_red_on();
   sei(); // Enable interrupts.
   
   tsl230_start();
   while(0 != tsl230_ready()) {}
   val = tsl230_read();
   
   cli(); // Disable interrupts.
   led_red_off();*/
   
   return val;
}


int main(void) {  
   blink_init();

   // After reset BT module communicates at 9600 baud, no parity, 8 data and 1 stop bit.
   // Set USART baud rate to 9600.
   if (0 != usart0_baud_rate(BLUETOOTH_MODULE_DEFAULT_BAUD_RATE)) 
      blink_error(".");
   
   // Change BT module name to 'baboom.me'.  
   if (0 != hc04_device_name("baboom.me"))
      blink_error("..");

   // Change BT module baud rate to 38400.   
   if (0 != hc04_baud_rate(BLUETOOTH_MODULE_BAUD_RATE))
      blink_error("...");
        
   // Set USART baud rate to 38400.      
   if (0 != usart0_baud_rate(BLUETOOTH_MODULE_BAUD_RATE))
      blink_error("...."); 
      
   //while (1) {blink(); _delay_ms(100);}
      
   // Setup LED pins.
   led_ir_pin_output();
   led_red_pin_output();

   // Initialize TSL230.
   tsl230_init();
   tsl230_sensitivity(X1);
   tsl230_scaling(DIV_BY_1);
     
   // Start taking measurements.
   uint32_t micro_watts_per_centimeter_squared;
   while(1) {
      micro_watts_per_centimeter_squared = led_ir_take_measurement(); // Take measurement of IR LED.
      sprintf(buffer_16_bytes, " ir[%04lu]", micro_watts_per_centimeter_squared);
      usart0_send_line(buffer_16_bytes);
         
      micro_watts_per_centimeter_squared = led_red_take_measurement(); // Take measurement of red LED.
      sprintf(buffer_16_bytes, "red[%04lu]", micro_watts_per_centimeter_squared);
      usart0_send_line(buffer_16_bytes);
   }  
}


