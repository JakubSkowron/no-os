#include <terminal.h>

#include <bootboot.h>

#include <stdfun.h>

extern BOOTBOOT bootboot;
extern uint32_t fb; // first pixel of screen frame-buffer

uint32_t *const screen_buffer = &fb;
uint32_t screen_width;
uint32_t screen_height;
uint32_t scanline_size; // in pixels

uint32_t cursor_x = 0;
uint32_t cursor_y = 0;
uint32_t text_color = 0x00AAAAFF;

// Ver 1
struct PSF1 {
  uint16_t magic; /* 0x0436 */
  uint8_t flags;  /* how many glyps and if unicode, etc. */
  uint8_t height; /* height; width is always 8 */
                  /* glyphs start here */
};
#define PSF1_MODE512 0x01
#define PSF1_MAGIC 0x0436

// Ver 2
struct PSF2 {
  uint32_t magic; /* 0x864ab572 */
  uint32_t version;
  uint32_t headersize; /* offset of bitmaps in file */
  uint32_t flags;
  uint32_t length;   /* number of glyphs */
  uint32_t charsize; /* number of bytes for each character */
  uint32_t height;   /* dimensions of glyphs */
  uint32_t width;
  /* glyphs start here */
} __attribute__((packed));
#define PSF2_MAGIC 0x864ab572

struct Font font;

void load_font() {
  if (*((uint16_t *)&_binary_font_psf_start) == PSF1_MAGIC) {
    const struct PSF1 *psf1 = (const struct PSF1 *)&_binary_font_psf_start;
    font.glyphs = (uint8_t *)_binary_font_psf_start + sizeof(struct PSF1);
    font.length = (psf1->flags & PSF1_MODE512) ? 512 : 256;
    font.charsize = psf1->height;
    font.width = 8;
    font.height = psf1->height;
    return;
  }

  if (*((uint32_t *)&_binary_font_psf_start) == PSF2_MAGIC) {
    const struct PSF2 *psf2 = (const struct PSF2 *)&_binary_font_psf_start;
    font.glyphs = (uint8_t *)_binary_font_psf_start + psf2->headersize;
    font.length = psf2->length;
    font.charsize = psf2->charsize;
    font.width = psf2->width;
    font.height = psf2->height;
  }
}

void init_terminal() {
  screen_width = bootboot.fb_width;
  screen_height = bootboot.fb_height;
  scanline_size = bootboot.fb_scanline / 4; // in pixels

  load_font();
}

void print_new_line() {
  cursor_x = 0;
  cursor_y += font.height;
  if (cursor_y >= screen_height) {
    // TODO: scroll_screen();
    cursor_y = 0;
  }
}

void print_char(char c) {
  if (c == '\n') {
    print_new_line();
    return;
  }

  uint8_t n = (uint8_t)c;

  // check if glyph exists
  if (n >= font.length) {
    n = (uint8_t)' ';
  }

  const uint8_t *const glyph = font.glyphs + n * font.charsize;
  const unsigned bytes_per_glyph_row = (font.width + 7) / 8;
  const uint8_t *glyph_row = glyph;

  uint32_t *pixel = screen_buffer + cursor_y * (scanline_size) + cursor_x;

  for (unsigned y = 0; y < font.height; ++y) {
    // get one glyph row
    uint64_t row = 0;
    // change to big endian for easier next loop
    for (unsigned i = 0; i < bytes_per_glyph_row; ++i) {
      ((uint8_t *)&row)[bytes_per_glyph_row - i - 1] = glyph_row[i];
    }
    // draw one row
    uint64_t mask = (1 << (font.width - 1));
    mask <<= (font.width + 7) / 8 * 8 - font.width;
    for (unsigned x = 0; x < font.width; ++x, mask >>= 1) {
      if (mask & row) {
        *pixel = text_color;
      }
      pixel++;
    }
    // shift to next row
    glyph_row += bytes_per_glyph_row;
    pixel += (scanline_size) - (font.width);
  }

  cursor_x += font.width;
  if (cursor_x >= screen_width) {
    print_new_line();
  }
}

void print_str(const char *str) {
  while (*str) {
    print_char(*str++);
  }
}

void print_hex16(uint16_t x) {
  const char *hex = "0123456789ABCDEF";
  char buf[2 * sizeof(x) + 1];
  buf[sizeof(buf) - 1] = '\0';
  char *p = buf + sizeof(buf) - 2;
  while (1) {
    *p = hex[x & 0xF];
    x >>= 4;
    if (p == buf) {
      break;
    }
    --p;
  }
  print_str(buf);
}

void move_to(uint32_t tox, uint32_t toy) {
  cursor_x = tox;
  cursor_y = toy;
}

void draw_line(int32_t dx, int32_t dy) {
  double dydx = (double)dy / (double)dx;
  double x = 0;
  double endx = 0;
  if (dx < 0) {
    x = cursor_x + dx;
    endx = cursor_x;
  } else {
    x = cursor_x;
    endx = cursor_x + dx;
  }
  for (; x < endx; x += 0.5) {
    double y = cursor_y + (x - cursor_x) * dydx;
    screen_buffer[scanline_size * (unsigned)y + (unsigned)x] = text_color;
  }
  cursor_x += dx;
  cursor_y += dy;
}
