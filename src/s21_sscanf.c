#include <math.h>
#include "s21_string.h"
#include <stdio.h>

void turn_off_flags(TypeFormat *typeFormat) {
    typeFormat->flag_c = 0;
    typeFormat->flag_d = 0;
    typeFormat->flag_i = 0;
    typeFormat->flag_e = 0;
    typeFormat->flag_E = 0;
    typeFormat->flag_f = 0;
    typeFormat->flag_g = 0;
    typeFormat->flag_G = 0;
    typeFormat->flag_o = 0;
    typeFormat->flag_s = 0;
    typeFormat->flag_u = 0;
    typeFormat->flag_x = 0;
    typeFormat->flag_X = 0;
    typeFormat->flag_p = 0;
    typeFormat->flag_n = 0;
    typeFormat->flag_proc = 0;
    typeFormat->flag_number = 0;
    typeFormat->flag_star = 0;
    typeFormat->flag_h = 0;
    typeFormat->flag_l = 0;
    typeFormat->flag_L = 0;
}
int s21_sscanf(const char *str, const char *format, ...) {
    int result1 = 0, result2 = 0;
    char *full_form = (char *) format;
    TypeFormat typeFormat[1];
    va_list args;
    va_start(args, format);
    turn_off_flags(typeFormat);
    while (*format) {
        if (*format == '%' || typeFormat[0].flag_proc) {
            set_flags(typeFormat, *format);
            if (*format == '*')
                str = parse_star((char *) str);
            if (*format != '*' && *format != 'h' && *format != 'l' && *format != 'L') {
                result1 = parse_form(typeFormat, (char *) str, args, full_form);
            }
            if (*format && (*format == 'h'|| *format == 'l' || *format == 'L'))
                result2 = parse_length(typeFormat, str, format, full_form, args);
        }
        format+=1;
    }
    return result1 + result2;
}
void set_flags(TypeFormat *typeFormat, char format)
 {
    if (format == 'c') typeFormat->flag_c +=1;
    else if (format == 'd') typeFormat->flag_d +=1;
    else if (format == 'i') typeFormat->flag_i +=1;
    else if (format == 'e') typeFormat->flag_e +=1;
    else if (format == 'E') typeFormat->flag_E +=1;
    else if (format == 'f') typeFormat->flag_f +=1;
    else if (format == 'g') typeFormat->flag_g +=1;
    else if (format == 'G') typeFormat->flag_G +=1;
    else if (format == 'o') typeFormat->flag_o +=1;
    else if (format == 's') typeFormat->flag_s +=1;
    else if (format == 'u') typeFormat->flag_u +=1;
    else if (format == 'x') typeFormat->flag_x +=1;
    else if (format == 'X') typeFormat->flag_X +=1;
    else if (format == 'p') typeFormat->flag_p +=1;
    else if (format == 'n') typeFormat->flag_n +=1;
    else if (format == '%') typeFormat->flag_proc +=1;
    else if (format >= '0' && format <= '9') typeFormat->flag_number +=1;
    else if (format == '*') typeFormat->flag_star +=1;
    else if (format == 'h') typeFormat->flag_h +=1;
    else if (format == 'l') typeFormat->flag_l +=1;
    else if (format == 'L') typeFormat->flag_L +=1;
}

char *parse_star(char *str) {
    char *point_str = str;
    while (*point_str != '\0') {
        if (*point_str == '\n' || *point_str == ' ') break;
        point_str += 1;
    }
    return point_str;
}

