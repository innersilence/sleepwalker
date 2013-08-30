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

#include "hc04.h"
#include "usart.h"



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
   
   // Don't wait for OK since USART is still using old baud rate.
   return err; 
}

int hc04_device_name(const char* name) {
   char buffer[32]; // "AT+NAME[device_name_20_char_max]\r\n";
   
   if (strlen(name) > 20)
      return 1;
      
   sprintf(buffer, "AT+NAME%s", name);
   if (0 == usart0_send_line(buffer)) {
      _delay_ms(1000);
      return usart0_receive_ok();
   }      
      
   return 1;
}
