#include <math.h>
#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
    int result = 0;
    char *full_form = (char *) format;
    TypeFormat typeFormat[1];
    va_list args;
    va_start(args, format);
    while (*format) {
        if (*format == '%' || typeFormat[0].flag_proc) {
            set_flags(typeFormat, *format);
            if (typeFormat[0].flag_star) {
                str = parse_star((char *) str);
            }
            if (!typeFormat[0].flag_star) {
                result = parse_form(typeFormat, (char*) str, args, full_form);
            }
        }
    }
    return result;
}
void set_flags(TypeFormat *typeFormat, char format)
 {
    if (format == 'c') typeFormat->flag_c;
    else if (format == 'd') typeFormat->flag_d;
    else if (format == 'i') typeFormat->flag_i;
    else if (format == 'e') typeFormat->flag_e;
    else if (format == 'E') typeFormat->flag_E;
    else if (format == 'f') typeFormat->flag_f;
    else if (format == 'g') typeFormat->flag_g;
    else if (format == 'G') typeFormat->flag_G;
    else if (format == 'o') typeFormat->flag_o;
    else if (format == 's') typeFormat->flag_s;
    else if (format == 'u') typeFormat->flag_u;
    else if (format == 'x') typeFormat->flag_x;
    else if (format == 'X') typeFormat->flag_X;
    else if (format == 'p') typeFormat->flag_p;
    else if (format == 'n') typeFormat->flag_n;
    else if (format == '%') typeFormat->flag_proc;
    else if (format >= '0' && format <= '9') typeFormat->flag_number;
    else if (format == '*') typeFormat->flag_star;
    else if (format == 'h') typeFormat->flag_h;
    else if (format == 'l') typeFormat->flag_l;
    else if (format == 'L') typeFormat->flag_L;
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
    if (typeFormat->flag_c) {
        if (str != NULL) result +=1;
        *va_arg(args, char *) = *str;
    }
    else if (typeFormat->flag_d || typeFormat->flag_l) {
        *va_arg(args, int *) = parse_digit(typeFormat, str, full_form);
        result+=1;
    }
    else if () {

    }
    return result;
}

void parse_weight(char *str, char *format) {
    int width = 0;
    int length = s21_strlen(str);
    char* point_format = format;

    while (*format != '\0') {
        if (*format >= '0' && *format <= '9')
            width = width * 10 + (*format - '0');
        format++;
    }

    char* point_str = buffered;

    if (length < width) {
        while (length < width) {
            *point_str = ' ';
            point_str++;
            length++;
        }
    } else if (length > width) {
        point_str += width;
        *point_str = '\0';
    }
}

long long int parse_digit(TypeFormat *typeFormat, char *str, char *full_form) {
    if (format->flag_number) parse_weight(str, full_form);
    long long int number = 0;
    int flag_8 = 0, flag_16 = 0, digit, part_ten = -1;
    while (*str != '\0') {
        if (*str == ' ' || *str == '\n')
            break;
        if (*str == '0' && part_ten == -1 && (*typeFormat->flag_d || *typeFormat->flag_i)) {
            if (*(str + 1) == 'x') {
                flag_16 = 1;
                part_ten += 1;
            } else
                flag_8 = 1;
            str--;
        }
        if ((*str >= '0' && ((*typeFormat->flag_d && *str <= '9') || (flag_8 && *str <= '7'))) ||
            (flag_16 && ((*str >= 'A' && *str <= 'F') || (*str >= 'a' && *str <= 'f')))) {
            if (!flag_8 && !flag_16) {
                digit = *str - '0';
                if (part_ten > 0)
                    number += digit * pow(10, part_ten);
                else
                    number += digit;
            } else if (flag_8 && *str >= '0' && *str <= '7') {
                digit = *str - '0';
                number = number * 8 + digit;
            } else if (flag_16) {
                if (*str >= 'A' && *str <= 'F')
                    digit = *str - 'A' + 10;
                else if (*str >= 'a' && *str <= 'f')
                    digit = *str - 'a' + 10;
                else
                    digit = *str - '0';
                number = number * 16 + digit;
            }
            part_ten += 1;
        }
        str++;
    }
    return number;
}

//long long int getHex(char *point_buf, int digit, unsigned long long int summa, int part_ten) {
//    if (*point_buf >= '0' && *point_buf <= '9')
//        digit = *point_buf - '0';
//    else if (*point_buf >= 'A' && *point_buf <= 'F')
//        digit = *point_buf - 'A' + 10;
//    else if (*point_buf >= 'a' && *point_buf <= 'f')
//        digit = *point_buf - 'a' + 10;
//    summa = summa + digit * pow(16, part_ten);
//    return summa;
//}
//
//long long int getEight(char *point_buf, int digit, unsigned long long int summa,
//                       int part_ten) {
//    digit = *point_buf - '0';
//    summa = summa + digit * pow(8, part_ten);
//    return summa;
//}

