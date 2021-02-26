#include <standard_functions.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__) || !defined(__i386__)
#error "Compile with i686-elf cross-compiler"
#endif

size_t strlen(const char *str) {
  const char *p = str;
  while (*p++)
    ;
  return p - str;
}

uint16_t *const screen_buffer = (uint16_t *)0xB8000;

static const unsigned screen_width = 80;
static const unsigned screen_height = 50;
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
  uint16_t attribute = (text_color | (bg_color << 4)) << 8;
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

void kernel_sleep(size_t megacycles) {
  megacycles <<= 20;
  while (megacycles--) {
    __asm__ volatile("xchg %eax, %eax");
  }
}

void halt(void);

void kernel_start(void) {
  print_str("Hello, kernel!\n");
  for (unsigned i = 0; i < 50; ++i) {
    kernel_sleep(100);
    text_color = i % 15;
    bg_color = 0;
    print_str("ping ");

    kernel_sleep(100);
    text_color = 0;
    bg_color = i % 15;
    print_str("pong ");
  }
  text_color = 15;
  bg_color = 0;
  print_str("Goodbye, halt.");
  halt();
}