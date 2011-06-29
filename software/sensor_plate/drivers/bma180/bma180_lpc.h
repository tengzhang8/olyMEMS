//Sensor Plate
//File: bma180.h
//Contains functions to operate the BMA180 accelerometer
//Copyright C. Au and T. Zhang, 2010

//#ifndef BMA180_H_
//#define BMA180_H_

#include "projectconfig.h"
//Address defines for BMA180//
//====================//
//ID and Version Registers
#define ID 0x00
#define Version 0x01
#define ACCXLSB 0x02
#define ACCXMSB 0x03
#define ACCYLSB 0x04
#define ACCYMSB 0x05
#define ACCZLSB 0x06
#define ACCZMSB 0x07
#define TEMPERATURE 0x08
#define STATREG1 0x09
#define STATREG2 0x0A
#define STATREG3 0x0B
#define STATREG4 0x0C
#define CTRLREG0 0x0D
#define CTRLREG1 0x0E
#define CTRLREG2 0x0F

#define HIGHDUR 0x27

#define BWTCS 0x20
#define CTRLREG3 0x21

#define HILOWNFO 0x25
#define LOWDUR 0x26

#define LOWTH 0x29

#define tco_y 0x2F
#define tco_z 0x30

#define OLSB1 0x35

//====================//
//Range setting
#define RANGESHIFT 1
#define RANGEMASK 0x0E
#define BWMASK 0xF0
#define BWSHIFT 4

//#endif /* BMA180_H_ */


//Lines
#define BMA180_CS 		(1<<2)
//#define BMA180_INT		PB3

//Addresses
#define BMA180_ID		0x00

//void init_spi(void);
void txdata (uint8_t data);
uint8_t rxdata (void);


//inline void BMA180_CS_enable(void);
//inline void BMA180_CS_disable(void);

void BMA180_single_write(uint8_t address, uint8_t data);
uint8_t BMA180_single_read (uint8_t address);
void switch_BMA180(void);
int init_BMA180(uint8_t range, uint8_t bw);
volatile int sample_BMA180(volatile int16_t data[4]);
void BMA180_multiple_read(uint8_t address, uint8_t *data, uint8_t len);
