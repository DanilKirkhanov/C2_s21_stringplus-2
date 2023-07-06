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
char* s21_strncpy(char* destination, const char* source, s21_size_t num);
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
    int flag_c;
    int flag_d;
    int flag_i;
    int flag_e;
    int flag_E;
    int flag_f;
    int flag_g;
    int flag_G;
    int flag_o;
    int flag_s;
    int flag_u;
    int flag_x;
    int flag_X;
    int flag_p;
    int flag_n;
    int flag_proc;
    int flag_number;
    int flag_star;
    int flag_h;
    int flag_l;
    int flag_L;
} TypeFormat;

void set_flags(TypeFormat *typeFormat, char format);
char *parse_star(char *str);
int parse_form(TypeFormat *typeFormat, char *str, va_list args, char *full_form);
long long int parse_digit(TypeFormat *format, char *str, char *full_form);
void parse_weight(char *str, char *full_form);

#endif  // S21_STRING