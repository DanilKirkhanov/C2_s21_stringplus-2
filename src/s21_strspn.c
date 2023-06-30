#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  int lenght = 0;
  while (*str1 != 0) {
    if (!s21_strchr(str2, *str1)) break;
    lenght += 1;
  }
  return lenght;
}