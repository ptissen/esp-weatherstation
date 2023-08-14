const uint8_t FreeSans8pt7bBitmaps[] PROGMEM = {
  0xF0, 0x00, 0x84, 0x22, 0x10, 0x88, 0x42, 0x21, 0x00, 0x7D, 0x8B, 0x1C,
  0x18, 0x30, 0x60, 0xC1, 0x87, 0x89, 0xF0, 0x37, 0xF3, 0x33, 0x33, 0x33,
  0x30, 0x7D, 0x8E, 0x0C, 0x10, 0x61, 0x8E, 0x30, 0xC1, 0x03, 0xF8, 0x7D,
  0x8E, 0x18, 0x30, 0xC3, 0x81, 0x81, 0x83, 0x8D, 0xF0, 0x06, 0x0E, 0x0E,
  0x16, 0x26, 0x66, 0x46, 0xFF, 0x06, 0x06, 0x06, 0x7E, 0x83, 0x06, 0x0F,
  0xD8, 0xC0, 0x81, 0x83, 0x8D, 0xF0, 0x7C, 0x8F, 0x0C, 0x0B, 0xD8, 0xE0,
  0xC1, 0x83, 0x8D, 0xF0, 0xFE, 0x04, 0x10, 0x60, 0x82, 0x04, 0x18, 0x20,
  0x41, 0x80, 0x7D, 0x8E, 0x1E, 0x37, 0xCF, 0xA1, 0xC1, 0x83, 0x8D, 0xF0,
  0x7D, 0x8A, 0x1C, 0x18, 0x78, 0xDE, 0x81, 0x87, 0x89, 0xE0, 0x83 };

const GFXglyph FreeSans8pt7bGlyphs[] PROGMEM = {
  {     0,   2,   2,   4,    1,   -1 },   // 0x2E '.'
  {     1,   5,  12,   4,    0,  -11 },   // 0x2F '/'
  {     9,   7,  11,   9,    1,  -10 },   // 0x30 '0'
  {    19,   4,  11,   9,    2,  -10 },   // 0x31 '1'
  {    25,   7,  11,   9,    1,  -10 },   // 0x32 '2'
  {    35,   7,  11,   9,    1,  -10 },   // 0x33 '3'
  {    45,   8,  11,   9,    0,  -10 },   // 0x34 '4'
  {    56,   7,  11,   9,    1,  -10 },   // 0x35 '5'
  {    66,   7,  11,   9,    1,  -10 },   // 0x36 '6'
  {    76,   7,  11,   9,    1,  -10 },   // 0x37 '7'
  {    86,   7,  11,   9,    1,  -10 },   // 0x38 '8'
  {    96,   7,  11,   9,    1,  -10 },   // 0x39 '9'
  {   106,   1,   8,   4,    2,   -7 } }; // 0x3A ':'

const GFXfont FreeSans8pt7b PROGMEM = {
  (uint8_t  *)FreeSans8pt7bBitmaps,
  (GFXglyph *)FreeSans8pt7bGlyphs,
  0x2E, 0x3A, 22 };

// Approx. 205 bytes