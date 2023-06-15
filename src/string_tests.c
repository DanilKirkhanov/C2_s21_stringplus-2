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
  ck_assert_str_eq(s21_memcpy(destinationTwo, source, 100), memcpy(forOriginalTwo, source, 100));
  ck_assert_str_eq(s21_memcpy(destinationThree, source, 14), memcpy(forOriginalThree, source, 14));
  ck_assert_str_eq(s21_memcpy(destinationFour, sourceTwo, 15), memcpy(forOriginalFour, sourceTwo, 15));
  ck_assert_str_eq(s21_memcpy(destinationFive, sourceTwo, 15), memcpy(forOriginalFive, sourceTwo, 15));
  ck_assert_str_eq(s21_memcpy(destinationSix, sourceTwo, 5), memcpy(forOriginalSix, sourceTwo, 5));
  ck_assert_str_eq(s21_memcpy(destinationSeven, sourceTwo, 15), memcpy(forOriginalSeven, sourceTwo, 15));
  ck_assert_str_eq(s21_memcpy(destinationEight, sourceTwo, 15), memcpy(forOriginalEight, sourceTwo, 15));
}

START_TEST(memcmp_test) {
  char sourceOne[10] = "HELLO";
  char destinOne[10] = "Hello";

  char sourceTwo[50] = "The first string for testing";
  char destinTwo[50] = "The second string for testin";

  char sourceThree[50] = "1241613413";
  char destinThree[50] = "1241613413";

  char sourceFour[50] = "\0";
  char destinFour[50] = "\0";
  
  char sourceFive[50] = "1\n\0";
  char destinFive[50] = "1\n\0";

  char testOne[50] = "\0";
  char testTwo[50] = " \n\0";
  char testThree[50] = "\n\0";
  char testFour[50] = "b\0";
  char testSix[50] = "Alpha Chad";
  char testSeven[50] = "Alpha Chad\0";

  ck_assert_int_eq(s21_memcmp(sourceOne, destinOne, 2), memcmp(sourceOne, destinOne, 2));
  ck_assert_int_eq(s21_memcmp(sourceTwo, destinTwo, 5), memcmp(sourceTwo, destinTwo, 5));
  ck_assert_int_eq(s21_memcmp(sourceThree, destinThree, 10), memcmp(sourceThree, destinThree, 10));
  ck_assert_int_eq(s21_memcmp(sourceFour, destinFour, 1), memcmp(sourceFour, destinFour, 1));
  ck_assert_int_eq(s21_memcmp(sourceFive, destinFive, 1), memcmp(sourceFive, destinFive, 1));
  ck_assert_int_eq(s21_memcmp(testOne, "", 1), memcmp(testOne, "", 1));
  ck_assert_int_eq(s21_memcmp(testTwo, " \n\0", 3), memcmp(testTwo, " \n\0", 3));
  ck_assert_int_eq(s21_memcmp(testThree, testTwo, 1), memcmp(testThree, testTwo, 1));
  ck_assert_int_eq(s21_memcmp(testFour, "b\0", 1), memcmp(testFour, "b\0", 1));
  ck_assert_int_eq(s21_memcmp(testSix, testSeven, 10), memcmp(testSix, testSeven, 10));

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

// memcmp
  TCase *tc_memcmp;
  tc_memcmp = tcase_create("memcmp test");
  suite_add_tcase(s, tc_memcmp);
  tcase_add_test(tc_memcmp, memcmp_test);


// runner
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

