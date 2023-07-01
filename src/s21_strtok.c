#include "s21_string.h"

char* s21_strtok(char* str, const char* delimiters) {
  static char* token = S21_NULL;
  static char* nextToken = S21_NULL;
  if (str != S21_NULL) {
    token = str;
    nextToken = str;
  } else {
    if (nextToken == S21_NULL) {
      return S21_NULL;
    }
    token = nextToken;
  }
  if (*token == '\0') {
    return S21_NULL;
  }
  while (*token != '\0' && s21_strchr(delimiters, *token) != S21_NULL) {
    token++;
  }
  if (*token == '\0') {
    return S21_NULL;
  }
  nextToken = token + 1;
  while (*nextToken != '\0' && s21_strchr(delimiters, *nextToken) == S21_NULL) {
    nextToken++;
  }
  if (*nextToken != '\0') {
    *nextToken = '\0';
    nextToken++;
  } else {
    nextToken = S21_NULL;
  }
  return token;
}
