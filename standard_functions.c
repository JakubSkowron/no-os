#include <standard_functions.h>

uint8_t *memmove(uint8_t *dest, const uint8_t *src, size_t n) {
  uint8_t *const ret = dest;
  if (dest == src || n == 0) {
    return ret;
  } else if (dest < src) {
    const uint8_t *end = dest + n;
    while (dest != end) {
      *dest++ = *src++;
    }
    return ret;
  } else {
    uint8_t *end = dest + n;
    const uint8_t *src_end = src + n;
    while (end != dest) {
      *--end = *--src_end;
    }
    return ret;
  }
}