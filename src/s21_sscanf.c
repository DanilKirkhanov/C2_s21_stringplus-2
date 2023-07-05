// #include "./s21_sscanf.h"
#include "s21_string.h"
// #define S21_NULL ((void *)0)
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

void defualt_typeformat(TypeFormat *typeFormat) {
    typeFormat->specificator = 0;
    typeFormat->weight_number = 0;
    typeFormat->weight_star = 0;
    typeFormat->length = 0;
    typeFormat->length_h = 0;
    typeFormat->length_l = 0;
    typeFormat->length_L = 0;
}

int s21_sscanf(const char *str, const char *format, ...) {
  int success_read_value = 0;
  TypeFormat typeFormat[1];
  va_list args;
  va_start(args, format);
  char full_form[128];
  char now_s, fut_s = ' ';
  defualt_typeformat(typeFormat);
  s21_strcpy(full_form, format);
  while (*format && *str != '\0') {
    now_s = *format;
    if (now_s == '%' || fut_s == '%' || typeFormat[0].specificator ||
        typeFormat[0].length || typeFormat[0].weight) {
      setTypeFormat(typeFormat, format);
      if (typeFormat->weight_star)
        str = parse_weight_star(typeFormat, (char *)str);
      if (*str == ' ' || *str == '\n')
        str += 1;
      else
        success_read_value =
            parsingForme((char *)str, typeFormat, args, format, full_form);
    }
    fut_s = *(format += 1);
  }
  va_end(args);
  return success_read_value;
}

void setTypeFormat(TypeFormat *typeFormat, const char *format) {
    if (*format == '%') format+=1;
    char symbol = *format;
    if (symbol == '*' || (symbol >= '0' && symbol <= '9')) {
        typeFormat->weight += 1;
        if (symbol == '*')
            typeFormat->weight_star += 1;
        else
            typeFormat->weight_number += 1;
    }
    else if (symbol == 'c' || symbol == 'd' || symbol == 'i' || symbol == 'e' ||
        symbol == 'E' || symbol == 'f' || symbol == 'g' || symbol == 'G' ||
        symbol == 'o' || symbol == 's' || symbol == 'u' || symbol == 'x' ||
        symbol == 'X' || symbol == 'p' || symbol == 'n') {
        typeFormat->specificator += 1;
    }
    else if (symbol == 'h' || symbol == 'l' || symbol == 'L') {
        typeFormat->length += 1;
        if (symbol == 'h') typeFormat->length_h += 1;
        if (symbol == 'l') typeFormat->length_l += 1;
        if (symbol == 'L') typeFormat->length_L += 1;
    }
    format--;
}

int parsingForme(char *str, TypeFormat *typeFormat, va_list args,
                 const char *format, char *full_form) {
  int flag_success = 0;
  char buffered[512];
  char *point_str = (char *)str;
  if (typeFormat->specificator && !typeFormat->length) {
    parse_specif(typeFormat, point_str, buffered, format, full_form, args);
    flag_success += 1;
  }
  if (typeFormat->length) {
    parse_length(typeFormat, str, format, full_form, args);
    flag_success += 1; 
  }
  return flag_success;
}

void parse_specif(TypeFormat *typeFormat, char *str, char *buffered,
                  const char *format, char *full_form, va_list args) {
  if (*format == 'c') {
    *va_arg(args, char *) = *str;
  } else if (*format == 'd' || *format == 'i') {
    *va_arg(args, int *) = parseDigit(typeFormat, str, buffered, (char *)format, full_form);
  } else if (*format == 'e' || *format == 'E' || *format == 'f' ||
             *format == 'g' || *format == 'G') {
    *va_arg(args, float *) = parseFloatPoint(str, buffered);
  } else if (*format == 'u' || *format == 'x' || *format == 'X' ||
             *format == 'o') {
    *va_arg(args, unsigned int *) =
        parseDigit(typeFormat, str, buffered, (char *)format, full_form);
  } else if (*format == 's') {
    char *string = va_arg(args, char *);
    if (typeFormat->weight_number) {
            s21_strcpy(string, str);
            parse_weight(string, full_form);
    } 
    else 
    s21_strcpy(string, str);

  } else if (*format == 'p') {
    
    s21_size_t** ptr = va_arg(args, s21_size_t**);
    s21_size_t test = parseAddress(str);
    *ptr = (void*) test;
  }
}

