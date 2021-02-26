#ifndef _STDFUN_H
#define _STDFUN_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);
uint8_t *memmove(uint8_t *dest, const uint8_t *src, size_t n);

#endif // _STDFUN_H