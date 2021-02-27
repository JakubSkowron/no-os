#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <stdint.h>

void init_terminal();

// Font representation (PSF1 or PSF2)
struct Font {
  uint8_t *glyphs;
  uint32_t length;
  uint32_t charsize;
  uint32_t height;
  uint32_t width;
};

extern struct Font font;

// linked using ld --format=binary
extern uint8_t _binary_font_psf_start[];
extern uint8_t _binary_font_psf_end;
extern uint8_t _binary_font_psf_size; // Note: get address of this byte to get real size

extern uint32_t *const screen_buffer;

extern uint32_t screen_width;
extern uint32_t screen_height;
extern uint32_t cursor_x;
extern uint32_t cursor_y;

extern uint32_t text_color;

void print_new_line();
void print_char(char c);
void print_str(const char *str);
void print_hex16(uint16_t x);
void move_to(uint32_t tox, uint32_t toy);
void draw_line(int32_t dx, int32_t dy);

#endif // _TERMINAL_H
