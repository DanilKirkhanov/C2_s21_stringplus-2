#include "../s21_string.h"
char *s21_strchr(const char *str, int c) {
  char *byte_str = (char *)str;
  int flag_str = 0;
  while (*byte_str != '\0') {
    if (*byte_str == c) {
      flag_str = 1;
      break;
    }
    byte_str += 1;
  }
  return flag_str ? byte_str : S21_NULL;
}
