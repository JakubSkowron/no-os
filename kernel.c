#include <stdfun.h>
#include <terminal.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__) || !defined(__i386__)
#error "Compile with i686-elf cross-compiler"
#endif

void halt(void);

void kernel_sleep(size_t megacycles) {
  megacycles <<= 20;
  while (megacycles--) {
    __asm__ volatile("xchg %eax, %eax");
  }
}

void kernel_start(void) {
  print_str("Hello, kernel!\n");
  for (unsigned i = 0; i < 250; ++i) {
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
  print_new_line();
  print_str("Goodbye, halt.");
  halt();
}