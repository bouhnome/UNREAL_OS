#ifndef PSFU_H
#define PSFU_H
#define PSF_FONT_MAGIC 0x864ab572
#include <stdint.h>

typedef struct {
	uint32_t magic;         /* magic bytes to identify PSF */
	uint32_t version;       /* zero */
	uint32_t headersize;    /* offset of bitmaps in file, 32 */
	uint32_t flags;         /* 0 if there's no unicode table */
	uint32_t numglyph;      /* number of glyphs */
	uint32_t bytesperglyph; /* size of each glyph */
	uint32_t height;        /* height in pixels */
	uint32_t width;         /* width in pixels */
} PSF_font;
extern uint8_t _binary_drivers_console_fonts_Cyr_a8x8_psfu_start;
extern uint8_t _binary_drivers_console_fonts_Cyr_a8x8_psfu_end;
extern uint8_t _binary_drivers_console_fonts_Cyr_a8x14_psfu_start;
extern uint8_t _binary_drivers_console_fonts_Cyr_a8x14_psfu_end;
extern uint8_t _binary_drivers_console_fonts_Cyr_a8x16_psfu_start;
extern uint8_t _binary_drivers_console_fonts_Cyr_a8x16_psfu_end;
extern uint8_t _binary_drivers_console_fonts_latarcyrheb_sun32_psfu_start;
extern uint8_t _binary_drivers_console_fonts_latarcyrheb_sun32_psfu_end;
#endif
