#include "../gfxfont.h"

const uint8_t dig_14_Bitmaps[] PROGMEM = {
    0xFC, 0x00, 0x7F, 0xBF, 0xFE, 0x1F, 0x87, 0xE1, 0xF8, 0x7E, 0x1F, 0x87,
    0xE1, 0xF8, 0x7E, 0x1F, 0x87, 0xFF, 0xDF, 0xE0, 0x38, 0x73, 0xE7, 0xC3,
    0x87, 0x0E, 0x1C, 0x38, 0x70, 0xE1, 0xCF, 0xFF, 0xC0, 0x7F, 0xBF, 0xFE,
    0x1C, 0x07, 0x01, 0xC0, 0xE0, 0xF0, 0xF0, 0x70, 0x38, 0x0E, 0x03, 0x80,
    0xFF, 0xFF, 0xF0, 0x7F, 0xBF, 0xFE, 0x1C, 0x07, 0x01, 0xC0, 0xE1, 0xF0,
    0x7E, 0x01, 0xC0, 0x70, 0x1F, 0x87, 0xFF, 0xDF, 0xE0, 0x01, 0x80, 0xE0,
    0x78, 0x3E, 0x1F, 0x8E, 0xE7, 0x3B, 0x8E, 0xE3, 0xBF, 0xFF, 0xFC, 0x0E,
    0x03, 0x80, 0xE0, 0xFF, 0xFF, 0xFE, 0x03, 0x80, 0xE0, 0x38, 0x0F, 0xFB,
    0xFF, 0x01, 0xC0, 0x70, 0x1F, 0x87, 0xFF, 0xDF, 0xE0, 0x3F, 0x9F, 0xEF,
    0x03, 0x80, 0xE0, 0x38, 0x0F, 0xFB, 0xFF, 0xE1, 0xF8, 0x7E, 0x1F, 0x87,
    0xFF, 0xDF, 0xE0, 0xFF, 0xFF, 0xFE, 0x1C, 0x07, 0x03, 0x80, 0xE0, 0x70,
    0x1C, 0x0E, 0x03, 0x81, 0xC0, 0x70, 0x38, 0x0E, 0x00, 0x7F, 0xBF, 0xFE,
    0x1F, 0x87, 0xE1, 0xF8, 0x77, 0xFB, 0xFF, 0xE1, 0xF8, 0x7E, 0x1F, 0x87,
    0xFF, 0xDF, 0xE0, 0x7F, 0xBF, 0xFE, 0x1F, 0x87, 0xE1, 0xF8, 0x7F, 0xFD,
    0xFF, 0x01, 0xC0, 0x70, 0x1F, 0x87, 0xFF, 0xDF, 0xE0};

const GFXglyph dig_14_Glyphs[] PROGMEM = {
    {0, 3, 2, 4, 0, -1},       // 0x2E '.'
    {0, 0, 0, 0, 0, 0},        // 0x2F '/'
    {2, 10, 14, 11, 0, -13},   // 0x30 '0'
    {20, 7, 14, 8, 0, -13},    // 0x31 '1'
    {33, 10, 14, 11, 0, -13},  // 0x32 '2'
    {51, 10, 14, 11, 0, -13},  // 0x33 '3'
    {69, 10, 14, 11, 0, -13},  // 0x34 '4'
    {87, 10, 14, 11, 0, -13},  // 0x35 '5'
    {105, 10, 14, 11, 0, -13}, // 0x36 '6'
    {123, 10, 14, 11, 0, -13}, // 0x37 '7'
    {141, 10, 14, 11, 0, -13}, // 0x38 '8'
    {159, 10, 14, 11, 0, -13}  // 0x39 '9'
};

const GFXfont dig_14 PROGMEM = {(uint8_t *)dig_14_Bitmaps,
                                (GFXglyph *)dig_14_Glyphs, 0x2E, 0x39, 14};
