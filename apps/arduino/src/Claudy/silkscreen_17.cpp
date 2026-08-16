/*******************************************************************************
 * Size: 17 px
 * Bpp: 1
 * Opts: --font Silkscreen-Regular.ttf -r 0x20-0x7E -r 0xB7 --size 17 --bpp 1 --no-compress --format lvgl --force-fast-kern-format -o silkscreen_17.c --lv-include lvgl.h
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef SILKSCREEN_17
#define SILKSCREEN_17 1
#endif

#if SILKSCREEN_17

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf0, 0x3c,

    /* U+0022 "\"" */
    0xcf, 0x3c, 0xf3,

    /* U+0023 "#" */
    0x33, 0x6, 0x63, 0xff, 0xff, 0xf3, 0x30, 0x66,
    0xc, 0xc7, 0xff, 0xff, 0xe6, 0x60, 0xcc, 0x0,

    /* U+0024 "$" */
    0xc, 0xc, 0x3f, 0x3f, 0xc0, 0xc0, 0x3c, 0x3c,
    0x4, 0x3, 0x3, 0xfc, 0xfc, 0x30, 0x30,

    /* U+0025 "%" */
    0xf3, 0x3c, 0xcf, 0x33, 0xcc, 0xc, 0x3, 0x0,
    0x40, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,

    /* U+0026 "&" */
    0xc, 0xc, 0x3f, 0x3f, 0xc0, 0xc0, 0x3c, 0x3c,
    0x40, 0xc0, 0xc0, 0x3f, 0x3f, 0xc, 0xc,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x33, 0xcc, 0xcc, 0xcc, 0x43, 0x30,

    /* U+0029 ")" */
    0xcc, 0x33, 0x33, 0x33, 0xc, 0xc0,

    /* U+002A "*" */
    0xc, 0x1, 0x83, 0x31, 0xe6, 0x33, 0xf0, 0x7e,
    0x13, 0x26, 0x63, 0xcc, 0x61, 0x80, 0x30, 0x0,

    /* U+002B "+" */
    0xc, 0x1, 0x80, 0x30, 0x6, 0xf, 0xff, 0xff,
    0xc3, 0x0, 0x60, 0xc, 0x1, 0x80, 0x30, 0x0,

    /* U+002C "," */
    0x33, 0xcc,

    /* U+002D "-" */
    0xff, 0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x30, 0xc3, 0x30, 0xc0, 0x30, 0xc3, 0xc,
    0x0,

    /* U+0030 "0" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x44, 0x3c, 0x3c,

    /* U+0031 "1" */
    0xf3, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x33, 0xff,
    0xc0,

    /* U+0032 "2" */
    0xfc, 0xfc, 0x3, 0x3, 0x3c, 0x3c, 0xc0, 0xc0,
    0xc0, 0xff, 0xff,

    /* U+0033 "3" */
    0xfc, 0xfc, 0x3, 0x3, 0x3c, 0x3c, 0x4, 0x3,
    0x3, 0xfc, 0xfc,

    /* U+0034 "4" */
    0xcc, 0x66, 0x33, 0x19, 0x8f, 0xff, 0xfc, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x0,

    /* U+0035 "5" */
    0xff, 0xff, 0xc0, 0xc0, 0xfc, 0xfc, 0x4, 0x3,
    0x3, 0xfc, 0xfc,

    /* U+0036 "6" */
    0x3c, 0x3c, 0x40, 0xc0, 0xc0, 0xfc, 0xfc, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0x3, 0x3, 0xc, 0xc, 0x10, 0x30,
    0x30, 0x30, 0x30,

    /* U+0038 "8" */
    0x3c, 0x3c, 0xc3, 0xc3, 0x3c, 0x3c, 0x44, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x3c, 0xc3, 0xc3, 0x3f, 0x3f, 0x3, 0x3,
    0x4, 0x3c, 0x3c,

    /* U+003A ":" */
    0xf0, 0xf0,

    /* U+003B ";" */
    0x33, 0x0, 0x3, 0x3c, 0xc0,

    /* U+003C "<" */
    0xc, 0x33, 0xc, 0xc3, 0x4, 0xc, 0x30, 0x30,
    0xc0,

    /* U+003D "=" */
    0xff, 0xf0, 0x0, 0xff, 0xf0,

    /* U+003E ">" */
    0xc3, 0x3, 0xc, 0xc, 0x30, 0xc, 0x33, 0xc,
    0x0,

    /* U+003F "?" */
    0xfc, 0xfc, 0x3, 0x3, 0x3c, 0x3c, 0x0, 0x0,
    0x0, 0x30, 0x30,

    /* U+0040 "@" */
    0x3f, 0x7, 0xe3, 0x33, 0xe6, 0x3c, 0xf9, 0x9e,
    0x30, 0x6, 0x0, 0x40, 0x7, 0xe0, 0xfc, 0x0,

    /* U+0041 "A" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0042 "B" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc4, 0xfc, 0xfc,

    /* U+0043 "C" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+0044 "D" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc4, 0xfc, 0xfc,

    /* U+0045 "E" */
    0xff, 0xff, 0x6, 0xf, 0xff, 0xf0, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+0046 "F" */
    0xff, 0xff, 0x6, 0xf, 0xff, 0xf0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x3f, 0x3f, 0xc0, 0xc0, 0xcf, 0xcf, 0xc3, 0xc3,
    0x0, 0x3c, 0x3c,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+004B "K" */
    0xc3, 0xc3, 0xcc, 0xcc, 0xf0, 0xf0, 0xd0, 0xcc,
    0xcc, 0xc3, 0xc3,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+004D "M" */
    0xc0, 0x78, 0xf, 0xcf, 0xf9, 0xfc, 0xc7, 0x98,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xf, 0x1, 0x80,

    /* U+004E "N" */
    0xc0, 0x78, 0xf, 0xc1, 0xf8, 0x3c, 0xc7, 0x98,
    0xf1, 0x1e, 0x1f, 0xc3, 0xf8, 0xf, 0x1, 0x80,

    /* U+004F "O" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x44, 0x3c, 0x3c,

    /* U+0050 "P" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xfc, 0xfc, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x44, 0x3c, 0x3c, 0x3, 0x3,

    /* U+0052 "R" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xfc, 0xfc, 0xcc, 0xcc,
    0xcc, 0xc3, 0xc3,

    /* U+0053 "S" */
    0x3f, 0x3f, 0xc0, 0xc0, 0x3c, 0x3c, 0x4, 0x3,
    0x3, 0xfc, 0xfc,

    /* U+0054 "T" */
    0xff, 0xf3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0x0,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+0056 "V" */
    0xc0, 0x78, 0xf, 0x1, 0xe0, 0x34, 0x0, 0x66,
    0xc, 0xc1, 0x98, 0x33, 0x1, 0x80, 0x30, 0x0,

    /* U+0057 "W" */
    0xc0, 0x78, 0xf, 0x1, 0xe6, 0x3c, 0xc7, 0x98,
    0xf3, 0x1e, 0x63, 0xcc, 0x66, 0x60, 0xcc, 0x0,

    /* U+0058 "X" */
    0xc0, 0x78, 0xc, 0xce, 0x19, 0x80, 0xc0, 0x18,
    0x1, 0x1, 0x98, 0x33, 0x18, 0x1f, 0x1, 0x80,

    /* U+0059 "Y" */
    0xc0, 0x78, 0xc, 0xcc, 0x19, 0x81, 0x0, 0x18,
    0x3, 0x0, 0x60, 0xc, 0x1, 0x80, 0x30, 0x0,

    /* U+005A "Z" */
    0xff, 0xf0, 0xc3, 0x30, 0xcc, 0x30, 0xc3, 0xff,
    0xc0,

    /* U+005B "[" */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc7, 0xfe,

    /* U+005C "\\" */
    0xc3, 0xc, 0x30, 0x30, 0xc1, 0x3, 0xc, 0x30,
    0xc0,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x3f, 0xf0,

    /* U+005E "^" */
    0x30, 0xcc, 0xf3,

    /* U+005F "_" */
    0xff, 0xff, 0xc0,

    /* U+0060 "`" */
    0xcc, 0x33,

    /* U+0061 "a" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0062 "b" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc4, 0xfc, 0xfc,

    /* U+0063 "c" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+0064 "d" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc4, 0xfc, 0xfc,

    /* U+0065 "e" */
    0xff, 0xff, 0x6, 0xf, 0xff, 0xf0, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+0066 "f" */
    0xff, 0xff, 0x6, 0xf, 0xff, 0xf0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0067 "g" */
    0x3f, 0x3f, 0xc0, 0xc0, 0xcf, 0xcf, 0xc3, 0xc3,
    0x0, 0x3c, 0x3c,

    /* U+0068 "h" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xff, 0xff, 0xfc,

    /* U+006A "j" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+006B "k" */
    0xc3, 0xc3, 0xcc, 0xcc, 0xf0, 0xf0, 0xd0, 0xcc,
    0xcc, 0xc3, 0xc3,

    /* U+006C "l" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+006D "m" */
    0xc0, 0x78, 0xf, 0xcf, 0xf9, 0xfc, 0xc7, 0x98,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xf, 0x1, 0x80,

    /* U+006E "n" */
    0xc0, 0x78, 0xf, 0xc1, 0xf8, 0x3c, 0xc7, 0x98,
    0xf1, 0x1e, 0x1f, 0xc3, 0xf8, 0xf, 0x1, 0x80,

    /* U+006F "o" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x44, 0x3c, 0x3c,

    /* U+0070 "p" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xfc, 0xfc, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x44, 0x3c, 0x3c, 0x3, 0x3,

    /* U+0072 "r" */
    0xfc, 0xfc, 0xc3, 0xc3, 0xfc, 0xfc, 0xcc, 0xcc,
    0xcc, 0xc3, 0xc3,

    /* U+0073 "s" */
    0x3f, 0x3f, 0xc0, 0xc0, 0x3c, 0x3c, 0x4, 0x3,
    0x3, 0xfc, 0xfc,

    /* U+0074 "t" */
    0xff, 0xf3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0x0,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x3c, 0x3c,

    /* U+0076 "v" */
    0xc0, 0x78, 0xf, 0x1, 0xe0, 0x34, 0x0, 0x66,
    0xc, 0xc1, 0x98, 0x33, 0x1, 0x80, 0x30, 0x0,

    /* U+0077 "w" */
    0xc0, 0x78, 0xf, 0x1, 0xe6, 0x3c, 0xc7, 0x98,
    0xf3, 0x1e, 0x63, 0xcc, 0x66, 0x60, 0xcc, 0x0,

    /* U+0078 "x" */
    0xc0, 0x78, 0xc, 0xce, 0x19, 0x80, 0xc0, 0x18,
    0x1, 0x1, 0x98, 0x33, 0x18, 0x1f, 0x1, 0x80,

    /* U+0079 "y" */
    0xc0, 0x78, 0xc, 0xcc, 0x19, 0x81, 0x0, 0x18,
    0x3, 0x0, 0x60, 0xc, 0x1, 0x80, 0x30, 0x0,

    /* U+007A "z" */
    0xff, 0xf0, 0xc3, 0x30, 0xcc, 0x30, 0xc3, 0xff,
    0xc0,

    /* U+007B "{" */
    0x3e, 0x7c, 0xc1, 0x8c, 0x18, 0xc, 0x18, 0x30,
    0x7c, 0xf8,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xf3, 0xc3, 0xc, 0xc, 0x33, 0xc, 0x33, 0xcf,
    0x0,

    /* U+007E "~" */
    0x33, 0x33, 0xcc, 0xcc,

    /* U+00B7 "·" */
    0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 136, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 102, .box_w = 2, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 170, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 204, .box_w = 8, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 238, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 204, .box_w = 8, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 67, .adv_w = 102, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 68, .adv_w = 136, .box_w = 4, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 136, .box_w = 4, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 136, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 114, .adv_w = 170, .box_w = 6, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 116, .adv_w = 102, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 204, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 102, .box_w = 2, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 238, .adv_w = 136, .box_w = 4, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 170, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 257, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 170, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 170, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 102, .box_w = 2, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 170, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 204, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 481, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 136, .box_w = 5, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 136, .box_w = 4, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 170, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 621, .adv_w = 204, .box_w = 9, .box_h = 2, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 624, .adv_w = 136, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 13},
    {.bitmap_index = 626, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 170, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 680, .adv_w = 170, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 102, .box_w = 2, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 170, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 747, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 763, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 790, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 204, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 814, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 204, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 888, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 904, .adv_w = 238, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 920, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 929, .adv_w = 170, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 939, .adv_w = 102, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 943, .adv_w = 170, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 952, .adv_w = 204, .box_w = 8, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 956, .adv_w = 102, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 4}
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
extern const lv_font_t silkscreen_17 = {   /* explicit `extern`: a bare top-level `const` gets internal
                                               linkage in C++ (unlike C), which would hide this symbol
                                               from claude_face_v2.cpp's LV_FONT_DECLARE reference */
#else
lv_font_t silkscreen_17 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if SILKSCREEN_17*/

