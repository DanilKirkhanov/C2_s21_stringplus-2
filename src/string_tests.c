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
END_TEST

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
END_TEST

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
  ck_assert_pstr_eq(s21_memmove(&testSOne[4], testSOne, 31),
                    memmove(&testSTwo[4], testSTwo, 31));

  char testSThree[50] = "Hello Moto";
  char testSFour[50] = "Hello Moto";
  ck_assert_pstr_eq(s21_memmove(testSThree + 4, testSThree, 10),
                    memmove(testSFour + 4, testSFour, 10));
  ck_assert_pstr_eq(s21_memmove(testSThree + 10, testSThree, 10),
                    memmove(testSFour + 10, testSFour, 10));

  char testSFive[] = "Hello Moto\n\0";
  char testSSix[] = "Hello Moto\n\0";
  char random[] = "Patrick Ba\n\0";
  char randomOne[] = "12345678910111213";
  ck_assert_pstr_eq(s21_memmove(testSFive, random, 13),
                    memmove(testSSix, random, 13));
  ck_assert_pstr_eq(s21_memmove(testSFive, randomOne, 5),
                    memmove(testSSix, randomOne, 5));

  char testSEight[] = "\0";
  char randomTwo[] = "\0";
  ck_assert_pstr_eq(s21_memmove(testSEight, randomTwo, 2),
                    memmove(testSEight, randomTwo, 2));
  ck_assert_pstr_eq(s21_memmove(testSEight, randomTwo, 0),
                    memmove(testSEight, randomTwo, 0));
}
END_TEST

START_TEST(memset_test) {
  char tOne[] = "Patrick Bateman\n\0";
  char tTwo[] = "Patrick Bateman\n\0";

  ck_assert_pstr_eq(s21_memset(tOne, '*', 8), memset(tTwo, '*', 8));
  ck_assert_pstr_eq(s21_memset(tOne, '-', 8), memset(tTwo, '-', 8));
  ck_assert_pstr_eq(s21_memset(tOne, '|', 8), memset(tTwo, '|', 8));

  char tThree[] = "Patrick420\0";
  char tFour[] = "Patrick420\0";

  ck_assert_pstr_eq(s21_memset(tThree, '*', 8), memset(tFour, '*', 8));
  ck_assert_pstr_eq(s21_memset(tThree, '-', 8), memset(tFour, '-', 8));
  ck_assert_pstr_eq(s21_memset(tThree, '|', 8), memset(tFour, '|', 8));

  char tFive[] = " \n\0";
  char tSix[] = " \n\0";

  ck_assert_pstr_eq(s21_memset(tFive, '*', 1), memset(tSix, '*', 1));
  ck_assert_pstr_eq(s21_memset(tFive, '-', 1), memset(tSix, '-', 1));
  ck_assert_pstr_eq(s21_memset(tFive, '|', 1), memset(tSix, '|', 1));

  char tSeven[] = "1\n\0";
  char tEight[] = "1\n\0";

  ck_assert_pstr_eq(s21_memset(tSeven, '*', 2), memset(tEight, '*', 2));
  ck_assert_pstr_eq(s21_memset(tSeven, '-', 2), memset(tEight, '-', 2));
  ck_assert_pstr_eq(s21_memset(tSeven, '|', 2), memset(tEight, '|', 2));

  char tNine[] = "\n\0";
  char tTen[] = "\n\0";

  ck_assert_pstr_eq(s21_memset(tNine, '*', 2), memset(tTen, '*', 2));
  ck_assert_pstr_eq(s21_memset(tNine, '-', 2), memset(tTen, '-', 2));
  ck_assert_pstr_eq(s21_memset(tNine, '|', 2), memset(tTen, '|', 2));

  char tEl[] = "\0";
  char tTwe[] = "\0";

  ck_assert_pstr_eq(s21_memset(tEl, '*', 1), memset(tTwe, '*', 1));
  ck_assert_pstr_eq(s21_memset(tEl, '-', 1), memset(tTwe, '-', 1));
  ck_assert_pstr_eq(s21_memset(tEl, '|', 1), memset(tTwe, '|', 1));
  // ck_assert_pstr_eq(s21_memset(tEl, '*', 2), memset(tTwe, '*', 2));
  ck_assert_pstr_eq(s21_memset(tEl, '|', 0), memset(tTwe, '|', 0));

  char whatevsOne[22] = "home sweet home 10 12";
  char whatevsTwo[15] = "home sour home";

  ck_assert_pstr_eq(s21_memset(whatevsOne, '1', 15),
                    memset(whatevsOne, '1', 15));
  ck_assert_pstr_eq(s21_memset(whatevsOne, '\0', 15),
                    memset(whatevsOne, '\0', 15));
  ck_assert_pstr_eq(s21_memset(whatevsTwo, '1', 14),
                    memset(whatevsTwo, '1', 14));
  ck_assert_pstr_eq(s21_memset(whatevsTwo, '\0', 14),
                    memset(whatevsTwo, '\0', 14));
}
END_TEST

