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



#include <string.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
void test_usart(void);

uint8_t usart_test_baud_rate(uint16_t baud);
uint8_t usart_send_line(const char* str);


int main(void) {  

   if (usart_test_baud_rate(9600)) {
      while (1) {
         usart_send_line("hello, world!");
         blink();
      }
   } else
      blink_error("---");
   
   /*usart0_init(38400);
   
   sei();
     
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

void test_usart0_send_byte(uint8_t byte) {   
   while (!(UCSR0A & (1 << UDRE0))) {
      // Wait while previous byte is completed.   
   }   
   UDR0 = byte; // Transmit data.
}

uint8_t test_usart0_receive_byte() {   
   while (!(UCSR0A & (1 << RXC0))) {
      // Wait for byte to be received.
   } 
   return UDR0;
}

uint8_t usart_test_baud_rate(uint16_t baud) {
   UCSR0B = 0x0; // Disable USART.
   
   uint16_t ubrr_value = F_CPU / baud / 16UL - 1;
   
   UBRR0H = (uint8_t)(ubrr_value >> 8); // Set baud rate (high then low bytes).
   UBRR0L = (uint8_t)ubrr_value;
   
   UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set frame format to 8 data bits, no parity, 1 stop bit.
   UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // Enable transmission and reception.
   
   const char* command = "AT";
   for (int i = 0; i < strlen(command); ++ i) {
      test_usart0_send_byte(command[i]);
   }
   
   char ok[2];
   ok[0] = test_usart0_receive_byte();
   ok[1] = test_usart0_receive_byte();
   if ((ok[0] == 'o' || ok[0] == 'O') && (ok[1] == 'k' || ok[1] == 'K'))
     return 1;

   return 0;
}


uint8_t usart_send_line(const char* str) {
   int len = strlen(str);
   for (int i = 0; i < len; ++ i) {
      test_usart0_send_byte(str[i]);
   }
   return 1;
}


void test_usart(void) {   
   UBRR0H = (uint8_t)(UBRR_VALUE >> 8); // Set baud rate (high then low bytes).
   UBRR0L = (uint8_t)UBRR_VALUE;
      
   UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set frame format to 8 data bits, no parity, 1 stop bit.  
   UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // Enable transmission and reception.
   
   //const char* command = "AT + NAMEbaboom.me";
   //const char* command = "hello, world!";
   const char* command = "AT";
   for (int i = 0; i < strlen(command); ++ i) {
      test_usart0_send_byte(command[i]);
   }
   
   //blink_error(".");
    
   char ok = test_usart0_receive_byte(); // Blocks indefinitely...
   if (ok == 'o' || ok == 'O')
      blink_error("---");
   else
      blink_error("...");
}

// [-] terminate command with "\r\n", HC-06 doesn't need termination (HC-04, HC-05 do).
// [?] AFio clock frequency? Has to be divided by 1.8432MHz.

