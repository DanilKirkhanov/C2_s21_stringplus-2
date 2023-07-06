#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int minus;
  int plus;
  int space;
  int sharp;
  int null;
  int width;
  int precision;
  char length;
  char spec;
} Flags;
int radix(char c);
char *width(Flags flags, char *string);
const char *str_to_int(const char *format, int *digit);
int s21_sprintf(char *str, const char *format, ...);
char *int_to_str(unsigned long int num, int radix, Flags flags);
const char *s21_parser(const char *format, Flags *flags, va_list arg);
void pars_num(Flags flags, unsigned long int *num, int *sign, char *s);

int s21_sprintf(char *str, const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  for (; *format != '\0'; format++, str++) {
    if (*format != '%') {
      *str = *format;
    } else {
      Flags flags = {0, 0, 0, 0, 0, 0, -1, ' ', ' '};
      format = s21_parser(format, &flags, arg);
      char *result;
      if (flags.spec == 'x' || flags.spec == 'X' || flags.spec == 'p' ||
          flags.spec == 'u' || flags.spec == 'd' || flags.spec == 'i' ||
          flags.spec == 'o') {
        unsigned long int digit = va_arg(arg, unsigned long int);
        result = int_to_str(digit, radix(flags.spec), flags);
      } else if (flags.spec == 's') {
        char *raw_result = va_arg(arg, char *);
        if (flags.precision > -1) {
          result = malloc(flags.precision + 1);
          strncpy(result, raw_result, flags.precision);
        } else {
          result = malloc(strlen(raw_result) + 1);
          strcpy(result, raw_result);
        }
      } else if (flags.spec == 'c') {
        result = malloc(2);
        *result = va_arg(arg, int);
      } else if (flags.spec == '%') {
        result = malloc(2);
        *result = '%';
      } else
        printf("nan");
      result = width(flags, result);
      strcat(str, result);
      str += strlen(result) - 1;
      free(result);
    }
  }
  va_end(arg);
  return strlen(str);  // strlen(str);
}

const char *s21_parser(const char *format, Flags *flags,
                       va_list arg) {  // for flags
  format++;
  char len[] = "hlL";
  char spec[] = "cdieEfgGosuxXpn%";
  while (1) {
    if (*format == '0')
      flags->null = 1;
    else if (*format == '-')
      flags->minus = 1;
    else if (*format == '+')
      flags->plus = 1;
    else if (*format == '#')
      flags->sharp = 1;
    else if (*format == ' ')
      flags->space = 1;
    else {
      break;
    }
    format++;
  }
  if (flags->minus) flags->null = 0;
  if (*format == '*') {
    flags->width = va_arg(arg, int);
    format++;
  }
  if (*format > 48 && *format < 58) {
    format = str_to_int(format, &flags->width);
  }
  if (*format == '.') {
    format++;
    if (*format == '*') {
      flags->precision = va_arg(arg, int);
      format++;
    } else
      format = str_to_int(format, &flags->precision);
  }
  for (int i = 0; i < 3; i++) {
    if (*format == len[i]) {
      flags->length = *format;
      format++;
      break;
    }
  }
  for (int i = 0; i < 16; i++) {
    if (*format == spec[i]) {
      flags->spec = *format;
      break;
    }
  }
  return format;
}

const char *str_to_int(const char *format, int *digit) {
  int result = 0;
  for (; *format > 47 && *format < 58; format++) {
    result = result * 10 + (*format - 48);
  }
  *digit = result;
  return format;
}  // --------------------------------------------- for flags

char *width(Flags flags, char *string) {
  char *result = 0;
  int length = strlen(string);
  int length2 = length;
  if (length < flags.width) {
    result = malloc(flags.width + 1);
    for (int i = 0; i < flags.width; i++) {
      char c = ' ';
      if (flags.null) c = '0';
      if (flags.minus) length2 = flags.width;
      result[i] = c;
    }
    for (int j = 0; j < length; j++) {
      result[j + (flags.width - length2)] = string[j];
    }
    free(string);
  } else {
    result = string;
  }
  return result;
}

char *int_to_str(unsigned long int num, int radix, Flags flags) {  // for int
  int j = 0;
  char str[100];
  int sign = 0;
  char s = '-';
  pars_num(flags, &num, &sign, &s);
  while (num != 0) {
    if (num % radix < 10)
      str[j] = num % radix + 48;
    else
      str[j] = (num % radix) + (flags.spec == 'X' ? 55 : 87);
    j++;
    num /= radix;
  }
  char *result;
  if (flags.precision > j) {
    result = malloc(flags.precision + sign + 1);
    for (int i = 0 + sign; i < flags.precision + sign; i++) result[i] = '0';
  } else {
    result = malloc(j + 1 + sign);
    flags.precision = j;
  }
  if (sign) result[0] = s;
  for (int i = 0; i < j; i++) {
    result[flags.precision - j + i + sign] = str[j - i - 1];
  }
  result[flags.precision + sign] = '\0';
  if ((flags.sharp && (flags.spec == 'x' || flags.spec == 'X' ||
                       flags.spec == 'p' || flags.spec == 'o')) ||
      flags.spec == 'p') {
    char *res_sharp = malloc(strlen(result) + (flags.spec == 'o' ? 2 : 3));
    if (flags.spec == 'o') {
      strcpy(res_sharp, "0");
    } else
      strcpy(res_sharp, flags.spec == 'X' ? "0X" : "0x");
    strcat(res_sharp, result);
    free(result);
    result = res_sharp;
  }

  return result;
}

void pars_num(Flags flags, unsigned long int *num, int *sign, char *s) {
  if (flags.length == 'h' && flags.spec != 'p')
    *num = (unsigned short int)*num;
  else if (flags.length != 'l' && flags.spec != 'p')
    *num = (unsigned int)*num;
  if ((flags.spec == 'd' || flags.spec == 'i')) {
    long int int_num;
    if (flags.length == 'h')
      int_num = (short int)*num;
    else if (flags.length == 'l')
      int_num = (long int)*num;
    else
      int_num = (int)*num;
    *num = int_num;
    if (int_num < 0) {
      int_num *= -1;
      *num = int_num;
      *sign = 1;
    }
    if (!*sign && flags.space) *s = ' ';
    if (!*sign && flags.plus) *s = '+';
    if (flags.plus || flags.space) *sign = 1;
  }
}

int radix(char c) {
  int radix = 0;
  if (c == 'x' || c == 'X' || c == 'p')
    radix = 16;
  else if (c == 'o')
    radix = 8;
  else if (c == 'u' || c == 'd' || c == 'i')
    radix = 10;
  return radix;
}  // ----------------------------------------------------for int