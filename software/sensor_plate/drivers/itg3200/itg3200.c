//Sensor Plate
//File: itg3200.c
//Contains functions to operate the ITG3200 gyroscope
//Copyright C. Au and T. Zhang, 2011

#include "itg3200.h"
#include "core/i2c/i2c.h"
#include "core/gpio/gpio.h"

extern volatile uint32_t I2CCount;
extern volatile uint32_t I2CMasterState;
extern volatile uint8_t I2CMasterBuffer[I2C_BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[I2C_BUFSIZE];
extern volatile uint32_t I2CReadLength, I2CWriteLength;

void gyroinit(void) 
{
	uint32_t i;
	// initialize I2c 
	if ( i2cInit( (uint32_t)I2CMASTER ) == FALSE ) {
		while ( 1 );				/* Fatal error */
	}  
	//Clearing slave buffer isn't needed but done anyway
	for ( i = 0; i < BUFSIZE; i++ ) {
		I2CSlaveBuffer[i] = 0x00;
	}

	// Perform I2C Write of Address, Write Start Reg, Data
	I2CWriteLength = 3;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = 0xD0; // Gyro Address
	I2CMasterBuffer[1] = 0x3E; // Register
	I2CMasterBuffer[2] = 0x01; // Sets internal clock source to PLL off x gyro
	i2cEngine();

	// Perform I2C Write of Address, Write Start Reg, Data
	I2CWriteLength = 5;
	I2CReadLength = 0;
	I2CMasterBuffer[0] = 0xD0; // Gyro Address
	I2CMasterBuffer[1] = 0x15; // Register
	I2CMasterBuffer[2] = 0x01; // Value for 0x15, Sampling rate divider
	I2CMasterBuffer[3] = 0x1a; // Value for 0x16, Range, low pass and sampl freq (1a)
	I2CMasterBuffer[4] = 0x31; // Value for 0x17, interrupt config
	i2cEngine();
}

// Clear the receive buffers
void clrbuf(void)
{
	int16_t i=0;

	for ( i = 0; i < I2C_BUFSIZE; i++ ) {
		I2CSlaveBuffer[i] = 0x00;
	}
}

void readgyro(uint8_t n, int16_t *gyroxout, int16_t *gyroyout, int16_t *gyrozout, int16_t *gyrotout)
{
/*
  if (gpioGetValue(CFG_LED_PORT, CFG_LED_PIN) == CFG_LED_OFF)
    {
	  gpioSetValue (CFG_LED_PORT, CFG_LED_PIN, CFG_LED_ON); 
    }
      else
    {
      gpioSetValue (CFG_LED_PORT, CFG_LED_PIN, CFG_LED_OFF); 
  }
*/

	int16_t gyrottemp; // Gyro Temperature (Temporary variable)
	int16_t gyroxtemp; // Gyro X (Temporary variable)
	int16_t gyroytemp; // Gyro Y (Temporary variable)
	int16_t gyroztemp; // Gyro Z (Temporary variable)

	clrbuf();

	// Acquiring Gyro Data
	I2CWriteLength = 2;
	I2CReadLength = 8;
	I2CMasterBuffer[0] = 0xD0; // Gyro Address + Write bit
	I2CMasterBuffer[1] = 0x1B; // Start read register
	I2CMasterBuffer[2] = 0xD0 | RD_BIT; // Gyro Address + Read bit to receive data
	i2cEngine();

	// Format Gyro Data
	gyrottemp=((I2CSlaveBuffer[0]<<8)|(I2CSlaveBuffer[1]))+13200; //Bit shifts the Temperature and scales
	gyroxtemp=((I2CSlaveBuffer[2]<<8)|(I2CSlaveBuffer[3]))+34; // 13Bit Shifts the Gyro X readings
	gyroytemp=((I2CSlaveBuffer[4]<<8)|(I2CSlaveBuffer[5]))+8; // -6Bit Shifts the Gyro Y readings
	gyroztemp=((I2CSlaveBuffer[6]<<8)|(I2CSlaveBuffer[7]))-2; // -14Bit Shifts the Gyro Z readings

	*gyroxout=gyroxtemp;//gyrosumx;
	*gyroyout=gyroytemp;//gyrosumy;
	*gyrozout=gyroztemp;//gyrosumz;
	*gyrotout=gyrottemp;//gyrosumt;

    clrbuf();
}

