//Sensor Plate
//File: itg3200.h
//Contains functions to operate the ITG3200 gyroscope
//Copyright C. Au and T. Zhang, 2011

#include "projectconfig.h"

#define BUFSIZE 64

void gyroinit(void);
void clrbuf(void);
void readgyro(uint8_t n, int16_t *gyroxout, int16_t *gyroyout, int16_t *gyrozout, int16_t *gyrotout);
