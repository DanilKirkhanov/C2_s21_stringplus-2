#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int lenght = 0;
  while (!s21_strchr(str2, *str1) && *str1 != '\0') {
    str1++;
    lenght += 1;
  }
  return lenght;
}

// s21_size_t s21_strcspn(const char *str1, const char *str2) {
//   int strOneLenght = s21_strlen(str1);
//   int strTwoLenght = s21_strlen(str2);

//   int i = 0;
//   while (i < strOneLenght) {
//     int j = 0;
//     i += 1;
//     while (j < strTwoLenght) {
//       j += 1;
//       if (strOneLenght[i] == strTwoLenght[j]) return i;
//     }
//   }
//   return i;
//   }
// unsigned char *point_str1 = (unsigned char *)str1;
// unsigned char *point_str2 = (unsigned char *)str2;
// s21_size_t i = 0;
// while (*point_str2 != '\0') {
//   if (*point_str1 == *point_str2) break;
//   i+=1;
//   point_str1+=1;
//   point_str2+=1;
// }
//   return i;
// }

// s21_size_t s21_strcspn(const char *str1, const char *str2) {
//      int len1 = s21_strlen(str1);
//      int len2 = s21_strlen(str2);
//      int i;
//      for (i = 0; i < len1; i++)
//          for (int j = 0; j < len2; j++)
//              if (str1[i] == str2[j]) return i;
//      return i;
// }