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

  DDRD = 0xFF;				 //Makes PORTD as Output
  while(1) 				 //infinite loop
   {
     PORTD = 0xFF;			 //Turns ON All LEDs
     _delay_ms(BLINK_DELAY_MS);

     PORTD= 0x00; 			 //Turns OFF All LEDs
     _delay_ms(BLINK_DELAY_MS);
   }
 
}
