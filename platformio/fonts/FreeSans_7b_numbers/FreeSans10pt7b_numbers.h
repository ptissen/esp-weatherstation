const uint8_t FreeSans10pt7bBitmaps[] PROGMEM = {
  0xF0, 0x04, 0x20, 0x82, 0x10, 0x41, 0x08, 0x20, 0x84, 0x10, 0x43, 0x08,
  0x00, 0x3E, 0x3B, 0x98, 0xD8, 0x3C, 0x1E, 0x0F, 0x07, 0x83, 0xC1, 0xE0,
  0xF0, 0x68, 0x36, 0x31, 0xF0, 0x08, 0xDF, 0xF1, 0x8C, 0x63, 0x18, 0xC6,
  0x31, 0x8C, 0x3E, 0x39, 0xB0, 0x78, 0x3C, 0x18, 0x0C, 0x0C, 0x1C, 0x1C,
  0x38, 0x18, 0x18, 0x0F, 0xFF, 0xFC, 0x3E, 0x33, 0xB0, 0x78, 0x30, 0x18,
  0x18, 0x78, 0x2E, 0x01, 0x80, 0xE0, 0x78, 0x3E, 0x33, 0xF8, 0x02, 0x03,
  0x03, 0x83, 0x41, 0x21, 0x91, 0x89, 0x84, 0x82, 0x7F, 0xFF, 0xE0, 0x40,
  0x20, 0x10, 0x7F, 0xBF, 0xD0, 0x08, 0x04, 0x07, 0xF3, 0x8D, 0x83, 0x01,
  0x80, 0xC0, 0x78, 0x3E, 0x33, 0xF0, 0x3E, 0x39, 0x98, 0x78, 0x3C, 0x06,
  0xF3, 0xFD, 0xC3, 0xC1, 0xE0, 0xF0, 0x78, 0x36, 0x31, 0xF8, 0xFF, 0xFF,
  0xC0, 0x60, 0x60, 0x20, 0x30, 0x30, 0x18, 0x08, 0x0C, 0x04, 0x06, 0x03,
  0x01, 0x80, 0x3E, 0x3B, 0xB0, 0x78, 0x3C, 0x1B, 0x18, 0xF8, 0xC6, 0xC1,
  0xE0, 0xF0, 0x78, 0x3E, 0x3B, 0xF8, 0x3E, 0x33, 0xB0, 0x78, 0x3C, 0x1E,
  0x0F, 0x06, 0xEF, 0x3D, 0x80, 0xC0, 0x78, 0x26, 0x33, 0xF0, 0xF0, 0x00,
  0xF0 };

const GFXglyph FreeSans10pt7bGlyphs[] PROGMEM = {
  {     0,   2,   2,   6,    2,   -1 },   // 0x2E '.'
  {     1,   6,  15,   6,    0,  -14 },   // 0x2F '/'
  {    13,   9,  14,  11,    1,  -13 },   // 0x30 '0'
  {    29,   5,  14,  11,    2,  -13 },   // 0x31 '1'
  {    38,   9,  14,  11,    1,  -13 },   // 0x32 '2'
  {    54,   9,  14,  11,    1,  -13 },   // 0x33 '3'
  {    70,   9,  14,  11,    1,  -13 },   // 0x34 '4'
  {    86,   9,  14,  11,    1,  -13 },   // 0x35 '5'
  {   102,   9,  14,  11,    1,  -13 },   // 0x36 '6'
  {   118,   9,  14,  11,    1,  -13 },   // 0x37 '7'
  {   134,   9,  14,  11,    1,  -13 },   // 0x38 '8'
  {   150,   9,  14,  11,    1,  -13 },   // 0x39 '9'
  {   166,   2,  10,   6,    2,   -9 } }; // 0x3A ':'

const GFXfont FreeSans10pt7b PROGMEM = {
  (uint8_t  *)FreeSans10pt7bBitmaps,
  (GFXglyph *)FreeSans10pt7bGlyphs,
  0x2E, 0x3A, 27 };

// Approx. 267 bytes