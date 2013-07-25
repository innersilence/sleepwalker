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

#include <avr/io.h>
#include <avr/interrupt.h>

#include "sleepwalker.h"
#include "usart.h"


usart_buffer the_buffer;


void usart0_init(uint16_t baud) {
   uint16_t baud_value = (F_CPU / (baud * 16UL)) - 1;
   
   UBRR0H = (uint8_t)(baud_value >> 8);
   UBRR0L = (uint8_t)baud_value;
   
   UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set frame format to 8 data bits, no parity, 1 stop bit.   
   UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);  // Enable reception and RC complete interrupt.
}


void usart0_buffer_init(usart_buffer* buffer) {
   buffer->index = 0;
}


uint8_t usart0_write(usart_buffer* buffer, uint8_t byte) {
   if (buffer->index < MAX_SBUFFER_SIZE) {
      buffer->data[buffer->index] = byte;
      buffer->index ++;
      return 0;
   }
   
   return 1;
}


uint8_t usart0_read(usart_buffer* buffer, volatile uint8_t* byte) {
   if (buffer->index > 0) {
      buffer->index --;
      *byte = buffer->data[buffer->index];
      return 0;
   }
   
   return 1;
}


ISR(USART_RX_vect) {
   uint8_t byte = UDR0;
   
   if ((usart0_write(&the_buffer, byte) == 1) || (byte == '.')) { // Check if period char or end of buffer.     
      UCSR0B &= ~((1 << RXEN0) | (1 << RXCIE0)); // Disable reception and RX Complete interrupt.      
      UCSR0B |= (1 << TXEN0) | (1 << UDRIE0); // Enable transmission and UDR0 empty interrupt.
   }
}


ISR(USART_UDRE_vect) {
   // If index is not at start of buffer.
   if (usart0_read(&the_buffer, &UDR0) == 1) {
      usart0_buffer_init(&the_buffer); // start over, reset buffer.
      
      UCSR0B &= ~((1 << TXEN0) | (1 << UDRIE0)); // Disable transmission and UDR0 empty interrupt.     
      UCSR0B |= (1 << RXEN0) | (1 << RXCIE0); // Enable reception and RC complete interrupt.
   }
}
