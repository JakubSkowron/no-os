#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <stdint.h>

extern uint16_t *const screen_buffer;

extern const unsigned screen_width;
extern const unsigned screen_height;
extern unsigned cursor_x;
extern unsigned cursor_y;

extern uint8_t text_color;
extern uint8_t bg_color;

// Move everything one line up
void scroll_screen();
void print_new_line();
void print_char(char c);
void print_str(const char *str);



#endif  // _TERMINAL_H
