#include <terminal.h>

uint16_t *const screen_buffer = (uint16_t *)0xB8000;

const unsigned screen_width = 80;
const unsigned screen_height = 25;
unsigned cursor_x = 0;
unsigned cursor_y = 0;

uint8_t text_color = 15; // lower 4 bits of attribute
uint8_t bg_color = 0;    // higher 4 bits

// Move everything one line up
void scroll_screen() {
  uint16_t *src = screen_buffer + screen_width;
  uint16_t *end = screen_buffer + screen_width * (screen_height - 1);
  uint16_t *dest = screen_buffer;
  while (dest != end) {
    *dest++ = *src++;
  }

  // Fill last line with spaces
  const uint16_t attribute = (text_color | (bg_color << 4)) << 8;
  const char c = ' ';
  end += screen_width;
  while (dest != end) {
    *dest++ = attribute | c;
  }
}

void print_new_line() {
  cursor_x = 0;
  ++cursor_y;
  if (cursor_y == screen_height) {
    scroll_screen();
    --cursor_y;
  }
}

void print_char(char c) {
  if (c == '\n') {
    print_new_line();
    return;
  }
  const uint16_t attribute = (text_color | (bg_color << 4)) << 8;
  screen_buffer[cursor_y * screen_width + cursor_x] = attribute | (uint8_t)c;
  ++cursor_x;
  if (cursor_x == screen_width) {
    print_new_line();
  }
}

void print_str(const char *str) {
  while (*str) {
    print_char(*str++);
  }
}
