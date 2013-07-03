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

#ifndef SLEEPWALKER_H_
#define SLEEPWALKER_H_

#define F_CPU 8000000UL // CPU clock 8 MHz

// TSL230 pins.
#define TSL_FREQ	2		// Interrupt pin.
#define TSL_S0		4		// Sensitivity pin 0.
#define TSL_S1		5		// Sensitivity pin 1.
#define TSL_S2		6		// Scaling pin 0.
#define TSL_S3		7		// Scaling pin 1.
#define TSL_OE		8		// Output Enabled.

#define POLL_FREQ_HZ 50

#endif /* SLEEPWALKER_H_ */

