#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif	

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 500

int main(void)
{
/*
Main entry program
*/

  DDRC = 0xFF; //Nakes PORTC as Output	(thats pin PC0(23) till PC5(28))
  while(1) //infinite loop
   {
     PORTC = 0xFF; //Turns ON All LEDs
     _delay_ms(BLINK_DELAY_MS);
     PORTC= 0x00; //Turns OFF All LEDs
     _delay_ms(BLINK_DELAY_MS);
   }
 
}
