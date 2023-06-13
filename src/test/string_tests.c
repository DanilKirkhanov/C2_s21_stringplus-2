#include <check.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

START_TEST(memchr_test) {
  char testOne[15] = "Patrick Bateman";
  char testTwo[15] = "Patrickk\n\0";
  char testThree[15] = "k\n\0";
  char testFour[9] = "694201337";
  char testFive[0] = '\0';
  char testSix[11] = "aaaaaaa!!!!";
  char testSeven[1] = "\n";
  char testEight[1] = ' ';
  char testNine[0] = "";

  ck_assert_ptr_eq(s21_memchr(testOne, 'B', 15), memchr(testOne, 'B', 15));
  ck_assert_ptr_eq(s21_memchr(testTwo, 'k', 9), memchr(testTwo, 'k', 9));
  ck_assert_ptr_eq(s21_memchr(testThree, '\n', 2), memchr(testThree, '\n', 2));
}
END_TEST

int main() {
  int no_failed = 0;
  Suite *s = suite_create("StrT");
  //   TCase *tc = tcase_create("StrT");
  SRunner *runner = srunner_create(s);

  TCase *tc_memchr;
  tc_memchr = tcase_create("memchr test");
  suite_add_tcase(s, tc_memchr);
  tcase_add_test(tc_memchr, memchr_test);
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
