#include "../s21_string.h"
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *byte_str1 = (unsigned char *)str1;
  unsigned char *byte_str2 = (unsigned char *)str2;
  s21_size_t neutral = 0;
  for (; n > 0; n -= 1) {
    if (*byte_str1 > *byte_str2)
      neutral = 1;
    else if (*byte_str1 < *byte_str2)
      neutral = -1;
    else
      neutral = 0;
    if (neutral != 0) break;
  }
  return (int)neutral;
}
