#ifndef S21_STRING
#define S21_STRING
#include <stdlib.h>
#include <stdarg.h>
#define S21_NULL ((void *)0)
typedef unsigned long int s21_size_t;
void *s21_memchr(const void *str, int c, s21_size_t n);            // ok
void *s21_memcpy(void *dest, const void *src, s21_size_t n);       // ok
void *s21_memset(void *str, int c, s21_size_t n);                  // ok
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);  // ok
void *s21_memmove(void *dest, const void *src, s21_size_t n);      // ok
char *s21_strcat(char *dest, const char *src);                     // ok
char *s21_strncat(char *dest, const char *src, s21_size_t n);      // ok
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
void s21_errnum_tostring(char str[], int num);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
int s21_sprintf(char *str, const char *format, ...);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_to_upper(const char *string);
void *s21_to_lower(const char *string);
int s21_sscanf(const char *str, const char *format, ...);

typedef struct TypeFormat {
    int specificator;
    int weight;
    int weight_number;
    int weight_star;
    int length;
    int length_h;
    int length_l;
    int length_L;
    int precent;
} TypeFormat;

void setTypeFormat(TypeFormat *typeFormat, const char *format);
int parsingForme(char *str, TypeFormat *typeFormat, va_list args,const char *format, char *full_form);
void parse_specif(TypeFormat *typeFormat, char *str, char *buffered, const char *format, char *full_format, va_list args);
void parse_length(TypeFormat *typeFormat, const char *str, const char *format, char *full_form, va_list args);
void parse_weight(const char *buffered, char *format);
char *parse_weight_star(TypeFormat *typeFormat, char *point_str);
long long int parseDigit(TypeFormat *typeFormat, const char *str, char *buffered, char *format, char *full_form);
long double parseFloatPoint(const char *str, char *buffered);
s21_size_t parseAddress(char* str);
long long int getHex(char *point_buf, int digit, unsigned long long int summa, int part_ten);
long long int getEight(char *point_buf, int digit, unsigned long long int summa, int part_ten);
void isEinPoint(char *point_str, int *number_pow, int *flag_e);

#endif  // S21_STRING