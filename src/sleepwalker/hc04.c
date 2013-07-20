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

#include "hc04.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"


int hc04_at_command(const char* command, const char* param) {
    uint8_t req_resp[20] = {0};
    sprintf((char*)req_resp, "AT + %s%s", command, param);
    
    usart0_write(req_resp, strlen((char*)req_resp) + 1);
    usart0_read(req_resp, sizeof(req_resp));
    
    if (req_resp[0] == 'O' && req_resp[1] == 'K')
      return 0; // No error.
    
    return -1;
}
