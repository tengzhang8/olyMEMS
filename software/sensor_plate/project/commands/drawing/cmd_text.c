/**************************************************************************/
/*! 
    @file     cmd_text.c
    @author   K. Townsend (microBuilder.eu)

    @brief    Code to execute for cmd_text in the 'core/cmd'
              command-line interpretter.

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2010, microBuilder SARL
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include <stdio.h>
#include <string.h>

#include "projectconfig.h"
#include "core/cmd/cmd.h"
#include "project/commands.h"       // Generic helper functions

#ifdef CFG_TFTLCD    
  #include "drivers/lcd/tft/lcd.h"    
  #include "drivers/lcd/tft/drawing.h"  
  #include "drivers/lcd/tft/fonts/inconsolata9.h"
  #include "drivers/lcd/tft/fonts/inconsolata11.h"

/**************************************************************************/
/*! 
    Displays the supplied text on the LCD.
*/
/**************************************************************************/
void cmd_text(uint8_t argc, char **argv)
{
  int32_t x, y, color;
  int32_t font;
  uint8_t i, len;
  char *data_ptr, data[80];
  
  // Convert supplied parameters
  getNumber (argv[0], &x);
  getNumber (argv[1], &y);
  getNumber (argv[2], &color);
  getNumber (argv[3], &font);

  // Get message contents
  data_ptr = data;
  for (i=0; i<argc-4; i++)
  {
    len = strlen(argv[i+4]);
    strcpy((char *)data_ptr, (char *)argv[i+4]);
    data_ptr += len;
    *data_ptr++ = ' ';
  }
  *data_ptr++ = '\0';

  if (font == 1)
  {
    drawString((uint16_t)x, (uint16_t)y, (uint16_t)color, &inconsolata11ptFontInfo, (char *)&data);
    return;
  }
  else
  {
    // Use 9 point font as default
    drawString((uint16_t)x, (uint16_t)y, (uint16_t)color, &inconsolata9ptFontInfo, (char *)&data);
  }
}

#endif  
