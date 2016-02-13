#define F_CPU 16000000UL

/**
 * A PWM example for the ATmega328P using the 8-Bit Fast PWM mode.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const int brightness[] = {1, 1, 2, 3, 5, 8, 11, 15, 20, 25, 30, 36, 43, 
49, 56, 64, 72, 80, 88, 97, 105, 114, 123, 132, 141, 150, 158, 167, 175, 
183, 191, 199, 206, 212, 219, 225, 230, 235, 240, 244, 247, 250, 252, 
253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 230, 225, 219, 
212, 206, 199, 191, 183, 175, 167, 158, 150, 141, 132, 123, 114, 105, 
97, 88, 80, 72, 64, 56, 49, 43, 36, 30, 25, 20, 15, 11, 8, 5, 3, 2, 1, 0};

int main (void) {

	/**
	 * We will be using OCR1A as our PWM output which is the
	 * same pin as PB1.
	 */
	DDRB |= _BV(PB1);

	/**
	 * There are quite a number of PWM modes available but for the
	 * sake of simplicity we'll just use the 8-bit Fast PWM mode.
	 * This is done by setting the WGM10 and WGM12 bits.  We 
	 * Setting COM1A1 tells the microcontroller to set the 
	 * output of the OCR1A pin low when the timer's counter reaches
	 * a compare value (which will be explained below).  CS10 being
	 * set simply turns the timer on without a prescaler (so at full
	 * speed).  The timer is used to determine when the PWM pin should 
be
	 * on and when it should be off.
	 */
	TCCR1A |= _BV(COM1A1) | _BV(WGM10);
	TCCR1B |= _BV(CS10) | _BV(WGM12);

	/**
	 *  This loop is used to change the value in the OCR1A register.
	 *  What that means is we're telling the timer waveform generator
	 *  the point when it should change the state of the PWM pin.
	 *  The way we configured it (with _BV(COM1A1) above) tells the
	 *  generator to have the pin be on when the timer is at zero and 
then
	 *  to turn it off once it reaches the value in the OCR1A 
register.
	 *
	 *  Given that we are using an 8-bit mode the timer will reset to 
zero
	 *  after it reaches 0xff, so we have 255 ticks of the timer until 
it
	 *  resets.  The value stored in OCR1A is the point within those 
255
	 *  ticks of the timer when the output pin should be turned off
	 *  (remember, it starts on).
	 *
	 *  Effectively this means that the ratio of pwm / 255 is the 
percentage
	 *  of time that the pin will be high.  Given this it isn't too 
hard
	 *  to see what when the pwm value is at 0x00 the LED will be off
	 *  and when it is 0xff the LED will be at its brightest.
	 */
	uint8_t pwm = 0x00;
	int i = 0;
	int arraySize = sizeof(brightness);
	for(;;) {
		pwm = brightness[i];
		i += 1;
		OCR1A = pwm;
		if (i > arraySize)i=0;
		_delay_ms(12);
	}

}