START_TEST(strcat_test) {
  char t[100] = "Hi, my name is Van, I'm an artist.\0";
  char tOne[100] = "Hi, my name is Van, I'm an artist.\0";
  char string[25] = "I'm a perfomance artist\0";

  ck_assert_pstr_eq(s21_strcat(t, string), strcat(tOne, string));

  char tTwo[100] = "I'm hired to fulfill their fantasies.\0";
  char tThree[100] = "I'm hired to fulfill their fantasies.\0";
  char stringTwo[28] = "Their deep dark fantasies.\0";

  ck_assert_pstr_eq(s21_strcat(tTwo, stringTwo), strcat(tThree, stringTwo));

  char tFour[100] = "I was gonna be a movie star y'know,\n\0";
  char tFive[100] = "I was gonna be a movie star y'know,\n\0";
  char stringThree[23] = "modeling and acting.\n\0";
  char stringFour[37] = "I was gonna be a movie star y'know\n\0";

  ck_assert_pstr_eq(s21_strcat(tFour, stringThree), strcat(tFive, stringThree));
  ck_assert_pstr_eq(s21_strcat(tFour, stringFour), strcat(tFive, stringFour));

  char tSix[50] = " \n\0";
  char tSeven[50] = " \n\0";
  char stringFive[50] = " \n\0";

  ck_assert_pstr_eq(s21_strcat(tSix, stringFive), strcat(tSeven, stringFive));

  char tEight[50] = "\n\0";
  char tNine[50] = "\n\0";
  char stringSix[50] = "\n\0";

  ck_assert_pstr_eq(s21_strcat(tEight, stringSix), strcat(tNine, stringSix));

  char tTen[50] = "\0";
  char tEl[50] = "\0";
  char stringSeven[50] = "\0";

  ck_assert_pstr_eq(s21_strcat(tTen, stringSeven), strcat(tEl, stringSeven));

  char forEmpty[260] =
      "After a hundred and two auditions and small parts I decided y'know I "
      "had enough, Then I got in to Escort world.";
  char forEmptyOne[260] =
      "After a hundred and two auditions and small parts I decided y'know I "
      "had enough, Then I got in to Escort world.";
  char random[2] = " ";
  char randomOne[145] =
      "The client requests contain a lot of fetishes, so I just decided to go "
      "y'know... full ♂Master♂ and change my entire house into a dungeon...";

  ck_assert_pstr_eq(s21_strcat(forEmpty, random), strcat(forEmptyOne, random));
  ck_assert_pstr_eq(s21_strcat(forEmpty, randomOne),
                    strcat(forEmptyOne, randomOne));
}
END_TEST

int main() {
  // runner init
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

  // memset
  TCase *tc_memset;
  tc_memset = tcase_create("memset test");
  suite_add_tcase(s, tc_memset);
  tcase_add_test(tc_memset, memset_test);

  // strcat
  TCase *tc_strcat;
  tc_strcat = tcase_create("strcat test");
  suite_add_tcase(s, tc_strcat);
  tcase_add_test(tc_strcat, strcat_test);

  // runner
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}