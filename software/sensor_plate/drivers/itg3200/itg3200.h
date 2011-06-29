#include "projectconfig.h"

#define BUFSIZE 64


void gyroinit(void);
void clrbuf(void);
void readgyro(uint8_t n, int16_t *gyroxout, int16_t *gyroyout, int16_t *gyrozout, int16_t *gyrotout);