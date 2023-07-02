#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  s21_size_t length = s21_strlen(src);
  if (src == S21_NULL || trim_chars == S21_NULL) {
    result = S21_NULL;
  }
  s21_size_t start = 0;
  s21_size_t end = length - 1;
  while (start < length && s21_strchr(trim_chars, src[start]) != S21_NULL) {
    start++;
  }
  while (end > start && s21_strchr(trim_chars, src[end]) != S21_NULL) {
    end--;
  }
  s21_size_t trimmed_length = end - start + 1;
  char *trimmed_str = (char *)malloc((trimmed_length + 1) * sizeof(char));
  if (trimmed_str == S21_NULL) {
    result = S21_NULL;
  }
  s21_strncpy(trimmed_str, src + start, trimmed_length);
  if (trimmed_str != S21_NULL) {
    result = trimmed_str;
    trimmed_str[trimmed_length] = '\0';
  }
  return result;
}