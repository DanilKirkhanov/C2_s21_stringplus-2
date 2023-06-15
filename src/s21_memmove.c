#include "s21_string.h"
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *byte_dest = (unsigned char *)dest;
  unsigned char *byte_src = (unsigned char *)src;
  int count = 0;
  if (dest < src) {
    byte_dest = (unsigned char *) dest;
    byte_src = (unsigned char *) src;
    count = 1;
  }
  else 
  {
    byte_dest = (unsigned char *) dest + n - 1;
    byte_src = (unsigned char *) src + n - 1;
    count = -1;
  }
  for (s21_size_t i = 0; i < n; i+=1) {
    *byte_dest = *byte_src;
    byte_dest += count;
    byte_src += count;
  }
  return dest;
}