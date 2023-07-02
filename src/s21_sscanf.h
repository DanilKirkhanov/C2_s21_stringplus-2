#ifndef C2_S21_STRINGPLUS_2_S21_SSCANF_H
#define C2_S21_STRINGPLUS_2_S21_SSCANF_H
#include <stdio.h>
#include <stdarg.h>
#include "s21_string.h"

// typedef unsigned long int s21_size_t;

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

void defualt_typeformat(TypeFormat *typeFormat) {
    typeFormat->specificator = 0;
    typeFormat->weight_number = 0;
    typeFormat->weight_star = 0;
    typeFormat->length = 0;
    typeFormat->length_h = 0;
    typeFormat->length_l = 0;
    typeFormat->length_L = 0;
}

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


#endif