int parse_form(TypeFormat *typeFormat, char *str, va_list args, char *full_form) {
    int result = 0;
    char buffered[512];
    if (typeFormat->flag_c) {
        if (str != S21_NULL) result +=1;
        *va_arg(args, char *) = *str;
    }
    else if (typeFormat->flag_d || typeFormat->flag_i) {
        *va_arg(args, int *) = parse_digit(typeFormat, str, full_form);
        if (va_arg(args, int *) != S21_NULL) result +=1;
    }
    else if (typeFormat->flag_e || typeFormat->flag_E || typeFormat->flag_f || typeFormat->flag_g || typeFormat->flag_G) {
        *va_arg(args, float *) = parse_float_point(typeFormat, str, buffered, full_form);
        if (va_arg(args,float *) != S21_NULL) result +=1;
    }
    else if (typeFormat->flag_u || typeFormat->flag_x || typeFormat->flag_X || typeFormat->flag_o) {
        *va_arg(args, unsigned int *) = parse_digit(typeFormat, str, full_form);
        if (va_arg(args, unsigned int *) != S21_NULL) result +=1;
    }
    else if (typeFormat->flag_s) {
        char *string = va_arg(args, char *);
        if (typeFormat->flag_number) {
            s21_strcpy(string, str);
            parse_weight(string, full_form);
        }
        else
            s21_strcpy(string, str);
        if (string != S21_NULL) result +=1;
    }
    else if (typeFormat->flag_p) {
        s21_size_t** ptr = va_arg(args, s21_size_t**);
        s21_size_t test = parse_address(str);
        *ptr = (void*) test;
        if (ptr != S21_NULL) result +=1;
    }
    else if (typeFormat->flag_n) {
        *va_arg(args, int *) = parse_n(full_form, args);
        if (va_arg(args, int *) != S21_NULL) result +=1;
    }
    return result;
}

int parse_length(TypeFormat *typeFormat, const char *str, const char *format, char *full_form, va_list args) {
    char buffered[512];
    int result = 0;
    if (typeFormat->flag_h && (*format == 'd' || *format == 'i'))
        *va_arg(args, short *) = *parse_digit(typeFormat, (char *) str, full_form);
    if (typeFormat->flag_h && (*format == 'u' || *format == 'x' || *format == 'X' || *format == 'o'))
        *va_arg(args, unsigned short *) = *parse_digit(typeFormat, (char *) str, full_form);
    if (typeFormat->flag_l && (*format == 'd' || *format == 'i')) {
        if (typeFormat->flag_l == 1)
            *va_arg(args, long int *) = *parse_digit(typeFormat, (char *) str, full_form);
        else if (typeFormat->flag_l == 2)
            *va_arg(args, long long int *) = *parse_digit(typeFormat, (char *) str, full_form);
    }
    if (typeFormat->flag_l &&
        (*format == 'u' || *format == 'x' || *format == 'X' || *format == 'o')) {
        if (typeFormat->flag_l == 1)
            *va_arg(args, unsigned long int *) = *parse_digit(typeFormat, (char *) str, full_form);
        else if (typeFormat->flag_l == 2)
            *va_arg(args, unsigned long long int *) = *parse_digit(typeFormat, (char *) str, full_form);
    }
    if (typeFormat->flag_L && (*format == 'e' || *format == 'E' || *format == 'f' || *format == 'g' || *format == 'G'))
        *va_arg(args, double *) = parse_float_point(typeFormat, str, buffered, full_form);
    if (parse_digit(typeFormat, (char *) str, full_form) != S21_NULL) result +=1;
    else if (parse_float_point(typeFormat, str, buffered, full_form) != S21_NULL) result +=1;
    return result;
}


void parse_weight(char *str, char *format) {
    int width = 0;
    int length = s21_strlen(str);
    while (*format != '\0') {
        if (*format >= '0' && *format <= '9') {
            width = width * 10 + (*format - '0');
        }
        format+=1;
    }
    char* point_str = str;
    if (length < width) {
        while (length < width) {
            *point_str = ' ';
            point_str+=1;
            length+=1;
        }
    } else if (length > width) {
        point_str += width;
        *point_str = '\0';
    }
}

