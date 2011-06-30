//Base Station
//File: Bitmap.c
//Displays the stored bitmap image on LCD (for the welcome splash screen)
//Copyright C. Au and T. Zhang, 2010

//************************************************************************
// Bitmap.C
//************************************************************************
#include <avr/pgmspace.h>
#include "Bitmap.h"
#include "ks0108.h"
//##########################################################
void LoadBitmap(unsigned char *bitmap)
{
uint16_t i, j,by;
for(i=0; i<64; i+=8)

		for(j=0; j<128; j++)
		{
			by=pgm_read_byte(bitmap++);
			ks0108GotoXY(j, i);
			ks0108WriteData(by);
		}

}
