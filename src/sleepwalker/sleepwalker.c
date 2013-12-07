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


void test_connection();

uint32_t led_ir_take_measurement() {  
   tsl230_start();
   
   while (0 != tsl230_ready()) {
   }
   
   tsl230_stop();
   uint32_t val = tsl230_read();      
   
   return val;
}


// To reset BT module set pin 11 (pin 5 on shield to 'low').
int main(void) {      
   hc04_init(); // Initialize Bluetooth HC-06 module.     
   tsl230_init(); // Initialize TSL230.
   
   tsl230_sensitivity(X1);
   tsl230_scaling(DIV_BY_1);
   
   // Start taking measurements.
   while(1) {
      uint32_t micro_watts_per_centimeter_squared = led_ir_take_measurement() / 4; // Take measurement of IR LED.
      if (micro_watts_per_centimeter_squared > 1000)
         micro_watts_per_centimeter_squared = 1000;
      sprintf(buffer_16_bytes, "1 %"PRIu32"\n", micro_watts_per_centimeter_squared);
      //sprintf(buffer_16_bytes, "1 %08lu\n", micro_watts_per_centimeter_squared);
      usart0_send_line(buffer_16_bytes);
   }
}

//void test_connection() {
   //while (1) {
      //usart0_send_line("-ok");
      //blink();
      //_delay_ms(1000);
   //}
//}


//uint32_t led_red_take_measurement() {
//led_red_on();
//
//tsl230_start();
//uint32_t while(0 != tsl230_ready()) {}
//val = tsl230_read();
//led_red_off();
//
//return val;
//}


       
       // Setup LED pins.
       //led_ir_pin_output();
       //led_red_pin_output();


      //micro_watts_per_centimeter_squared = led_red_take_measurement(); // Take measurement of red LED.
      //sprintf(buffer_16_bytes, "red[%04lu]", micro_watts_per_centimeter_squared);
      //usart0_send_line(buffer_16_bytes);


/*

// http://dronecolony.com/2008/11/13/arduino-and-the-taos-tsl230r-light-sensor-getting-started/

// IR LED 1.4-1.5V @ 20mA
// Red LED 2.0-2.4V @ 50mA


. When programming wait for charging light to go off, or serial won't work.
. When open port with HTerm use \\.\COM4 syntax.
. After reprogramming need to remove device and pair again.
. Powering IR LED. Current must be around 20mA, I = V/R -> 3.3V/0.020A =~ 165Ohm. Voltage on led must ve around 1.4-1.5V
   3.3/1.5 = (165 + x) / x
   3.3 * x = 1.5 * (165 + x)
   3.3x = 1.5x + 247.5
   1.8x = 247.5
   x = 138Ohm
   Two resistors 165 & 138 Ohms led connected in between and to the ground, current = 20mA, voltage = 1.5V
*/