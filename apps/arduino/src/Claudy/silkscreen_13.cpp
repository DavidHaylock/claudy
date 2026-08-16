/*******************************************************************************
 * Size: 13 px
 * Bpp: 1
 * Opts: --font silkscreen_regular.ttf -r 0x20-0x7E --size 13 --bpp 1 --no-compress --format lvgl --force-fast-kern-format -o out/fonts/silkscreen_13.c --lv-include lvgl.h
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef SILKSCREEN_13
#define SILKSCREEN_13 1
#endif

#if SILKSCREEN_13

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xc3,

    /* U+0022 "\"" */
    0xde, 0xf6,

    /* U+0023 "#" */
    0x6c, 0x6c, 0xff, 0x6c, 0x6c, 0xff, 0x6c, 0x6c,

    /* U+0024 "$" */
    0x18, 0x30, 0xf8, 0xc, 0x7, 0x2, 0x3, 0x9,
    0xf0, 0x81, 0x0,

    /* U+0025 "%" */
    0xe6, 0xe6, 0xe6, 0x18, 0x8, 0x67, 0x67, 0x67,

    /* U+0026 "&" */
    0x18, 0x30, 0xfa, 0xc, 0x7, 0x10, 0x60, 0x40,
    0x7c, 0x60, 0xc0,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x23, 0x6d, 0xb1,

    /* U+0029 ")" */
    0xc8, 0x92, 0x4e,

    /* U+002A "*" */
    0x18, 0x18, 0xd9, 0x3e, 0x5a, 0xd9, 0x18, 0x18,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0x38,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0xc, 0x30, 0xc8, 0x3, 0xc, 0x30,

    /* U+0030 "0" */
    0x38, 0x93, 0x1e, 0x3c, 0x78, 0xf1, 0x9c,

    /* U+0031 "1" */
    0xe3, 0x18, 0xc6, 0x31, 0x9f,

    /* U+0032 "2" */
    0xf8, 0x10, 0x19, 0xcc, 0x18, 0x30, 0x7f,

    /* U+0033 "3" */
    0xf8, 0x10, 0x19, 0xc0, 0x80, 0xc0, 0x7c,

    /* U+0034 "4" */
    0xd9, 0xb3, 0x67, 0xf1, 0x83, 0x6, 0xc,

    /* U+0035 "5" */
    0xff, 0x83, 0x7, 0xc0, 0x80, 0xc0, 0x7c,

    /* U+0036 "6" */
    0x39, 0x83, 0x6, 0xf, 0x98, 0xd2, 0x1c,

    /* U+0037 "7" */
    0xfe, 0xc, 0x18, 0x41, 0x6, 0xc, 0x18,

    /* U+0038 "8" */
    0x38, 0x93, 0x19, 0xc4, 0x98, 0xd2, 0x1c,

    /* U+0039 "9" */
    0x38, 0x93, 0x19, 0xf0, 0x60, 0xc1, 0x9c,

    /* U+003A ":" */
    0xc0, 0xc0,

    /* U+003B ";" */
    0x20, 0x11, 0x80,

    /* U+003C "<" */
    0xc, 0x2, 0x30, 0x40, 0x81, 0x3,

    /* U+003D "=" */
    0xf8, 0x0, 0xf, 0x80,

    /* U+003E ">" */
    0xc1, 0x2, 0x7, 0x0, 0x80, 0x30,

    /* U+003F "?" */
    0xf0, 0x10, 0x1b, 0x80, 0x0, 0x0, 0x30,

    /* U+0040 "@" */
    0x3e, 0x1a, 0xdb, 0xde, 0xc0, 0xc0, 0xc0, 0x3e,

    /* U+0041 "A" */
    0x38, 0x93, 0x1f, 0xfc, 0x78, 0xf1, 0xe3,

    /* U+0042 "B" */
    0xf9, 0x93, 0x1f, 0xfc, 0x78, 0xf1, 0xfc,

    /* U+0043 "C" */
    0x38, 0x13, 0x1e, 0xc, 0x18, 0xd0, 0x1c,

    /* U+0044 "D" */
    0xf9, 0x93, 0x1e, 0x3c, 0x78, 0xf1, 0xfc,

    /* U+0045 "E" */
    0xfe, 0x31, 0xfc, 0x63, 0x1f,

    /* U+0046 "F" */
    0xfe, 0x31, 0xfc, 0x63, 0x18,

    /* U+0047 "G" */
    0x3e, 0x3, 0x6, 0xfc, 0x78, 0xf1, 0x9c,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1f, 0xfc, 0x78, 0xf1, 0xe3,

    /* U+0049 "I" */
    0xff, 0xff,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x78, 0xd0, 0x1c,

    /* U+004B "K" */
    0xc7, 0x83, 0x67, 0xe, 0x1b, 0x32, 0x63,

    /* U+004C "L" */
    0xc6, 0x31, 0x8c, 0x63, 0x1f,

    /* U+004D "M" */
    0xc3, 0xc3, 0xe7, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+004E "N" */
    0xc3, 0xc3, 0xe3, 0xdb, 0xcb, 0xc7, 0xc3, 0xc3,

    /* U+004F "O" */
    0x38, 0x93, 0x1e, 0x3c, 0x78, 0xf1, 0x9c,

    /* U+0050 "P" */
    0xf9, 0x93, 0x1f, 0xcc, 0x18, 0x30, 0x60,

    /* U+0051 "Q" */
    0x38, 0x93, 0x1e, 0x3c, 0x78, 0xf1, 0x9c, 0x6,

    /* U+0052 "R" */
    0xf9, 0x93, 0x1f, 0xcd, 0x9b, 0x36, 0x63,

    /* U+0053 "S" */
    0x3e, 0x3, 0x1, 0xc0, 0x80, 0xc0, 0x7c,

    /* U+0054 "T" */
    0xfb, 0x18, 0xc6, 0x31, 0x8c,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xd0, 0x1c,

    /* U+0056 "V" */
    0xc1, 0xc1, 0xc1, 0x26, 0x26, 0x26, 0x20, 0x18,

    /* U+0057 "W" */
    0xc1, 0xd9, 0xd9, 0xd9, 0xd9, 0xd9, 0x48, 0x26,

    /* U+0058 "X" */
    0xc1, 0x42, 0x26, 0x18, 0x8, 0x26, 0x2, 0xc1,

    /* U+0059 "Y" */
    0xc1, 0x40, 0x26, 0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xfc, 0x30, 0xc8, 0xc3, 0xc, 0x3f,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0xc3, 0xc, 0x8, 0x10, 0x30, 0xc3,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x21, 0x4c, 0xc0,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xc8, 0x80,

    /* U+0061 "a" */
    0x38, 0x93, 0x1f, 0xfc, 0x78, 0xf1, 0xe3,

    /* U+0062 "b" */
    0xf9, 0x93, 0x1f, 0xfc, 0x78, 0xf1, 0xfc,

    /* U+0063 "c" */
    0x38, 0x13, 0x1e, 0xc, 0x18, 0xd0, 0x1c,

    /* U+0064 "d" */
    0xf9, 0x93, 0x1e, 0x3c, 0x78, 0xf1, 0xfc,

    /* U+0065 "e" */
    0xfe, 0x31, 0xfc, 0x63, 0x1f,

    /* U+0066 "f" */
    0xfe, 0x31, 0xfc, 0x63, 0x18,

    /* U+0067 "g" */
    0x3e, 0x3, 0x6, 0xfc, 0x78, 0xf1, 0x9c,

    /* U+0068 "h" */
    0xc7, 0x8f, 0x1f, 0xfc, 0x78, 0xf1, 0xe3,

    /* U+0069 "i" */
    0xff, 0xff,

    /* U+006A "j" */
    0x6, 0xc, 0x18, 0x30, 0x78, 0xd0, 0x1c,

    /* U+006B "k" */
    0xc7, 0x83, 0x67, 0xe, 0x1b, 0x32, 0x63,

    /* U+006C "l" */
    0xc6, 0x31, 0x8c, 0x63, 0x1f,

    /* U+006D "m" */
    0xc3, 0xc3, 0xe7, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+006E "n" */
    0xc3, 0xc3, 0xe3, 0xdb, 0xcb, 0xc7, 0xc3, 0xc3,

    /* U+006F "o" */
    0x38, 0x93, 0x1e, 0x3c, 0x78, 0xf1, 0x9c,

    /* U+0070 "p" */
    0xf9, 0x93, 0x1f, 0xcc, 0x18, 0x30, 0x60,

    /* U+0071 "q" */
    0x38, 0x93, 0x1e, 0x3c, 0x78, 0xf1, 0x9c, 0x6,

    /* U+0072 "r" */
    0xf9, 0x93, 0x1f, 0xcd, 0x9b, 0x36, 0x63,

    /* U+0073 "s" */
    0x3e, 0x3, 0x1, 0xc0, 0x80, 0xc0, 0x7c,

    /* U+0074 "t" */
    0xfb, 0x18, 0xc6, 0x31, 0x8c,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xd0, 0x1c,

    /* U+0076 "v" */
    0xc1, 0xc1, 0xc1, 0x26, 0x26, 0x26, 0x20, 0x18,

    /* U+0077 "w" */
    0xc1, 0xd9, 0xd9, 0xd9, 0xd9, 0xd9, 0x48, 0x26,

    /* U+0078 "x" */
    0xc1, 0x42, 0x26, 0x18, 0x8, 0x26, 0x2, 0xc1,

    /* U+0079 "y" */
    0xc1, 0x40, 0x26, 0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+007A "z" */
    0xfc, 0x30, 0xc8, 0xc3, 0xc, 0x3f,

    /* U+007B "{" */
    0x39, 0x9, 0x82, 0x10, 0x87,

    /* U+007C "|" */
    0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xf1, 0x8c, 0x13, 0x18, 0xde,

    /* U+007E "~" */
    0x26, 0xc3, 0x60
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 104, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 78, .box_w = 2, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 130, .box_w = 5, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 5, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 156, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 24, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 156, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 43, .adv_w = 78, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 44, .adv_w = 104, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 104, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 104, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 67, .adv_w = 130, .box_w = 5, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 68, .adv_w = 78, .box_w = 2, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 78, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 145, .adv_w = 104, .box_w = 3, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 130, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 158, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 78, .box_w = 2, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 156, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 290, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 104, .box_w = 4, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 104, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 130, .box_w = 6, .box_h = 3, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 371, .adv_w = 156, .box_w = 7, .box_h = 1, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 372, .adv_w = 104, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 374, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 78, .box_w = 2, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 156, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 485, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 182, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 78, .box_w = 2, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 557, .adv_w = 130, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 156, .box_w = 7, .box_h = 3, .ofs_x = 2, .ofs_y = 5}
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
    .cmap_num = 1,
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
extern const lv_font_t silkscreen_13 = {   /* explicit `extern`: a bare top-level `const` gets internal
                                               linkage in C++ (unlike C), which would hide this symbol
                                               from claude_face.cpp's LV_FONT_DECLARE reference */
#else
lv_font_t silkscreen_13 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if SILKSCREEN_13*/

