//Base Station
//File: nordic_spi.c
//Implements low level SPI functions to interface to the Nordic Wireless
//Copyright C. Au and T. Zhang, 2011

#include <avr/io.h>
#include <stdlib.h>
#include "nordic_spi.h"
#include <stdbool.h>



// START CARSON****************************************************************************************************************************************
void init_nordic_spi() {

	//Configure IO Directions

	DDRB |= (1<<NORDIC_MOSI)|(1<<NORDIC_SCK)|(1<<NORDIC_CE)|(1<<NORDIC_CSN);
	DDRB &= ~((1<<NORDIC_IRQ)|(1<<NORDIC_MISO));

	//Drive nCS HIGH
	NORDIC_CSN_HIGH();

	//Configure SPI
	//CPOL and CPHA both at 0? 
	//SCK should normally be low. And the clock samples data in the middle of data bits, 

	SPCR |= (1<<MSTR)|(1<<SPR0); //CPOL and CPHA both 0
	
	//No spi clock prescaler, enable SPI2X
	//SPSR |= (1<<SPI2X);

	//Enable SPI
	SPCR |= (1<<SPE);
	
}


//Low Level Functions
/*
unsigned char nordic_execute_command(unsigned char instruction, unsigned char *data, unsigned int len, bool copydata) {
	unsigned char status;

	NORDIC_CSN_LOW();

	status = instruction;
	nordic_transfer(&status, 1, TRUE);
	nordic_transfer(data, len, copydata);

	NORDIC_CSN_HIGH();

	return status;
}


void nordic_transfer(unsigned char *data, unsigned int len, int copydata) {
	unsigned int count;
	unsigned char tempbyte;

	for(count = 0; count < len; count++) {
		if(copydata != FALSE) {
			data[count] = nordic_transfer_byte(data[count]);
		} else {
			tempbyte = data[count];
			nordic_transfer_byte(tempbyte);
		}
	}
}
*/

uint8_t nordic_transfer_byte(uint8_t byte) {

	SPDR = byte;

	while(!(SPSR & (1<<SPIF)));

	return SPDR;

}



/*
void nordic_transfer_block(uint8_t* data, uint8_t* buffer, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++) {
		//SPI WAIT??	
    	buffer[i] = nordic_transfer_byte(data[i]);
    }
}

void nordic_write_block(uint8_t* data, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++) {
          nordic_transfer_byte(data[i]);
          //SPI_WAIT()??
    }
}
*/
