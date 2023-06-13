#include <string.h>
#include "s21_string.h"
#include <check.h> 
#include <wchar.h>

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
  //ck_assert_ptr_eq(s21_memchr(testOne, '8', 15), memchr(testOne, '8', 15));
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
  char source[100] = "asdasdasdasd;c";
  char sourceTwo[100] = "PatrickBateman\n\0";

  char destinationOne[100] = "Sweet home Alabama\0";
  char forOriginalOne[100] = "Sween home Alabama\0";

  char destinationTwo[100] = {0};
  char forOriginalTwo[100] = {0};

  char destinationThree[100] = "1241241241241241212sdadas\n\0";
  char forOriginalThree[100] = "1241241241241241212sdadas\n\0";

  char destinationFour[100] = " \n\0";
  char forOriginalFour[100] = " \n\0";

  char destinationFive[100] = " \0";
  char forOriginalFive[100] = " \0";

  char destinationSix[100] = "Ominous\n\0";
  char forOriginalSix[100] = "Ominous\n\0";

  char destinationSeven[100] = "\n\0";
  char forOriginalSeven[100] = "\n\0";

  char destinationEight[100] = "Ominous music\0";
  char forOriginalEight[100] = "Ominous music\0";

  ck_assert_str_eq(s21_memcpy(destinationOne, source, 14), memcpy(forOriginalOne, source, 14));
  ck_assert_str_eq(s21_memcpy(destinationTwo, source, 7), memcpy(forOriginalTwo, source, 7));
  ck_assert_str_eq(s21_memcpy(destinationThree, source, 14), memcpy(forOriginalThree, source, 14));
  ck_assert_str_eq(s21_memcpy(destinationFour, sourceTwo, 15), memcpy(forOriginalFour, sourceTwo, 15));
  ck_assert_str_eq(s21_memcpy(destinationFive, sourceTwo, 15), memcpy(forOriginalFive, sourceTwo, 15));
  ck_assert_str_eq(s21_memcpy(destinationSix, sourceTwo, 5), memcpy(forOriginalSix, sourceTwo, 5));
  ck_assert_str_eq(s21_memcpy(destinationSeven, sourceTwo, 15), memcpy(forOriginalSeven, sourceTwo, 15));
  ck_assert_str_eq(s21_memcpy(destinationEight, sourceTwo, 15), memcpy(forOriginalEight, sourceTwo, 15));
}

int main() {
  int no_failed = 0;
  Suite *s = suite_create("StrT");
  //   TCase *tc = tcase_create("StrT");
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


// runner
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