s21_size_t parseAddress(char* str) {
    s21_size_t address = 0;

    // Пропускаем пробелы в начале строки
    while (*str == ' ')
        str++;

    // Проверяем префикс "0x" (если есть)
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
        str += 2;

    // Парсим шестнадцатеричное значение
    while (*str != '\0') {
        char ch = *str;
        int digit;
        address *= 16;
        if (ch >= '0' && ch <= '9')
            digit = ch - '0';
        else if (ch >= 'A' && ch <= 'F')
            digit = ch - 'A' + 10;
        else if (ch >= 'a' && ch <= 'f')
            digit = ch - 'a' + 10;
        else {
          address /= 16;
        }  // Некорректный символ - выходим из цикла

        // Сдвигаем адрес влево на 4 бита и добавляем новую цифру
        // address = (void*)(4(uintptr_t)address << 4 | digit);  
        address += digit; 
        str++;
    }
    return address;
}

void parse_length(TypeFormat *typeFormat, const char *str, const char *format, char *full_form, va_list args) {
  char buffered[512];
  if (typeFormat->length_h && (*format == 'd' || *format == 'i'))
    *va_arg(args, short *) = parseDigit(typeFormat, str, buffered, (char*) format, full_form);
  if (typeFormat->length_h &&
      (*format == 'u' || *format == 'x' || *format == 'X' || *format == 'o'))
    *va_arg(args, unsigned short *) = parseDigit(typeFormat,str, buffered, (char*) format, full_form);
  if (typeFormat->length_l && (*format == 'd' || *format == 'i')) {
    if (typeFormat->length_l == 1)
      *va_arg(args, long int *) = parseDigit(typeFormat, str, buffered, (char *) format, full_form);
    else if (typeFormat->length_l == 2)
      *va_arg(args, long long int *) = parseDigit(typeFormat, str, buffered, (char *) format, full_form);
  }
  if (typeFormat->length_l &&
      (*format == 'u' || *format == 'x' || *format == 'X' || *format == 'o')) {
    if (typeFormat->length_l == 1)
      *va_arg(args, unsigned long int *) = parseDigit(typeFormat, str, buffered, (char *) format, full_form);
    else if (typeFormat->length_l == 2)
      *va_arg(args, unsigned long long int *) = parseDigit(typeFormat, str, buffered, (char *) format, full_form);
  }
  if (typeFormat->length_L &&
      (*format == 'e' || *format == 'E' || *format == 'f' || *format == 'g' ||
       *format == 'G')) {
    *va_arg(args, double *) = parseFloatPoint(str, buffered);
  }
}

void parse_weight(const char *buffered, char *format) {
    int number = 0, part_ten = -1, digit;
    int length = s21_strlen(buffered);
    char *point_format = format;
    while (*format != '\0') {
        if (*format >= '0' && *format <= '9')
            part_ten += 1;
        format += 1;
    }

    while (part_ten >= 0) {
        if (*point_format > '0' && *point_format <= '9') {
            digit = *point_format - '0';
            number = number + digit * pow(10, part_ten);
            part_ten -= 1;
        }
        point_format += 1;
    }

    char *point_str = (char *) buffered;
    for (int i = 0; i < number; i += 1) {
        if (*point_str == '\0' || point_str == S21_NULL) *point_str = ' ';
        point_str+=1;
    }
    if (length > number) *point_str = '\0';
}

char *parse_weight_star(TypeFormat *typeFormat, char *point_str) {
    typeFormat->specificator = 0;
    typeFormat->length = 0;
    typeFormat->weight = 0;
    typeFormat->weight_star = 0;
    while (*point_str != '\0') {
        if (*point_str == '\n' || *point_str == ' ') break;
        point_str += 1;
    }
    return point_str;
}


