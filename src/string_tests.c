#include <check.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"

START_TEST(memchr_test) {
  char testOne[15] = "Patrick Bateman";
  char testTwo[15] = "Patrickk\n\0";
  char testThree[15] = "k\n\0";
  char testFour[9] = "694201337";
  char testFive[10] = "\0";
  char testSix[11] = "aaaaaaa!!!!";
  char testSeven[2] = " \n";
  char testEight[1] = " ";

  ck_assert_ptr_eq(s21_memchr(testOne, 'B', 15), memchr(testOne, 'B', 15));
  // ck_assert_ptr_eq(s21_memchr(testOne, '8', 15), memchr(testOne, '8', 15));
  ck_assert_ptr_eq(s21_memchr(testTwo, 'k', 9), memchr(testTwo, 'k', 9));
  ck_assert_ptr_eq(s21_memchr(testThree, '\n', 2), memchr(testThree, '\n', 2));
  ck_assert_ptr_eq(s21_memchr(testFour, '2', 9), memchr(testFour, '2', 9));
  ck_assert_ptr_eq(s21_memchr(testFive, ' ', 0), memchr(testFive, ' ', 0));
  ck_assert_ptr_eq(s21_memchr(testSix, '!', 11), memchr(testSix, '!', 11));
  ck_assert_ptr_eq(s21_memchr(testSeven, '\n', 2), memchr(testSeven, '\n', 2));
  ck_assert_ptr_eq(s21_memchr(testEight, ' ', 1), memchr(testEight, ' ', 1));
}
END_TEST

START_TEST(memcpy_test) {
  char s[100] = "asdasdasdasd;c";
  char sTwo[100] = "PatrickBateman\n\0";

  char dOne[100] = "Sweet home Alabama\0";
  char origOne[100] = "Sween home Alabama\0";

  char dTwo[100] = {0};
  char origTwo[100] = {0};

  char dThree[100] = "1241241241241241212sdadas\n\0";
  char origThree[100] = "1241241241241241212sdadas\n\0";

  char dFour[100] = " \n\0";
  char origFour[100] = " \n\0";

  char dFive[100] = " \0";
  char origFive[100] = " \0";

  char dSix[100] = "Ominous\n\0";
  char origSix[100] = "Ominous\n\0";

  char dSeven[100] = "\n\0";
  char origSeven[100] = "\n\0";

  char dEight[100] = "Ominous music\0";
  char origEight[100] = "Ominous music\0";

  ck_assert_str_eq(s21_memcpy(dOne, s, 14), memcpy(origOne, s, 14));
  ck_assert_str_eq(s21_memcpy(dTwo, s, 7), memcpy(origTwo, s, 7));
  ck_assert_str_eq(s21_memcpy(dTwo, s, 100), memcpy(origTwo, s, 100));
  ck_assert_str_eq(s21_memcpy(dThree, s, 14), memcpy(origThree, s, 14));
  ck_assert_str_eq(s21_memcpy(dFour, sTwo, 15), memcpy(origFour, sTwo, 15));
  ck_assert_str_eq(s21_memcpy(dFive, sTwo, 15), memcpy(origFive, sTwo, 15));
  ck_assert_str_eq(s21_memcpy(dSix, sTwo, 5), memcpy(origSix, sTwo, 5));
  ck_assert_str_eq(s21_memcpy(dSeven, sTwo, 15), memcpy(origSeven, sTwo, 15));
  ck_assert_str_eq(s21_memcpy(dEight, sTwo, 15), memcpy(origEight, sTwo, 15));
}

