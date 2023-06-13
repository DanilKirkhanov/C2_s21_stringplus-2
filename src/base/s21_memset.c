#include "../s21_string.h"
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *byte_str = (unsigned char *)str;
  while (n > 0) {
    *byte_str = c;
    byte_str += 1;
    n -= 1;
  }
  return byte_str;
}
