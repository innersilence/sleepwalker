#ifndef SLEEPWALKER_H_
#define SLEEPWALKER_H_

#define F_CPU 8000000UL // CPU clock 8 MHz

// LED pins.
#define LED_RED_PIN  10
#define LED_IR_PIN   11

// TSL230 pins.
#define TSL_FREQ	2		// Interrupt pin.
#define TSL_S0		4		// Sensitivity pin 0.
#define TSL_S1		5		// Sensitivity pin 1.
#define TSL_S2		6		// Scaling pin 0.
#define TSL_S3		7		// Scaling pin 1.
#define TSL_OE		8		// Output Enabled.

#define POLL_FREQ_HZ 50

#endif /* SLEEPWALKER_H_ */