long long int *parse_digit(TypeFormat *typeFormat, char *str, char *full_form) {
    if (typeFormat->flag_number) parse_weight(str, full_form);
    int flag_8 = 0, flag_16 = 0, digit, part_ten = -1;
    long long int number = 0;
    long long int *point_number = &number;
    char *point_buf = str;
    for (; *point_buf != '\0'; point_buf += 1) {
        if (*point_buf == ' ' || *point_buf == '\n') break;
        if (*point_buf == '0' && part_ten == -1 && typeFormat->flag_i) {
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
    char *buffered = str;
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
            number = getEight(point_buf, part_ten);
            part_ten -= 1;
        } else if (flag_16) {
            number = getHex(point_buf, part_ten);
            part_ten -= 1;
        }
        point_buf += 1;
    }
    return point_number;
}

long double *parse_float_point(TypeFormat *typeFormat, const char* str, char* buffered, char *full_form) {
    if (typeFormat->flag_number) parse_weight((char *) str, full_form);
    s21_strcpy(buffered, str);
    int flag_point = 0, flag_e = 0, part_ten = -1, number_pow = 0,
    part_point_ten = 0, temp_part_point;
    long double number = 0;
    long double *point_number = &number;
    char* point_str = (char *) str;
    is_ein_point(point_str, &number_pow, &flag_e);
    for (; *point_str != '\0'; point_str+=1) {
        if (*point_str == '.' || *point_str == ',') {
            flag_point = 1;
        } else if (*point_str >= '0' && *point_str <= '9') {
            if (flag_point) {
                part_point_ten++;
            } else {
                part_ten++;
            }
        }
    }
    point_str = buffered;
    temp_part_point = part_point_ten;
    flag_point = 0;
    while (*point_str != '\0') {
        if (*point_str == '.' || *point_str == ',')
            flag_point = 1;
        if (*point_str >= '0' && *point_str <= '9') {
            double digit = *point_str - '0';
            if (flag_point && !flag_e) {
                number += digit / pow(10, temp_part_point - part_point_ten + 1);
                part_point_ten--;
            } else {
                if (part_ten > 0) {
                    number += digit * pow(10, part_ten);
                } else if (part_ten == 0) {
                    number += digit;
                }
                part_ten--;
            }
        }
        point_str+=1;
    }
    if (flag_e < 0)
        number /= pow(10, number_pow);
    else if (flag_e > 0)
        number *= pow(10, number_pow);
    return point_number;
}

void is_ein_point(char *str, int *number_pow, int *flag_e) {
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
        point_str +=1;
    }
}

s21_size_t parse_address(char* str) {
    s21_size_t address = 0;
    while (*str == ' ')
        str++;
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
        str += 2;
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
        else
            address /= 16;
        address += digit;
        str++;
    }
    return address;
}

int parse_n (char *full_form, va_list args) {
    int count = 0;
    char* formatPtr = full_form;
    char* inputPtr = full_form;
    while (*inputPtr != '\0') {
        if (*inputPtr == '%' && *(inputPtr + 1) == 'n') {
            int len = inputPtr - formatPtr;
            char temp[len + 1];
            s21_strncpy(temp, formatPtr, len);
            temp[len] = '\0';
            int readCount = s21_strlen(temp);
            int* countPtr = va_arg(args, int*);
            *countPtr = readCount;
            inputPtr += 2;
            formatPtr = inputPtr;
            count += readCount;
        } else {
            inputPtr++;
        }
    }
    return count;
}

long long int getHex(char* point_buf, int part_ten) {
    int digit = 0;
    if (*point_buf >= '0' && *point_buf <= '9')
        digit = *point_buf - '0';
    else if (*point_buf >= 'A' && *point_buf <= 'F')
        digit = *point_buf - 'A' + 10;
    else if (*point_buf >= 'a' && *point_buf <= 'f')
        digit = *point_buf - 'a' + 10;
    long long int summa = digit * pow(16, part_ten);
    return summa;
}

long long int getEight(char* point_buf, int part_ten) {
    int digit = *point_buf - '0';
    long long int summa = digit * pow(8, part_ten);
    return summa;
}