long long int parseDigit(TypeFormat *typeFormat, const char *str, char *buffered, char *format, char *full_form) {
  s21_strcpy(buffered, str);
  if (typeFormat->weight_number) parse_weight(buffered, full_form);
  int flag_8 = 0, flag_16 = 0, digit, part_ten = -1;
  long long int number = 0;
  char *point_buf = buffered;
  for (; *point_buf != '\0'; point_buf += 1) {
    if (*point_buf == ' ' || *point_buf == '\n') break;
    if (*point_buf == '0' && part_ten == -1 && *format == 'i') {
      if (*(point_buf += 1) == 'x') {
        flag_16 += 1;
        part_ten += 1;
      } else
        flag_8 += 1;
      point_buf -= 1;
    }
    if ((*point_buf >= '0' &&
         ((flag_16 && *point_buf <= '9') || (flag_8 && *point_buf <= '7'))) ||
        (flag_16 && ((*point_buf >= 'A' && *point_buf <= 'F') ||
                     (*point_buf >= 'a' && *point_buf <= 'f'))))
      part_ten += 1;
    else if (*point_buf >= '0' && *point_buf <= '9')
      part_ten += 1;
  }
  point_buf = buffered;
  while (part_ten >= 0) {
    if (*point_buf >= '0' && *point_buf <= '9' && !flag_8 && !flag_16) {
      digit = *point_buf - '0';
      if (part_ten > 0)
        number = number + digit * (unsigned int)(pow(10, part_ten));
      else
        number = number + digit;
      part_ten -= 1;
    } else if (flag_8 && *point_buf >= '0' && *point_buf <= '7') {
      number = getEight(point_buf, digit, number, part_ten);
      part_ten -= 1;
    } else if (flag_16) {
      number = getHex(point_buf, digit, number, part_ten);
      part_ten -= 1;
    }
    point_buf += 1;
  }
  return number;
}

long double parseFloatPoint(const char *str, char *buffered) {
  s21_strcpy(buffered, str);
  int flag_point = 0, flag_e_point = 0, flag_e = 0, part_ten = -1,
      number_pow = 0, part_point_ten = 0, temp_part_point;
  long double number = 0;
  char *point_str = buffered;
  isEinPoint(point_str, &number_pow, &flag_e);
  for (; *point_str != '\0'; point_str += 1) {
    if (*point_str == '.' || *point_str == ',' || flag_point) {
      flag_point = 1;
      if (*point_str >= '0' && *point_str <= '9') part_point_ten += 1;
    } else if (*point_str >= '0' && *point_str <= '9')
      part_ten += 1;
  }
  point_str = buffered;
  temp_part_point = part_point_ten;
  flag_point = 0;
  while (*point_str != '\0') {
    if (*point_str == '.' || *point_str == ',') flag_point = 1;
    if (*point_str == 'e') flag_e_point = 1;
    if (*point_str >= '0' && *point_str <= '9') {
      double digit = *point_str - '0';
      if (flag_point && !flag_e_point) {
        number = number + digit / pow(10, temp_part_point - part_point_ten + 1);
        part_point_ten -= 1;
      } else {
        if (part_ten > 0)
          number = number + digit * pow(10, part_ten);
        else if (part_ten == 0)
          number = number + digit;
        part_ten -= 1;
      }
    }
    point_str += 1;
  }
  if (flag_e < 0)
    number = number / pow(10, number_pow);
  else if (flag_e > 0)
    number = number * pow(10, number_pow);
  return number;
}

void isEinPoint(char *str, int *number_pow, int *flag_e) {
  char symbol;
  char *point_str = str;
  int temp_e = 0, part_ten = -1;
  *flag_e = 0;
  double digit;
  while (*point_str != '\0') {
    if (*point_str == 'e') {
      symbol = *(point_str += 1);
      if (symbol == '-') {
        *flag_e -= 1;
      } else if (symbol >= '0' && symbol <= '9')
        *flag_e += 1;
      point_str -= 1;
    } else if ((*flag_e > 0 || *flag_e < 0) && *point_str >= '0' &&
               *point_str <= '9')
      part_ten += 1;
    point_str += 1;
  }
  point_str = str;
  while (part_ten >= 0 && *point_str != '\0') {
    if (*point_str == 'e') temp_e = 1;
    if (temp_e && *point_str >= '0' && *point_str <= '9') {
      digit = *point_str - '0';
      *number_pow = *number_pow + digit * pow(10, part_ten);
      part_ten -= 1;
    }
    point_str += 1;
  }
}

long long int getHex(char *point_buf, int digit, unsigned long long int summa,
                     int part_ten) {
  if (*point_buf >= '0' && *point_buf <= '9')
    digit = *point_buf - '0';
  else if (*point_buf >= 'A' && *point_buf <= 'F')
    digit = *point_buf - 'A' + 10;
  else if (*point_buf >= 'a' && *point_buf <= 'f')
    digit = *point_buf - 'a' + 10;
  summa = summa + digit * pow(16, part_ten);
  return summa;
}

long long int getEight(char *point_buf, int digit, unsigned long long int summa,
                       int part_ten) {
  digit = *point_buf - '0';
  summa = summa + digit * pow(8, part_ten);
  return summa;
}


