#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && *str1 == *str2) {
    str1 += 1;
    str2 += 1;
    if (*str1 == '\0' || *str2 == '\0') break;
  }
  return (*str1 - *str2);
}