START_TEST(memcmp_test) {
  char sOne[10] = "HELLO";
  char dOne[10] = "Hello";

  char sTwo[50] = "The first string for testing";
  char dTwo[50] = "The second string for testin";

  char sThree[50] = "1241613413";
  char dThree[50] = "1241613413";

  char sFour[50] = "\0";
  char dFour[50] = "\0";

  char sFive[50] = "1\n\0";
  char dFive[50] = "1\n\0";

  char testOne[50] = "\0";
  char testTwo[50] = " \n\0";
  char testThree[50] = "\n\0";
  char testFour[50] = "b\0";
  char testSix[50] = "Alpha Chad";
  char testSeven[50] = "Alpha Chad\0";

  ck_assert_int_eq(s21_memcmp(sOne, dOne, 2), memcmp(sOne, dOne, 2));
  ck_assert_int_eq(s21_memcmp(sTwo, dTwo, 5), memcmp(sTwo, dTwo, 5));
  ck_assert_int_eq(s21_memcmp(sThree, dThree, 10), memcmp(sThree, dThree, 10));
  ck_assert_int_eq(s21_memcmp(sFour, dFour, 1), memcmp(sFour, dFour, 1));
  ck_assert_int_eq(s21_memcmp(sFive, dFive, 1), memcmp(sFive, dFive, 1));
  ck_assert_int_eq(s21_memcmp(testOne, "", 1), memcmp(testOne, "", 1));
  ck_assert_int_eq(s21_memcmp(testTwo, " \n\0", 3),
                   memcmp(testTwo, " \n\0", 3));
  ck_assert_int_eq(s21_memcmp(testThree, testTwo, 1),
                   memcmp(testThree, testTwo, 1));
  ck_assert_int_eq(s21_memcmp(testFour, "b\0", 1), memcmp(testFour, "b\0", 1));
  ck_assert_int_eq(s21_memcmp(testSix, testSeven, 10),
                   memcmp(testSix, testSeven, 10));
}

START_TEST(memmove_test) {
  char sOne[10] = "alabama123";
  char dOne[10] = "45678910";
  char dTwo[10] = "sweet home";

  ck_assert_pstr_eq(s21_memmove(dOne, sOne, 10), memmove(dOne, sOne, 10));
  ck_assert_pstr_eq(s21_memmove(dOne, sOne, 1), memmove(dOne, sOne, 1));
  ck_assert_pstr_eq(s21_memmove(dTwo, sOne, 10), memmove(dTwo, sOne, 10));
  ck_assert_pstr_eq(s21_memmove(dOne, sOne, 5), memmove(dOne, sOne, 5));

  char destOne[] = "0000000000";
  char sourOne[] = "12523523";
  char destTwo[] = "1,2,3,4,5,6,7,8,9";
  char sourTwo[] = "1,2,3,4,5,6,7,8,9";
  char destThree[50] = {0};
  char sourThree[] = "\n\0";
  char sourFour[] = "qkrjhqkwjrndaksd;zx.c,zxc/aweafqwrt315";

  ck_assert_pstr_eq(s21_memmove(destOne, sourOne, 8),
                    memmove(destOne, sourOne, 8));
  ck_assert_pstr_eq(s21_memmove(destOne, sourTwo, 10),
                    memmove(destOne, sourTwo, 10));
  ck_assert_pstr_eq(s21_memmove(destTwo, sourTwo, 17),
                    memmove(destTwo, sourTwo, 17));
  ck_assert_pstr_eq(s21_memmove(destThree, sourFour, 1),
                    memmove(destThree, sourFour, 1));
  ck_assert_pstr_eq(s21_memmove(destTwo, sourThree, 3),
                    memmove(destTwo, sourThree, 3));

  char testSOne[50] = "Understandable, have a nice day";
  char testSTwo[50] = "Understandable, have a nice day";
  ck_assert_pstr_eq(s21_memmove(&testSOne[4], testSOne, 31), memmove(&testSTwo[4], testSTwo, 31));

  char testSThree[50] = "Hello Moto";
  char testSFour[50] = "Hello Moto";
  ck_assert_pstr_eq(s21_memmove(testSThree + 4, testSThree, 10), memmove(testSFour + 4, testSFour, 10));
}

int main() {
  int no_failed = 0;
  Suite *s = suite_create("StrT");
  SRunner *runner = srunner_create(s);

  // memchr
  TCase *tc_memchr;
  tc_memchr = tcase_create("memchr test");
  suite_add_tcase(s, tc_memchr);
  tcase_add_test(tc_memchr, memchr_test);

  // memcpy
  TCase *tc_memcpy;
  tc_memcpy = tcase_create("memcpy test");
  suite_add_tcase(s, tc_memcpy);
  tcase_add_test(tc_memcpy, memcpy_test);

  // memcmp
  TCase *tc_memcmp;
  tc_memcmp = tcase_create("memcmp test");
  suite_add_tcase(s, tc_memcmp);
  tcase_add_test(tc_memcmp, memcmp_test);

  // memmove
  TCase *tc_memmove;
  tc_memmove = tcase_create("memmove test");
  suite_add_tcase(s, tc_memmove);
  tcase_add_test(tc_memmove, memmove_test);

  // runner
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
