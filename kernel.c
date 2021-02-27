
#include <stddef.h>
#include <stdint.h>

#include <bootboot.h>

#include <stdfun.h>
#include <terminal.h>

#if defined(__linux__) || !defined(__x86_64__)
#error "Compile with x86_64-elf-elf cross-compiler"
#endif

extern BOOTBOOT bootboot;
extern uint8_t environment[4096];

extern uint32_t screen_width;
extern uint32_t screen_height;

void halt(void);

void kernel_sleep(size_t megacycles) {
  megacycles <<= 20;
  while (megacycles--) {
    __asm__ volatile("xchg %eax, %eax");
  }
}

// apic_id - identifier of executing processor
void kernel_start(uint16_t apic_id) {
  if (apic_id != bootboot.bspid) {
    // not a bootstrap processor
    kernel_sleep(apic_id * 10);
    move_to(0, apic_id * 50);
    print_str("CPU");
    print_hex16(apic_id);
    return;
  }

  init_terminal();

  print_str("Hello, kernel!\n");
  print_str("Bootstrap CPU");
  print_hex16(apic_id);

  move_to(screen_width / 2, screen_height / 2);
  draw_line(50, -20);
  draw_line(-100, 100);
  draw_line(-10, 110);
  draw_line(200, -50);

  text_color = 0x0011F0F0;
  for (unsigned i = 0; i < 100; ++i) {
    kernel_sleep(50);
    text_color = (text_color * 15) & 0x00FFFFFF;
    print_str("ping ");
    kernel_sleep(50);
    text_color = (text_color * 15) & 0x00FFFFFF;
    print_str("pong ");
  }
  text_color = 0x00FFFFFF;
  print_new_line();
  print_str("Goodbye, halt.");
}