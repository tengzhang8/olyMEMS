//Calibrated delay Library using loops

#include <avr/io.h>
#include <stdlib.h>
#include "flash.h"
#include "delay.h"

/*
uint8_t nordic_transfer_byte(uint8_t byte) {
	//Wait for empty transmit buffer
	while(!(UCSR1A & (1<<UDRE1)));

	//Put data into the buffer, sends data
	UDR1 = byte;

	//Wait for data to be received
	while(!(UCSR1A & (1<<RXC1))); 

	//Get and return received data from buffer
	return UDR1;
}

//Flash OPCODES
#define WR_ENABLE	0x06
#define RD_STATUS	0x05
#define RD_ARRAY	0x03

#define	BK_ERASE4	0x20
#define BK_ERASE32	0x52
#define BK_ERASE64	0xD8

#define BP_PROGRAM	0x02
*/


void flash_init() {

	DDRD |= (1<<FLASH_CSN);



	//UBRR should be set to zero at the time the transmitter is enabled, then set the correct value.
	UBRR1L = 0;
	UBRR1H = 0;

	//Set MSPI mode of operation and SPI data mode 0
	UCSR1C = (1<<UMSEL11)|(1<<UMSEL10)|(0<<UCPHA1)|(0<<UCPOL1);

	//Enable receiver and transmitter
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);

	//Set final baud rate
	UBRR1 = 1;





	flash_csn_high();
	//Others would have been setup by init_nordic

	//Disable all write protects
	write_status_reg(0x00);
}

void flash_csn_low() {
	PORTD &= ~(1<<FLASH_CSN);
}

void flash_csn_high() {
	PORTD |= (1<<FLASH_CSN);
}

uint8_t flash_transfer_byte(uint8_t byte) {
	//Wait for empty transmit buffer
	while(!(UCSR1A & (1<<UDRE1)));

	//Put data into the buffer, sends data
	UDR1 = byte;

	//Wait for data to be received
	while(!(UCSR1A & (1<<RXC1))); 

	//Get and return received data from buffer
	return UDR1;
}


//Write Enable comand is used to set the Write Enable Latch bit in the Status Register to 1.
//The WEL bit must be set before a Byte/Page Program, erase..or write status register command
void write_enable() {
	//First bring CSN low
	flash_csn_low();

	//Transfer Write Enable OPCODE
	flash_transfer_byte(WR_ENABLE);

	//Bring CSN High again
	flash_csn_high();
}

//Byte Page Program allows 1 to 256 bytes of data to be programmed into previously erased memory locations
//Erased locations have a logical state fo 1
void flash_program(uint8_t address[3], uint8_t *data, int len) {

	int i;

	//First we need to enable write
	write_enable();
	
	//Bring CSN low
	flash_csn_low();

	//Write OPCODE
	flash_transfer_byte(BP_PROGRAM);

	//Write the three addresses
	flash_transfer_byte(address[2]);
	flash_transfer_byte(address[1]);
	flash_transfer_byte(address[0]);

	for(i=0;i<len;i++) {
		flash_transfer_byte(data[i]);
	}

	//Bring CSN high
	flash_csn_high();

	//Loop until write actually has taken place.
	while(flash_busy() == 1);

}

void flash_read(uint8_t address[3], uint8_t *data, int len) {
	int i;
	
	//Bring CSN low
	flash_csn_low();

	//Write OPCODE
	flash_transfer_byte(RD_ARRAY);

	//Write the three addresses
	flash_transfer_byte(address[2]);
	flash_transfer_byte(address[1]);
	flash_transfer_byte(address[0]);

	for(i=0;i<len;i++) {
		data[i] = flash_transfer_byte(data[i]);
	}

	//Bring CSN high
	flash_csn_high();

}

void block_erase(uint8_t address[3], uint8_t byte) {
	//First we need to enable write
	write_enable();
	
	//Bring CSN low
	flash_csn_low();

	//Write OPCODE
	flash_transfer_byte(byte);

	//Write the three addresses
	flash_transfer_byte(address[2]);
	flash_transfer_byte(address[1]);
	flash_transfer_byte(address[0]);

	//Bring CSN high
	flash_csn_high();

	//Loop until erase actually has taken place.
	while(flash_busy() == 1);

}

uint8_t flash_busy() {

	uint8_t status_reg;

	//First bring CSN low
	flash_csn_low();

	//Transfer Read Status Register OPCODE
	flash_transfer_byte(RD_STATUS);

	//Feed another byte in to bring STATUS REG OUT
	status_reg = flash_transfer_byte(RD_STATUS);

	//Bring CSN High again
	flash_csn_high();

	//Extract RDY/BSY bit from status reg
	status_reg = status_reg & 1;

	return status_reg;
}

void write_status_reg(uint8_t byte) {

	//First we need to enable write
	write_enable();
	
	//Bring CSN low
	flash_csn_low();

	//Write OPCODE
	flash_transfer_byte(WR_STATUS);

	//Write the three addresses
	flash_transfer_byte(byte);

	//Bring CSN high
	flash_csn_high();
}
