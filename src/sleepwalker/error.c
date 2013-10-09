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
#include <util/delay.h>
#include <string.h>

#include "error.h"

/*void blink_init() {
   DDRB |= _BV(DDB5);            // PB.5 output.
}*/


void blink_error(const char* code) {
   DDRB |= _BV(DDB5); // PB.5 output.
   while (1) {
      for (int i = 0; i < strlen(code); ++ i) {
         PORTB |= _BV(DDB5);          // PB.5 high.
         switch (code[i]) {           // keep high.
            case '.':
               _delay_ms(ERROR_DOT);
               break;
            case '-':
               _delay_ms(ERROR_DASH);
               break;
         }
         PORTB &= ~_BV(DDB5);         // PB.5 low.
         _delay_ms(ERROR_INTERVAL);   // keep low.  
      }
      
      _delay_ms(ERROR_REPEAT_AFTER);
   }  
}

void blink() {   
   DDRB |= _BV(DDB5);            // PB.5 output.
   PORTB |= _BV(DDB5);           // PB.5 high.
   _delay_ms(ERROR_DOT);
   PORTB &= ~_BV(DDB5);          // PB.5 low.
   _delay_ms(ERROR_INTERVAL);    // keep low.  
}


void error_hc04_command_failed() {
   blink_error("....-");
}