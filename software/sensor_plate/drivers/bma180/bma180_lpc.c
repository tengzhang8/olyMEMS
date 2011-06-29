#include "bma180_lpc.h"
#include "core/gpio/gpio.h"
#include "core/ssp/ssp.h"


void BMA180_CS_low(void) {
//	gpioSetValue (0, 2, 0);
	gpioSetValue (1, 10, 0);	//1 10
}

void BMA180_CS_high(void) {
//	gpioSetValue (0, 2, 1);
	gpioSetValue (1, 10, 1);
}


void txdata(uint8_t data) {
	sspSend (0, &data, 1);
}

uint8_t rxdata(void) {
	uint8_t rxbuf = 0;
	sspReceive(0, &rxbuf, 1);
	return rxbuf;
}

uint8_t BMA180_single_read(uint8_t address) {
	//Returns the contents of any 1 byte register from any address
	//sets the MSB for every address byte (READ mode)

	uint8_t byte;

	address |= 0x80;		//0x80 = 0b10000000

	BMA180_CS_low();
	txdata(address);
	byte = rxdata();
	BMA180_CS_high();

	return byte;
}

void BMA180_single_write(uint8_t address, uint8_t data) {
	//Write any data byte to any single address
	//adds a 0 to the MSB of the address byte (WRITE mode)

	address &= 0x7F;		//0x7F = 0b01111111

	BMA180_CS_low();
	txdata(address);
	txdata(data);
	BMA180_CS_high();
}


void BMA180_multiple_read(uint8_t address, uint8_t *data, uint8_t len) {

	uint8_t i;

	address |= 0x80;		//0x80 = 0b10000000

	BMA180_CS_low();
	txdata(address);
	for(i=0;i<len;i++) {
		data[i] = rxdata();
	}
	BMA180_CS_high();
}

void switch_BMA180(void) {
	/*
	uint32_t configReg = ( SSP_SSP0CR0_DSS_8BIT   // Data size = 8-bit
                  | SSP_SSP0CR0_FRF_SPI           // Frame format = SPI
                  | SSP_SSP0CR0_SCR_8);           // Serial clock rate = 8
  
    // Set clock polarity
      configReg |= SSP_SSP0CR0_CPOL_HIGH;     // Clock polarity = High between frames
  
    // Set edge transition
      configReg |= SSP_SSP0CR0_CPHA_SECOND;   // Clock out phase = Trailing edge clock transition

  
    // Assign config values to SSP0CR0
    SSP_SSP0CR0 = configReg;
	*/
	
	sspInit (0, sspClockPolarity_High, sspClockPhase_FallingEdge);
}


int init_BMA180(uint8_t range, uint8_t bw) {
	char temp, temp1;
	
	uint8_t address = 0;
	
    sspInit (0, sspClockPolarity_High, sspClockPhase_FallingEdge);	
	
//	gpioSetDir(1, 10, gpioDirection_Output);
	gpioSetDir(0, 11, gpioDirection_Input);		


	// if connected correctly, ID register should be 3
	if(BMA180_single_read(ID) != 3)
		return -1;
		
	//-------------------------------------------------------------------------------------
	// Set ee_w bit
	address = CTRLREG0;
	temp = BMA180_single_read(address);
	temp |= 0x10;
	BMA180_single_write(address, temp);	// Have to set ee_w to write any other registers
	//-------------------------------------------------------------------------------------

	//Disable I2C
	address = HIGHDUR;
	temp = BMA180_single_read(address);
	temp |= 0x01;  //Set dis_I2C to high
	BMA180_single_write(address, temp);

	//Enable New Data Interrupt
	address = CTRLREG3;	
	temp = BMA180_single_read(address);
	temp |= 0x02;	//Set new_data_int to 1
	BMA180_single_write(address, temp);

	// Set BW
	address = BWTCS;	
	temp = BMA180_single_read(address);
	temp1 = bw;
	temp1 = temp1<<4;
	temp &= (~BWMASK);
	temp |= temp1;
	BMA180_single_write(address, temp);		// Keep tcs<3:0> in BWTCS, but write new BW
	//-------------------------------------------------------------------------------------
	// Set Range
	address = OLSB1;	
	temp = BMA180_single_read(address);
	temp1 = range;
	temp1 = (temp1<<RANGESHIFT);
	temp &= (~RANGEMASK);
	temp |= temp1;
	BMA180_single_write(address, temp); //Write new range data, keep other bits the same
	//-------------------------------------------------------------------------------------


	

	return 0;
}

volatile int sample_BMA180(volatile int16_t data[4]) {
	//uint8_t temp;
	uint8_t address = 0;

	uint8_t data_temp[7];

	//Reset INT to erase any past data. obtain fresh sample
	//address = CTRLREG0;	
	//temp = BMA180_single_read(address);
	//temp |= 0b01000000;	//Set reset_int to 1
	//BMA180_single_write(address, temp);

	//Now wait for interrupt to generate
	//while((PINB & (1<<BMA180_INT)) == 0);
	while(gpioGetValue(0, 11) == 0);
//	while(gpioGetValue(2, 0) == 0);
	
	//Now read all the raw data out.
	address = ACCXLSB;
	BMA180_multiple_read(address, data_temp, 7);

	//Process X AXIS
	data[0] = data_temp[1] << 8;	//Handle MSB
	data[0] |= data_temp[0];
	data[0] = data[0] >> 2; //Get rid of the two non-value bits in LSB
	

	//Process Y AXIS
	data[1] = data_temp[3] << 8;	//Handle MSB
	data[1] |= data_temp[2];
	data[1] = data[1] >> 2; //Get rid of the two non-value bits in LSB
	

	//Process Z AXIS
	data[2] = data_temp[5] << 8;	//Handle MSB
	data[2] |= data_temp[4];
	data[2] = data[2] >> 2; //Get rid of the two non-value bits in LSB	

	//Process Temperature
	data[3] = (int8_t) data_temp[6];

	return 1;

}