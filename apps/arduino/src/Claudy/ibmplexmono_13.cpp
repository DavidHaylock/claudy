/*******************************************************************************
 * Size: 13 px
 * Bpp: 1
 * Opts: --font IBMPlexMono-Regular.ttf -r 0x20-0x7E -r 0xB7 --size 13 --bpp 1 --no-compress --format lvgl --force-fast-kern-format -o ibmplexmono_13.c --lv-include lvgl.h
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef IBMPLEXMONO_13
#define IBMPLEXMONO_13 1
#endif

#if IBMPLEXMONO_13

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xaa, 0xa3, 0xc0,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x14, 0x14, 0x14, 0x67, 0x24, 0xee, 0x28, 0x28,
    0x48,

    /* U+0024 "$" */
    0x10, 0xcd, 0xe4, 0x91, 0xc1, 0xc5, 0x16, 0x57,
    0x84, 0x10,

    /* U+0025 "%" */
    0x63, 0x2a, 0x63, 0x0, 0xc6, 0x54, 0xa9, 0x8c,

    /* U+0026 "&" */
    0x38, 0x91, 0x2, 0x6, 0x72, 0xa3, 0x46, 0x76,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x24, 0x48, 0x88, 0x88, 0x84, 0x42,

    /* U+0029 ")" */
    0x42, 0x21, 0x11, 0x11, 0x12, 0x24,

    /* U+002A "*" */
    0x10, 0x23, 0x59, 0xc2, 0x8d, 0x80, 0x0,

    /* U+002B "+" */
    0x10, 0x23, 0xf8, 0x81, 0x2, 0x0,

    /* U+002C "," */
    0xe8,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x8, 0x20, 0x84, 0x10, 0x42, 0x8, 0x41, 0x4,
    0x20,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x96, 0x18, 0x52, 0x78,

    /* U+0031 "1" */
    0x31, 0x49, 0x4, 0x10, 0x41, 0x4, 0xfc,

    /* U+0032 "2" */
    0x39, 0x10, 0x41, 0x8, 0x42, 0x10, 0xfc,

    /* U+0033 "3" */
    0x79, 0x10, 0x4e, 0xc, 0x10, 0x73, 0x78,

    /* U+0034 "4" */
    0xc, 0x28, 0x51, 0x24, 0x48, 0xbf, 0x82, 0x4,

    /* U+0035 "5" */
    0xff, 0x8, 0x2e, 0xcc, 0x10, 0x73, 0x78,

    /* U+0036 "6" */
    0x10, 0x84, 0x2e, 0xce, 0x18, 0x73, 0x78,

    /* U+0037 "7" */
    0xfe, 0x18, 0x82, 0x18, 0x43, 0x8, 0x20,

    /* U+0038 "8" */
    0x7a, 0x18, 0x5e, 0xce, 0x18, 0x73, 0x78,

    /* U+0039 "9" */
    0x7b, 0x38, 0x61, 0xcd, 0xd0, 0x84, 0x20,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0xf0, 0xe, 0x80,

    /* U+003C "<" */
    0x4, 0x62, 0x30, 0xc0, 0xc1, 0x81,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0x3, 0x3, 0x8, 0xcc, 0x0,

    /* U+003F "?" */
    0x76, 0x42, 0x13, 0x10, 0x6, 0x30,

    /* U+0040 "@" */
    0x79, 0x19, 0xe9, 0xa6, 0x9a, 0x67, 0x41, 0xe0,

    /* U+0041 "A" */
    0x18, 0x30, 0xa1, 0x22, 0x4f, 0x90, 0xa1, 0x42,

    /* U+0042 "B" */
    0xfa, 0x18, 0x61, 0xfa, 0x18, 0x61, 0xf8,

    /* U+0043 "C" */
    0x79, 0x38, 0x20, 0x82, 0x8, 0x13, 0x78,

    /* U+0044 "D" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0x62, 0xf8,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0xfc,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x80,

    /* U+0047 "G" */
    0x79, 0x18, 0x20, 0x9e, 0x18, 0x53, 0x74,

    /* U+0048 "H" */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x84,

    /* U+0049 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+004A "J" */
    0x78, 0x42, 0x10, 0x84, 0x31, 0x70,

    /* U+004B "K" */
    0x8e, 0x29, 0x28, 0xe3, 0x49, 0xa2, 0x84,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0xf8,

    /* U+004D "M" */
    0xcf, 0x3c, 0xed, 0xb6, 0x98, 0x61, 0x84,

    /* U+004E "N" */
    0xc7, 0x1e, 0x69, 0xb6, 0x59, 0xe3, 0x8c,

    /* U+004F "O" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x52, 0x78,

    /* U+0050 "P" */
    0xfa, 0x18, 0x61, 0xfa, 0x8, 0x20, 0x80,

    /* U+0051 "Q" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70, 0x40, 0xe0,

    /* U+0052 "R" */
    0xfa, 0x18, 0x61, 0xfa, 0x49, 0xa2, 0x84,

    /* U+0053 "S" */
    0x7a, 0x18, 0x30, 0x38, 0x10, 0x61, 0x78,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0x78,

    /* U+0056 "V" */
    0x42, 0x85, 0x19, 0x22, 0x44, 0x8a, 0xc, 0x18,

    /* U+0057 "W" */
    0x86, 0x1b, 0x6d, 0xb6, 0xdc, 0xf3, 0xcc,

    /* U+0058 "X" */
    0x42, 0xc8, 0x90, 0xc1, 0x83, 0x9, 0x23, 0x42,

    /* U+0059 "Y" */
    0x82, 0x89, 0x11, 0x43, 0x82, 0x4, 0x8, 0x10,

    /* U+005A "Z" */
    0xfe, 0x8, 0x20, 0xc1, 0x4, 0x10, 0x60, 0xfe,

    /* U+005B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x8f,

    /* U+005C "\\" */
    0x81, 0x4, 0x10, 0x20, 0x81, 0x4, 0x10, 0x20,
    0x82,

    /* U+005D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x1f,

    /* U+005E "^" */
    0x31, 0xc4, 0xa2, 0x84,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x50,

    /* U+0061 "a" */
    0x72, 0x20, 0x9e, 0x8a, 0x27, 0xc0,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x8f, 0xe0,

    /* U+0063 "c" */
    0x7b, 0x28, 0x20, 0x83, 0x27, 0x80,

    /* U+0064 "d" */
    0x4, 0x10, 0x5d, 0xce, 0x18, 0x61, 0xc5, 0xf0,

    /* U+0065 "e" */
    0x7b, 0x38, 0x7f, 0x83, 0x17, 0x80,

    /* U+0066 "f" */
    0x3c, 0x82, 0x3f, 0x20, 0x82, 0x8, 0x23, 0xe0,

    /* U+0067 "g" */
    0x5, 0xe8, 0x61, 0x85, 0xec, 0x1f, 0x86, 0x17,
    0x80,

    /* U+0068 "h" */
    0x84, 0x21, 0x6c, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0069 "i" */
    0x20, 0x1, 0xc2, 0x10, 0x84, 0x27, 0xc0,

    /* U+006A "j" */
    0x10, 0xf, 0x11, 0x11, 0x11, 0x11, 0xf0,

    /* U+006B "k" */
    0x82, 0x8, 0x22, 0x92, 0x8f, 0x24, 0x8a, 0x30,

    /* U+006C "l" */
    0xe1, 0x8, 0x42, 0x10, 0x84, 0x27, 0xc0,

    /* U+006D "m" */
    0xff, 0x26, 0x4c, 0x99, 0x32, 0x64, 0x80,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x3f, 0xa0, 0x82, 0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x87, 0x17, 0xc1, 0x4, 0x10,

    /* U+0072 "r" */
    0xec, 0xc2, 0x8, 0x20, 0x8f, 0xc0,

    /* U+0073 "s" */
    0x7a, 0x18, 0x1e, 0x6, 0x17, 0x80,

    /* U+0074 "t" */
    0x20, 0x8f, 0xc8, 0x20, 0x82, 0x8, 0x3c,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xc5, 0xe0,

    /* U+0076 "v" */
    0x86, 0x24, 0x92, 0x50, 0xc3, 0x0,

    /* U+0077 "w" */
    0x9a, 0xb5, 0x6b, 0x56, 0xac, 0xd9, 0x0,

    /* U+0078 "x" */
    0x8d, 0x23, 0xc, 0x31, 0x28, 0xc0,

    /* U+0079 "y" */
    0x86, 0x34, 0x92, 0x50, 0xc3, 0x8, 0x23, 0x0,

    /* U+007A "z" */
    0xfc, 0x21, 0x8, 0x63, 0xf, 0xc0,

    /* U+007B "{" */
    0x39, 0x8, 0x41, 0xb, 0x82, 0x11, 0x8, 0x70,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0xe1, 0x8, 0x44, 0x20, 0xe8, 0x41, 0x9, 0xc0,

    /* U+007E "~" */
    0xe6, 0x99, 0x80,

    /* U+00B7 "·" */
    0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 125, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 125, .box_w = 2, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 125, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 125, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 25, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 125, .box_w = 1, .box_h = 3, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 42, .adv_w = 125, .box_w = 4, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 48, .adv_w = 125, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 125, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 61, .adv_w = 125, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 67, .adv_w = 125, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 68, .adv_w = 125, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 69, .adv_w = 125, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 79, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 125, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 125, .box_w = 2, .box_h = 9, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 155, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 125, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 164, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 125, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 184, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 125, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 125, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 125, .box_w = 5, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 125, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 305, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 125, .box_w = 4, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 379, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 388, .adv_w = 125, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 394, .adv_w = 125, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 398, .adv_w = 125, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 399, .adv_w = 125, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 400, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 451, .adv_w = 125, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 125, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 125, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 472, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 125, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 125, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 125, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 513, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 521, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 125, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 125, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 572, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 125, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 586, .adv_w = 125, .box_w = 1, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 588, .adv_w = 125, .box_w = 5, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 596, .adv_w = 125, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 599, .adv_w = 125, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 183, .range_length = 1, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
extern const lv_font_t ibmplexmono_13 = {   /* explicit `extern`: a bare top-level `const` gets internal
                                               linkage in C++ (unlike C), which would hide this symbol
                                               from claude_face_v2.cpp's LV_FONT_DECLARE reference */
#else
lv_font_t ibmplexmono_13 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if IBMPLEXMONO_13*/

