#include "s21_string.h"

char* insert(const char* src, const char* str, size_t start_index) {
  char* result = S21_NULL;
  if (src == S21_NULL || str == S21_NULL || start_index > s21_strlen(src))
    result = S21_NULL;
  else {
    size_t src_len = s21_strlen(src);
    size_t str_len = s21_strlen(str);
    size_t new_len = src_len + str_len;
    char* new_str = (char*)malloc((new_len + 1) * sizeof(char));
    s21_strncpy(new_str, src, start_index);
    s21_strncpy(new_str + start_index, str, str_len);
    s21_strncpy(new_str + start_index + str_len, src + start_index,
                src_len - start_index);
    result = new_str;
    new_str[new_len] = '\0';
  }
  return result;
}
