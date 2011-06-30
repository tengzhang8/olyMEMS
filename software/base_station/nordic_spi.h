//Base Station
//File: nordic_spi.h
//Implements low level SPI functions to interface to the Nordic Wireless
//Copyright C. Au and T. Zhang, 2011

#define NORDIC_IRQ		PB5
#define	NORDIC_CSN		PB0
#define	NORDIC_CE		PB6
#define NORDIC_SCK		PB1
#define	NORDIC_MISO		PB3
#define NORDIC_MOSI		PB2

#define TRUE			1
#define	FALSE			0


//Macros
#define NORDIC_CSN_HIGH()		PORTB |= (1<<NORDIC_CSN)
#define NORDIC_CSN_LOW()		PORTB &= ~(1<<NORDIC_CSN)
#define NORDIC_CE_HIGH()		PORTB |= (1<<NORDIC_CE)
#define NORDIC_CE_LOW()			PORTB &= ~(1<<NORDIC_CE)

void init_nordic_spi();

uint8_t nordic_transfer_byte(uint8_t byte);
