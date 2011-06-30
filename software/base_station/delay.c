//Calibrated delay Library using loops

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "delay.h"

//Calibrated with 7.3728Mhz Crystal
void delay_10us() {

	volatile int count = 1;
	for(count;count>0;count--);
	count = count + 1;
}

void delay_10us_multiple(volatile unsigned char i) {
	for(i;i>0;i--) {
		delay_10us();
	}
}
/* - Failed timer experiment.september 07, 2010. constant delay too long.
void init_delay_timer() {
	//Set to no prescaling
	TCCR1B |= (1<<CS10);
}

void delay_us(uint16_t x) {

    while(x > 500)
    {
        TIFR1 = (1<<TOV1); //Clear any interrupt flags on Timer2
        TCNT1 = 65535-3687; //256 - 125 = 131 : Preload timer 2 for x clicks. Should be 1us per click
        while( (TIFR1 & (1<<TOV1)) == 0);

        x -= 500;
    }

	//x = x*74;
	//x = x/10;

    TIFR1 = (1<<TOV1); //Clear any interrupt flags on Timer2
    TCNT1= 65465; //256 - 125 = 131 : Preload timer 2 for x clicks. Should be 1us per click
    while( (TIFR1 & (1<<TOV1)) == 0);
}
*/
