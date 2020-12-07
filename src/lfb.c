#include "uart.h"

#include "mbox.h"

typedef struct {
  unsigned int magic;
  unsigned int version;
  unsigned int headersize;
  unsigned int flags;
  unsigned int numglyph;
  unsigned int bytesperglyph;
  unsigned int height;
  unsigned int width;
  unsigned char glyphs;
}
__attribute__((packed)) psf_t;
extern volatile unsigned char _binary_font_psf_start;

typedef struct {
  unsigned char magic[4];
  unsigned int size;
  unsigned char type;
  unsigned char features;
  unsigned char width;
  unsigned char height;
  unsigned char baseline;
  unsigned char underline;
  unsigned short fragments_offs;
  unsigned int characters_offs;
  unsigned int ligature_offs;
  unsigned int kerning_offs;
  unsigned int cmap_offs;
}
__attribute__((packed)) sfn_t;
extern volatile unsigned char _binary_font_sfn_start;

unsigned int width, height, pitch;
unsigned char * lfb;

void lfb_init() {
  mbox[0] = 35 * 4;
  mbox[1] = MBOX_REQUEST;

  mbox[2] = 0x48003;
  mbox[3] = 8;
  mbox[4] = 8;
  mbox[5] = 1024;
  mbox[6] = 768;

  mbox[7] = 0x48004;
  mbox[8] = 8;
  mbox[9] = 8;
  mbox[10] = 1024;
  mbox[11] = 768;

  mbox[12] = 0x48009;
  mbox[13] = 8;
  mbox[14] = 8;
  mbox[15] = 0;
  mbox[16] = 0;

  mbox[17] = 0x48005;
  mbox[18] = 4;
  mbox[19] = 4;
  mbox[20] = 32;

  mbox[21] = 0x48006;
  mbox[22] = 4;
  mbox[23] = 4;
  mbox[24] = 1;

  mbox[25] = 0x40001;
  mbox[26] = 8;
  mbox[27] = 8;
  mbox[28] = 4096;
  mbox[29] = 0;

  mbox[30] = 0x40008;
  mbox[31] = 4;
  mbox[32] = 4;
  mbox[33] = 0;

  mbox[34] = MBOX_TAG_LAST;

  if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
    mbox[28] &= 0x3FFFFFFF;
    width = mbox[5];
    height = mbox[6];
    pitch = mbox[33];
    lfb = (void * )((unsigned long) mbox[28]);
  } else {
    uart_puts("Unable to set screen resolution to 1024x768x32\n");
  }
}

void lfb_print(int x, int y, char * s) {
  psf_t * font = (psf_t * ) & _binary_font_psf_start;
  // loop over every character
  while ( * s) {
	  // get the glyph of every character
    unsigned char * glyph = (unsigned char * ) & _binary_font_psf_start +
      font -> headersize + ( * ((unsigned char * ) s) < font -> numglyph ? * s : 0) * font->bytesperglyph;
    // calculate the offset of topleft corner
    int offs = (y * pitch) + (x * 4);
    int i, j, line, mask, bytesperline = (font -> width + 7) / 8;
    if ( * s == '\r') {
      x = 0;
    } else
    if ( * s == '\n') {
      x = 0;
      y += font -> height;
    } else {
      for (j = 0; j < font -> height; j++) {
        line = offs;
        mask = 1 << (font -> width - 1);
        for (i = 0; i < font -> width; i++) {
          *((unsigned int * )(lfb + line)) = ((int) * glyph) & mask ? 0xFFFFFF : 0;
          mask >>= 1;
          line += 4;
        }
        glyph += bytesperline;
        offs += pitch;
      }
      x += (font -> width + 1);
    }
    s++;
  }
}

