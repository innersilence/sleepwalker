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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "usart.h"



void usart0_send_byte(uint8_t byte) {
   while (!(UCSR0A & (1 << UDRE0))) {
      // Wait while previous byte is completed.
   }
   UDR0 = byte; // Transmit data.
}


uint8_t usart0_receive_byte(void) {
   while (!(UCSR0A & (1 << RXC0))) {
      // Wait for byte to be received.
   }
   return UDR0;
}


uint8_t usart0_receive_byte_with_timeout(void) { // 1 second timeout.
   for (int i = 0; i < 20; ++ i) {
      if (!(UCSR0A & (1 << RXC0))) {
         _delay_ms(50);
      }
   }   
   return UDR0;
}


// UBRR calculator http://www.wormfood.net/avrbaudcalc.php
uint8_t usart0_baud_rate(uint16_t baud) {
   UCSR0B = 0x0; // Disable USART.
   
   uint16_t ubrr_value = F_CPU / (baud * 16UL) - 1;
   
   UBRR0H = (uint8_t)(ubrr_value >> 8); // Set baud rate (high then low bytes).
   UBRR0L = (uint8_t)ubrr_value;
   
   UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Set frame format to 8 data bits, no parity, 1 stop bit.
   UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Enable transmission and reception.

   usart0_send_line("AT"); // Send "AT" wait for "OK".
   _delay_ms(USART_DELAY_MS);

   return usart0_receive_ok();
}


uint8_t usart0_send_line(const char* str) {
   int len = strlen(str);
   for (int i = 0; i < len; ++ i) {
      usart0_send_byte(str[i]);
   }
   return 0;
}


uint8_t usart0_receive_ok(void) {
   char ok[2] = {0};
   ok[0] = usart0_receive_byte_with_timeout();
   ok[1] = usart0_receive_byte_with_timeout();
   
   if ((ok[0] == 'o' || ok[0] == 'O') && (ok[1] == 'k' || ok[1] == 'K'))
      return 0;

   return 1;
}
