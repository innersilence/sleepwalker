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

#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

#include "hc04.h"
#include "usart.h"
#include "error.h"


void hc04_reset_pin_output(void) {
   DDRB |= _BV(PORTB2);
}


void hc04_reset_high(void) {
   PORTB |= _BV(PORTB2);
}


void hc04_reset_low(void) {
   PORTB &= ~_BV(PORTB2);
}


void hc04_reset() {
   hc04_reset_low();
   _delay_ms(1000);
   hc04_reset_high();
}


void hc04_init() {
   // Reset BT module.
   hc04_reset_pin_output();
   hc04_reset();
   
   // Change BT module baud rate & name.
   if (0 != usart0_baud_rate(9600)) // Test if BT module respond @ 9600 (i.e. default settings).
      blink_error(".");

   //if (0 != hc04_baud_rate(38400)) // BT module is using default settings, set higher (38400) baud rate.
   //   blink_error("..");
   
   //if (0 != usart0_baud_rate(38400)) // Set USART baud rate to match BT module.
   //   blink_error("...");

   if (0 != hc04_device_name("58.baboom.me")) // Set BT module name.
      blink_error("....");

   blink_error("----");
}


int hc04_baud_rate(uint16_t baud) {
   int err = 0;
   switch (baud) {
      case 1200:
          err = usart0_send_line("AT+BAUD1");
          break;
      case 2400:
         err = usart0_send_line("AT+BAUD2");
         break;
      case 4800:
         err = usart0_send_line("AT+BAUD3");
         break;
      case 9600:
         err = usart0_send_line("AT+BAUD4");
         break;
      case 19200:
         err = usart0_send_line("AT+BAUD5");
         break;
      case 38400:
         err = usart0_send_line("AT+BAUD6");
         break;
      case 57600:
         err = usart0_send_line("AT+BAUD7");
         break;
      //case 115200:
      //   err = usart0_send_line("AT+BAUD8");
      //   break;
      default:
         return 1;
   }
   
   if (err == 0)
      return usart0_receive_ok();
      
   // Don't wait for OK since USART is still using old baud rate.
   return err; 
}


int hc04_device_name(const char* name) {     
   if (strlen(name) > 20)
      return 1;
      
   char buffer[32]; // "AT+NAME[device_name_20_char_max]";   
   sprintf(buffer, "AT+NAME%s", name);
   
   if (0 == usart0_send_line(buffer)) {
      _delay_ms(USART_DELAY_MS);
      return usart0_receive_ok();
   }      
      
   return 1;
}


/*
Q. Module does not respond @ any baud rate (9600, 38400, 57600)
T. Set to 57600 then error is too high cannot recognize response.
A. Connect module to a PC and set baud rate from terminal.


Applying 'low' to reset pin (11) does not reset it (neither name, nor baud rate)

http://www.elecfreaks.com/wiki/index.php?title=Bluetooth_Bee
*/
/*
int hc04_test_baud_rate() {
   char o, k;
   
   o = '-', k = '-';
   usart0_baud_rate(9600);
   usart0_send_line("AT");
   blink();
   o = usart0_receive_byte_with_timeout();
   k = usart0_receive_byte_with_timeout();
   if ((o == 'o' || o == 'O') && (k == 'k' || k == 'K'))
   blink_error("-");

   o = '-', k = '-';
   usart0_baud_rate(38400);
   usart0_send_line("AT");
   blink();
   o = usart0_receive_byte_with_timeout();
   k = usart0_receive_byte_with_timeout();
   if ((o == 'o' || o == 'O') && (k == 'k' || k == 'K'))
   blink_error("--");
   
   o = '-', k = '-';
   usart0_baud_rate(57600);
   usart0_send_line("AT");
   blink();
   o = usart0_receive_byte_with_timeout();
   k = usart0_receive_byte_with_timeout();
   if ((o == 'o' || o == 'O') && (k == 'k' || k == 'K'))
   blink_error("---");
   
   //usart0_send_line("AT+NAMEbaboom.me\r\n");
   //if (0 == usart0_receive_ok())
   //   blink_error("---");
   //blink_error("---");
   return 0;
}*/
