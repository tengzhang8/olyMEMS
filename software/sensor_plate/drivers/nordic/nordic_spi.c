//Sensor Plate
//File: nordic_spi.c
//Implements low-level SPI functions for interacting with the NORDIC library
//Copyright C. Au and T. Zhang, 2010

#include "nordic_spi.h"
#include "core/gpio/gpio.h"
#include "core/ssp/ssp.h"

void switch_nordic(void) {
	/*
	uint32_t configReg = ( SSP_SSP0CR0_DSS_8BIT   // Data size = 8-bit
                  | SSP_SSP0CR0_FRF_SPI           // Frame format = SPI
                  | SSP_SSP0CR0_SCR_8);           // Serial clock rate = 8
  
    // Set clock polarity
      configReg &= ~SSP_SSP0CR0_CPOL_MASK;    // Clock polarity = Low between frames
  
    // Set edge transition
       //configReg |= SSP_SSP0CR0_CPHA_SECOND;  // Clock Phase = data transition on falling edge
	   configReg &= ~SSP_SSP0CR0_CPHA_MASK;    // Clock out phase = Leading edge clock transition
	   
    // Assign config values to SSP0CR0
    SSP_SSP0CR0 = configReg;
	*/
	
	sspInit (0, sspClockPolarity_Low, sspClockPhase_RisingEdge);

}

//Initializes the SPI module of the AVR to work with the NORDIC
void init_nordic_spi() {

	//Configure IO Directions
	// config CSN pin
	IOCON_JTAG_TDO_PIO1_1 &= ~IOCON_JTAG_TDO_PIO1_1_FUNC_MASK;
	IOCON_JTAG_TDO_PIO1_1 |= IOCON_JTAG_TDO_PIO1_1_FUNC_GPIO;
    gpioSetDir(1, NORDIC_CSN, gpioDirection_Output);
	// config CE pin
	IOCON_JTAG_nTRST_PIO1_2 &= ~IOCON_JTAG_nTRST_PIO1_2_FUNC_MASK;
	IOCON_JTAG_nTRST_PIO1_2 |= IOCON_JTAG_nTRST_PIO1_2_FUNC_GPIO;
    gpioSetDir(1, NORDIC_CE, gpioDirection_Output);
	// config IRQ pin - needs to be input actually.
	IOCON_JTAG_TMS_PIO1_0 &= ~IOCON_JTAG_TMS_PIO1_0_FUNC_MASK;
	IOCON_JTAG_TMS_PIO1_0 |= IOCON_JTAG_TMS_PIO1_0_FUNC_GPIO;
    
	//Edited to be input
	gpioSetDir(1, NORDIC_IRQ, gpioDirection_Input);
	

	//Drive nCS HIGH
	NORDIC_CSN_HIGH();

	//Configure UART1 in SPI MODE
	//CPOL and CPHA both at 0? 
	//SCK should normally be low. And the clock samples data in the middle of data bits, 
	sspInit (0, sspClockPolarity_Low, sspClockPhase_RisingEdge);

	timer16Init(0, TIMER16_DEFAULTINTERVAL);
}

//Low-level function to send and receive SPI data 
uint8_t nordic_transfer_byte(uint8_t byte) {

	//sspSend (0, &byte, 1);
	//sspReceive (0, &byte, 1);	
	sspTransfer(0, &byte, 1);

	return byte;
}


