//Base Station
//File: rotatedheadings.h
//Rotated headings font
//Copyright C. Au and T. Zhang, 2011

/*
 *
 * rotatedheadings
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : rotatedheadings.h
 * Date                : 05.09.2010
 * Font size in bytes  : 9342
 * Font width          : 10
 * Font height         : 15
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef ROTATEDHEADINGS_H
#define ROTATEDHEADINGS_H

#define ROTATEDHEADINGS_WIDTH 10
#define ROTATEDHEADINGS_HEIGHT 15

static uint8_t rotatedheadings[] PROGMEM = {
    0x24, 0x7E, // size
    0x0A, // width
    0x0F, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x02, 0x05, 0x08, 0x07, 0x0B, 0x0A, 0x02, 0x04, 0x04, 
    0x05, 0x08, 0x03, 0x03, 0x02, 0x07, 0x07, 0x06, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x02, 0x03, 0x07, 0x08, 
    0x07, 0x06, 0x0C, 0x0A, 0x07, 0x07, 0x08, 0x06, 0x06, 0x08, 
    0x08, 0x02, 0x04, 0x08, 0x06, 0x0C, 0x09, 0x09, 0x07, 0x0A, 
    0x07, 0x06, 0x08, 0x08, 0x09, 0x0F, 0x07, 0x08, 0x08, 0x03, 
    0x07, 0x03, 0x07, 0x08, 0x03, 0x06, 0x07, 0x05, 0x07, 0x06, 
    0x05, 0x07, 0x07, 0x02, 0x03, 0x07, 0x02, 0x0A, 0x07, 0x07, 
    0x07, 0x07, 0x05, 0x04, 0x05, 0x07, 0x08, 0x0C, 0x07, 0x08, 
    0x04, 0x04, 0x02, 0x04, 0x07, 0x08, 
    
    // font data
    0xFE, 0xFE, 0x1A, 0x1A, // 33
    0x1E, 0x1E, 0x00, 0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x20, 0xA0, 0xFC, 0x7C, 0xA0, 0xFC, 0x7C, 0x20, 0x02, 0x1E, 0x1E, 0x02, 0x1E, 0x1E, 0x02, 0x02, // 35
    0x38, 0x7C, 0xEC, 0xCF, 0xCF, 0x8C, 0x18, 0x0C, 0x18, 0x78, 0x78, 0x1A, 0x1E, 0x0E, // 36
    0x38, 0x7C, 0x44, 0x7C, 0xB8, 0xC0, 0x70, 0xB8, 0x8C, 0x84, 0x00, 0x00, 0x10, 0x18, 0x0E, 0x06, 0x00, 0x0E, 0x1E, 0x10, 0x1E, 0x0E, // 37
    0x18, 0xD8, 0xF8, 0x30, 0x78, 0xD8, 0x98, 0x98, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x1C, 0x3E, 0x32, 0x32, 0x3E, 0x1C, 0x00, // 38
    0x1E, 0x1E, 0x00, 0x00, // 39
    0xE0, 0xFC, 0x1E, 0x02, 0x0E, 0x7E, 0xF0, 0x80, // 40
    0x02, 0x1E, 0xFC, 0xE0, 0x80, 0xF0, 0x7E, 0x0E, // 41
    0x24, 0x18, 0x7E, 0x18, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0xC0, 0xC0, 0xC0, 0xF8, 0xF8, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x00, 0x40, 0x78, 0x38, // 44
    0x80, 0x80, 0x80, 0x02, 0x02, 0x02, // 45
    0x18, 0x18, 0x00, 0x00, // 46
    0x00, 0x00, 0x80, 0xF0, 0x7C, 0x0F, 0x03, 0x60, 0x78, 0x1E, 0x06, 0x00, 0x00, 0x00, // 47
    0xF0, 0xF8, 0x18, 0x18, 0x18, 0xF8, 0xF0, 0x1E, 0x3E, 0x30, 0x30, 0x30, 0x3E, 0x1E, // 48
    0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x00, 0x00, 0x3E, 0x3E, 0x18, 0x18, // 49
    0x18, 0x18, 0x98, 0xD8, 0x78, 0x38, 0x18, 0x1C, 0x3E, 0x32, 0x30, 0x30, 0x30, 0x18, // 50
    0xF0, 0xF8, 0x98, 0x98, 0x98, 0x98, 0x30, 0x1C, 0x3E, 0x32, 0x32, 0x32, 0x32, 0x18, // 51
    0x60, 0xF8, 0xF8, 0x60, 0x60, 0xE0, 0xE0, 0x00, 0x3E, 0x3E, 0x18, 0x1E, 0x06, 0x00, // 52
    0xF0, 0xF8, 0x98, 0x98, 0x98, 0x98, 0xB0, 0x30, 0x32, 0x32, 0x32, 0x32, 0x3E, 0x3E, // 53
    0xF0, 0xF8, 0x98, 0x98, 0x98, 0xF8, 0xF0, 0x30, 0x32, 0x32, 0x32, 0x38, 0x1E, 0x0E, // 54
    0x00, 0x00, 0x80, 0xE0, 0x78, 0x18, 0x00, 0x30, 0x3C, 0x3E, 0x32, 0x30, 0x30, 0x30, // 55
    0x70, 0xF8, 0x98, 0x98, 0x98, 0xF8, 0x70, 0x1C, 0x3E, 0x32, 0x32, 0x32, 0x3E, 0x1C, // 56
    0xE0, 0xF0, 0x38, 0x98, 0x98, 0x98, 0x18, 0x1E, 0x3E, 0x32, 0x32, 0x32, 0x3E, 0x1E, // 57
    0x18, 0x18, 0x06, 0x06, // 58
    0x00, 0x60, 0x60, 0x40, 0x78, 0x38, // 59
    0x30, 0x30, 0x60, 0x60, 0xC0, 0xC0, 0x80, 0x18, 0x18, 0x0C, 0x0C, 0x06, 0x06, 0x02, // 60
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, // 61
    0x80, 0xC0, 0xC0, 0x60, 0x60, 0x30, 0x30, 0x02, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18, // 62
    0x0C, 0x06, 0xC6, 0xC6, 0x7E, 0x3C, 0x00, 0x00, 0x1A, 0x1A, 0x00, 0x00, // 63
    0xC0, 0xF0, 0x38, 0xD8, 0xEC, 0x6C, 0xEC, 0xEC, 0x6C, 0x1C, 0xF8, 0xF0, 0x0E, 0x3E, 0x30, 0x66, 0x6E, 0x6C, 0x66, 0x6E, 0x6C, 0x0C, 0x06, 0x02, // 64
    0x18, 0xF8, 0xE0, 0x60, 0x60, 0x60, 0x60, 0xE0, 0xF8, 0x18, 0x00, 0x00, 0x06, 0x1E, 0x38, 0x38, 0x1E, 0x06, 0x00, 0x00, // 65
    0xF0, 0xF8, 0x98, 0x98, 0x98, 0xF8, 0xF8, 0x1C, 0x3E, 0x32, 0x32, 0x32, 0x3E, 0x3E, // 66
    0x30, 0x18, 0x18, 0x18, 0x38, 0xF0, 0xE0, 0x18, 0x30, 0x30, 0x30, 0x38, 0x1E, 0x0E, // 67
    0xE0, 0xF0, 0x38, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x0E, 0x1E, 0x38, 0x30, 0x30, 0x30, 0x3E, 0x3E, // 68
    0x18, 0x98, 0x98, 0x98, 0xF8, 0xF8, 0x30, 0x32, 0x32, 0x32, 0x3E, 0x3E, // 69
    0x00, 0x80, 0x80, 0x80, 0xF8, 0xF8, 0x30, 0x32, 0x32, 0x32, 0x3E, 0x3E, // 70
    0xF0, 0xF8, 0x98, 0x98, 0x18, 0x38, 0xF0, 0xE0, 0x1A, 0x32, 0x32, 0x32, 0x30, 0x38, 0x1E, 0x0E, // 71
    0xF8, 0xF8, 0x80, 0x80, 0x80, 0x80, 0xF8, 0xF8, 0x3E, 0x3E, 0x02, 0x02, 0x02, 0x02, 0x3E, 0x3E, // 72
    0xF8, 0xF8, 0x3E, 0x3E, // 73
    0xF0, 0xF8, 0x18, 0x18, 0x3E, 0x3E, 0x00, 0x00, // 74
    0x18, 0x38, 0x70, 0xE0, 0xC0, 0x80, 0xF8, 0xF8, 0x30, 0x38, 0x1C, 0x0E, 0x06, 0x02, 0x3E, 0x3E, // 75
    0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x3E, // 76
    0xF8, 0xF8, 0x00, 0x80, 0xE0, 0x78, 0x78, 0xE0, 0x80, 0x00, 0xF8, 0xF8, 0x3E, 0x3E, 0x38, 0x1E, 0x06, 0x00, 0x00, 0x06, 0x1E, 0x38, 0x3E, 0x3E, // 77
    0xF8, 0xF8, 0x38, 0xF0, 0xC0, 0x00, 0x00, 0xF8, 0xF8, 0x3E, 0x3E, 0x00, 0x00, 0x06, 0x1E, 0x38, 0x3E, 0x3E, // 78
    0xE0, 0xF0, 0x38, 0x18, 0x18, 0x18, 0x38, 0xF0, 0xE0, 0x0E, 0x1E, 0x38, 0x30, 0x30, 0x30, 0x38, 0x1E, 0x0E, // 79
    0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xF8, 0xF8, 0x1E, 0x3E, 0x30, 0x30, 0x30, 0x3E, 0x3E, // 80
    0x06, 0xEE, 0xFC, 0x38, 0x18, 0x18, 0x18, 0x38, 0xF0, 0xE0, 0x00, 0x0E, 0x1E, 0x38, 0x30, 0x30, 0x30, 0x38, 0x1E, 0x0E, // 81
    0x18, 0x78, 0xE0, 0x80, 0x80, 0xF8, 0xF8, 0x1C, 0x3E, 0x32, 0x32, 0x32, 0x3E, 0x3E, // 82
    0xF0, 0xF8, 0x98, 0x98, 0x98, 0x30, 0x18, 0x32, 0x32, 0x32, 0x3E, 0x1E, // 83
    0x00, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x3E, 0x3E, 0x30, 0x30, 0x30, // 84
    0xE0, 0xF0, 0x38, 0x18, 0x18, 0x38, 0xF0, 0xE0, 0x3E, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x3E, // 85
    0x00, 0x00, 0xE0, 0xF8, 0x18, 0xF8, 0xE0, 0x00, 0x00, 0x30, 0x3E, 0x0E, 0x00, 0x00, 0x00, 0x0E, 0x3E, 0x30, // 86
    0x00, 0x00, 0xE0, 0xF8, 0x78, 0xE0, 0x80, 0x00, 0x80, 0xE0, 0x78, 0xF8, 0xE0, 0x00, 0x00, 0x30, 0x3E, 0x0E, 0x00, 0x00, 0x06, 0x1E, 0x38, 0x1E, 0x06, 0x00, 0x00, 0x0E, 0x3E, 0x30, // 87
    0x18, 0x78, 0xE0, 0x80, 0xE0, 0x78, 0x18, 0x30, 0x3C, 0x0E, 0x02, 0x0E, 0x3C, 0x30, // 88
    0x00, 0x00, 0x80, 0xF8, 0xF8, 0x80, 0x00, 0x00, 0x30, 0x3C, 0x0E, 0x02, 0x02, 0x0E, 0x3C, 0x30, // 89
    0x18, 0x18, 0x18, 0x98, 0xD8, 0xF8, 0x78, 0x38, 0x38, 0x3C, 0x3E, 0x36, 0x32, 0x30, 0x30, 0x30, // 90
    0xFE, 0xFE, 0x06, 0xFE, 0xFE, 0xC0, // 91
    0x03, 0x1F, 0x7C, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1E, 0x78, 0x60, // 92
    0x06, 0xFE, 0xFE, 0xC0, 0xFE, 0xFE, // 93
    0xC0, 0xF0, 0x3C, 0x0C, 0x3C, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, // 95
    0x02, 0x06, 0x0C, 0x00, 0x00, 0x00, // 96
    0xF8, 0xF8, 0x58, 0x58, 0x78, 0x30, 0x02, 0x06, 0x06, 0x06, 0x06, 0x06, // 97
    0xF0, 0xF8, 0x18, 0x18, 0x10, 0xF8, 0xF8, 0x02, 0x06, 0x06, 0x06, 0x02, 0x7E, 0x7E, // 98
    0x18, 0x18, 0x18, 0xF8, 0xF0, 0x06, 0x06, 0x06, 0x06, 0x02, // 99
    0xF8, 0xF8, 0x10, 0x18, 0x18, 0xF8, 0xF0, 0x7E, 0x7E, 0x02, 0x06, 0x06, 0x06, 0x02, // 100
    0xD8, 0xD8, 0x58, 0x58, 0xF8, 0xF0, 0x02, 0x06, 0x06, 0x06, 0x06, 0x02, // 101
    0x00, 0x00, 0xF8, 0xF8, 0x00, 0x66, 0x66, 0x7E, 0x3E, 0x06, // 102
    0x06, 0x8F, 0xC9, 0x49, 0x49, 0xFF, 0x96, 0x08, 0x0E, 0x0E, 0x08, 0x08, 0x0E, 0x06, // 103
    0xF8, 0xF8, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x02, 0x06, 0x06, 0x06, 0x02, 0x7E, 0x7E, // 104
    0xF8, 0xF8, 0x36, 0x36, // 105
    0xFE, 0xFF, 0x03, 0x36, 0x36, 0x00, // 106
    0x08, 0x18, 0xB0, 0xE0, 0x40, 0xF8, 0xF8, 0x04, 0x06, 0x02, 0x00, 0x00, 0x7E, 0x7E, // 107
    0xF8, 0xF8, 0x7E, 0x7E, // 108
    0xF8, 0xF8, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0xF8, 0xF8, 0x02, 0x06, 0x06, 0x06, 0x02, 0x06, 0x06, 0x02, 0x06, 0x06, // 109
    0xF8, 0xF8, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x02, 0x06, 0x06, 0x06, 0x02, 0x06, 0x06, // 110
    0xF0, 0xF8, 0x18, 0x18, 0x18, 0xF8, 0xF0, 0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 0x02, // 111
    0xF0, 0xF8, 0x18, 0x18, 0x10, 0xFF, 0xFF, 0x02, 0x06, 0x06, 0x06, 0x02, 0x06, 0x06, // 112
    0xFF, 0xFF, 0x10, 0x18, 0x18, 0xF8, 0xF0, 0x06, 0x06, 0x02, 0x06, 0x06, 0x06, 0x02, // 113
    0x00, 0x00, 0x00, 0xF8, 0xF8, 0x06, 0x06, 0x02, 0x06, 0x06, // 114
    0x30, 0x78, 0xD8, 0x98, 0x06, 0x06, 0x06, 0x02, // 115
    0x18, 0x18, 0xF8, 0xF0, 0x00, 0x06, 0x06, 0x1E, 0x1E, 0x06, // 116
    0xF8, 0xF8, 0x10, 0x18, 0x18, 0xF8, 0xF0, 0x06, 0x06, 0x00, 0x00, 0x00, 0x06, 0x06, // 117
    0x00, 0xC0, 0xF0, 0x38, 0x38, 0xF0, 0xC0, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, // 118
    0x00, 0xC0, 0xF0, 0x38, 0xF8, 0xC0, 0xC0, 0xF8, 0x38, 0xF0, 0xC0, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x06, 0x06, // 119
    0x08, 0xB8, 0xF0, 0x40, 0xF0, 0xB8, 0x08, 0x04, 0x06, 0x02, 0x00, 0x02, 0x06, 0x04, // 120
    0x00, 0xC0, 0xF0, 0x3C, 0x3F, 0xF3, 0xC0, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, // 121
    0x98, 0xD8, 0x78, 0x38, 0x06, 0x06, 0x06, 0x06, // 122
    0x80, 0xFC, 0x7E, 0x06, 0x02, 0x7E, 0xFC, 0xC0, // 123
    0xFE, 0xFE, 0xFE, 0xFE, // 124
    0x06, 0x7E, 0xFC, 0x80, 0xC0, 0xFC, 0x7E, 0x02, // 125
    0x70, 0x78, 0x18, 0x30, 0x60, 0x78, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFC, 0x04, 0x14, 0x14, 0xF4, 0x64, 0x04, 0xFC, 0x1E, 0x10, 0x10, 0x16, 0x16, 0x10, 0x10, 0x1E // 127
    
};

#endif
