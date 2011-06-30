//Base Station
//File: small.h
//Small font
//Copyright C. Au and T. Zhang, 2010

/*
 *
 * small
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : small.h
 * Date                : 08.09.2010
 * Font size in bytes  : 5030
 * Font width          : 10
 * Font height         : 11
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

#ifndef SMALL_H
#define SMALL_H

#define SMALL_WIDTH 10
#define SMALL_HEIGHT 11

static uint8_t small[] PROGMEM = {
    0x13, 0xA6, // size
    0x0A, // width
    0x0B, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x01, 0x03, 0x06, 0x05, 0x08, 0x07, 0x01, 0x03, 0x03, 
    0x03, 0x05, 0x02, 0x04, 0x01, 0x03, 0x05, 0x03, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x01, 0x02, 0x05, 0x05, 
    0x05, 0x05, 0x09, 0x07, 0x05, 0x06, 0x06, 0x05, 0x05, 0x07, 
    0x06, 0x01, 0x05, 0x06, 0x04, 0x07, 0x06, 0x07, 0x05, 0x07, 
    0x07, 0x05, 0x07, 0x06, 0x07, 0x09, 0x07, 0x07, 0x06, 0x02, 
    0x03, 0x02, 0x05, 0x06, 0x02, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x03, 0x05, 0x05, 0x01, 0x02, 0x05, 0x01, 0x07, 0x05, 0x05, 
    0x05, 0x05, 0x03, 0x05, 0x02, 0x05, 0x05, 0x07, 0x05, 0x05, 
    0x05, 0x03, 0x01, 0x03, 0x05, 0x09, 
    
    // font data
    0x7E, 0x20, // 33
    0x20, 0xA0, 0x60, 0x60, 0x80, 0x40, // 34
    0x48, 0xE8, 0x5E, 0xE8, 0x5E, 0x48, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, // 35
    0x8C, 0x12, 0xFF, 0x22, 0xC4, 0x00, 0x20, 0x60, 0x20, 0x00, // 36
    0x0C, 0x12, 0xCC, 0x20, 0x10, 0xCC, 0x22, 0xC0, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, // 37
    0x04, 0x38, 0x98, 0x64, 0x44, 0xA4, 0x18, 0x00, 0x00, 0x20, 0x40, 0x40, 0x20, 0x00, // 38
    0x0E, 0x00, // 39
    0xF8, 0x04, 0x02, 0x20, 0x40, 0x80, // 40
    0x02, 0x04, 0xF8, 0x80, 0x40, 0x20, // 41
    0x14, 0x0E, 0x14, 0x00, 0x00, 0x00, // 42
    0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x80, 0x60, // 44
    0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, // 45
    0x04, 0x00, // 46
    0x80, 0x78, 0x06, 0x20, 0x00, 0x00, // 47
    0xF8, 0x04, 0x04, 0x04, 0xF8, 0x20, 0x40, 0x40, 0x40, 0x20, // 48
    0xFC, 0x00, 0x80, 0x60, 0x20, 0x00, // 49
    0xC4, 0x24, 0x14, 0x0C, 0x04, 0x20, 0x40, 0x40, 0x40, 0x20, // 50
    0xB8, 0x44, 0x44, 0x04, 0x08, 0x20, 0x40, 0x40, 0x40, 0x20, // 51
    0x10, 0xFC, 0x10, 0xD0, 0x30, 0x00, 0x60, 0x20, 0x00, 0x00, // 52
    0x38, 0x44, 0x44, 0x44, 0xE8, 0x40, 0x40, 0x40, 0x60, 0x00, // 53
    0x38, 0x44, 0x44, 0x44, 0xF8, 0x20, 0x40, 0x40, 0x40, 0x20, // 54
    0x00, 0xC0, 0x30, 0x0C, 0x00, 0x60, 0x40, 0x40, 0x40, 0x40, // 55
    0xB8, 0x44, 0x44, 0x44, 0xB8, 0x20, 0x40, 0x40, 0x40, 0x20, // 56
    0xF8, 0x24, 0x24, 0x24, 0xC8, 0x20, 0x40, 0x40, 0x40, 0x20, // 57
    0x84, 0x00, // 58
    0x00, 0x08, 0x80, 0x60, // 59
    0x88, 0x88, 0x50, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x20, 0x50, 0x50, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x04, 0x02, 0x62, 0x12, 0x0C, 0x00, 0x00, 0x20, 0x00, 0x00, // 63
    0xF8, 0x04, 0xF2, 0x0A, 0x0A, 0xF2, 0x1A, 0x84, 0x78, 0x20, 0x40, 0xC0, 0xA0, 0xA0, 0xA0, 0xA0, 0x80, 0x40, // 64
    0x0C, 0x30, 0xD0, 0x10, 0xD0, 0x30, 0x0C, 0x00, 0x00, 0x20, 0x40, 0x20, 0x00, 0x00, // 65
    0xB8, 0x44, 0x44, 0x44, 0xFC, 0x20, 0x40, 0x40, 0x40, 0x60, // 66
    0x08, 0x04, 0x04, 0x04, 0x08, 0xF0, 0x20, 0x40, 0x40, 0x40, 0x20, 0x00, // 67
    0xF0, 0x08, 0x04, 0x04, 0x04, 0xFC, 0x00, 0x20, 0x40, 0x40, 0x40, 0x60, // 68
    0x44, 0x44, 0x44, 0x44, 0xFC, 0x40, 0x40, 0x40, 0x40, 0x60, // 69
    0x00, 0x40, 0x40, 0x40, 0xFC, 0x40, 0x40, 0x40, 0x40, 0x60, // 70
    0x38, 0x24, 0x24, 0x04, 0x04, 0x08, 0xF0, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x00, // 71
    0xFC, 0x40, 0x40, 0x40, 0x40, 0xFC, 0x60, 0x00, 0x00, 0x00, 0x00, 0x60, // 72
    0xFC, 0x60, // 73
    0xF8, 0x04, 0x04, 0x04, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, // 74
    0x04, 0x08, 0x90, 0x60, 0x20, 0xFC, 0x40, 0x20, 0x00, 0x00, 0x00, 0x60, // 75
    0x04, 0x04, 0x04, 0xFC, 0x00, 0x00, 0x00, 0x60, // 76
    0xFC, 0x80, 0x70, 0x0C, 0x70, 0x80, 0xFC, 0x60, 0x20, 0x00, 0x00, 0x00, 0x20, 0x60, // 77
    0xFC, 0x08, 0x30, 0xC0, 0x00, 0xFC, 0x60, 0x00, 0x00, 0x00, 0x20, 0x60, // 78
    0xF0, 0x08, 0x04, 0x04, 0x04, 0x08, 0xF0, 0x00, 0x20, 0x40, 0x40, 0x40, 0x20, 0x00, // 79
    0xC0, 0x20, 0x20, 0x20, 0xFC, 0x20, 0x40, 0x40, 0x40, 0x60, // 80
    0xF2, 0x0C, 0x14, 0x04, 0x04, 0x08, 0xF0, 0x00, 0x20, 0x40, 0x40, 0x40, 0x20, 0x00, // 81
    0x04, 0xC8, 0x30, 0x20, 0x20, 0x20, 0xFC, 0x00, 0x20, 0x40, 0x40, 0x40, 0x40, 0x60, // 82
    0x18, 0x24, 0x44, 0x44, 0x88, 0x20, 0x40, 0x40, 0x40, 0x20, // 83
    0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x60, 0x40, 0x40, 0x40, // 84
    0xF8, 0x04, 0x04, 0x04, 0x04, 0xF8, 0x60, 0x00, 0x00, 0x00, 0x00, 0x60, // 85
    0x00, 0xC0, 0x38, 0x04, 0x38, 0xC0, 0x00, 0x40, 0x20, 0x00, 0x00, 0x00, 0x20, 0x40, // 86
    0x00, 0xF8, 0x04, 0xF8, 0x00, 0xF8, 0x04, 0xF8, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, // 87
    0x04, 0x08, 0x90, 0x60, 0x90, 0x08, 0x04, 0x40, 0x20, 0x00, 0x00, 0x00, 0x20, 0x40, // 88
    0x00, 0x80, 0x40, 0x3C, 0x40, 0x80, 0x00, 0x40, 0x20, 0x00, 0x00, 0x00, 0x20, 0x40, // 89
    0x04, 0x84, 0x44, 0x24, 0x14, 0x0C, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, // 90
    0xFE, 0x02, 0xE0, 0x80, // 91
    0x06, 0x78, 0x80, 0x00, 0x00, 0x20, // 92
    0x02, 0xFE, 0x80, 0xE0, // 93
    0x10, 0x0C, 0x02, 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x01, 0x02, 0x00, 0x00, // 96
    0x7C, 0xA8, 0xA4, 0xA4, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0x78, 0x84, 0x84, 0x48, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x60, // 98
    0x48, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, // 99
    0xFC, 0x48, 0x84, 0x84, 0x78, 0x60, 0x00, 0x00, 0x00, 0x00, // 100
    0x68, 0xA4, 0xA4, 0xA4, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0x00, 0x80, 0xFC, 0x40, 0x40, 0x20, // 102
    0xFE, 0x49, 0x85, 0x85, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, // 103
    0x7C, 0x80, 0x80, 0x40, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x60, // 104
    0xFC, 0x40, // 105
    0xFE, 0x01, 0x40, 0x00, // 106
    0x84, 0x48, 0x30, 0x10, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x60, // 107
    0xFC, 0x60, // 108
    0x7C, 0x80, 0x80, 0x7C, 0x80, 0x80, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0x7C, 0x80, 0x80, 0x40, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x78, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0x78, 0x84, 0x84, 0x48, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, // 112
    0xFF, 0x48, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, // 113
    0x80, 0xC0, 0xFC, 0x00, 0x00, 0x00, // 114
    0x48, 0x94, 0xA4, 0xA4, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, // 115
    0x84, 0xF8, 0x00, 0x60, // 116
    0xFC, 0x08, 0x04, 0x04, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0xC0, 0x38, 0x04, 0x38, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0xF0, 0x0C, 0x70, 0x80, 0x70, 0x0C, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0x84, 0x48, 0x30, 0x48, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0xC0, 0x38, 0x06, 0x3D, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, // 121
    0x84, 0xC4, 0xA4, 0x94, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, // 122
    0x40, 0xBC, 0x02, 0x00, 0x60, 0x80, // 123
    0xFE, 0xE0, // 124
    0x02, 0xBC, 0x40, 0x80, 0x60, 0x00, // 125
    0x20, 0x10, 0x30, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFE, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFE, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 // 127
    
};

#endif
