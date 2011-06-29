//Sensor Plate
//File: nordic_spi.h
//Implements low-level SPI functions for interacting with the NORDIC library
//Copyright C. Au and T. Zhang, 2010
#include "projectconfig.h"
#include "core/gpio/gpio.h"
#include "core/timer16/timer16.h"

#define NORDIC_IRQ		0
#define	NORDIC_CSN		1
#define	NORDIC_CE		2
#define NORDIC_SCK		10
#define	NORDIC_MISO		8
#define NORDIC_MOSI		9

//#define TRUE			1
//#define	FALSE			0


//Macros
#define NORDIC_CSN_HIGH()		gpioSetValue (1, NORDIC_CSN, 1)
#define NORDIC_CSN_LOW()		gpioSetValue (1, NORDIC_CSN, 0)
#define NORDIC_CE_HIGH()		gpioSetValue (1, NORDIC_CE, 1)
#define NORDIC_CE_LOW()			gpioSetValue (1, NORDIC_CE, 0)

void switch_nordic();
void init_nordic_spi();

//Low level functions
uint8_t nordic_transfer_byte(uint8_t byte);
