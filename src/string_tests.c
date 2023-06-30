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
  char stringSeven[2] = "\0";

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

START_TEST(strncat_test) {
  // char possOverlap[] = "This is a string\0XXX";
  // char possOverlap1[] = "This is a string\0XXX";
  // ck_assert_pstr_eq(s21_strncat(possOverlap, possOverlap + 1, 10),
  // strncat(possOverlap1, possOverlap1 + 1, 10));

  char t[100] = "Hi, my name is Van, I'm an artist.\0";
  char tOne[100] = "Hi, my name is Van, I'm an artist.\0";
  char string[25] = "I'm a perfomance artist\0";

  ck_assert_pstr_eq(s21_strncat(t, string, 25), strncat(tOne, string, 25));

  char tTwo[100] = "I'm hired to fulfill their fantasies.\0";
  char tThree[100] = "I'm hired to fulfill their fantasies.\0";
  char stringTwo[28] = "Their deep dark fantasies.\0";

  ck_assert_pstr_eq(s21_strncat(tTwo, stringTwo, 28),
                    strncat(tThree, stringTwo, 28));

  char tFour[100] = "I was gonna be a movie star y'know,\n\0";
  char tFive[100] = "I was gonna be a movie star y'know,\n\0";
  char stringThree[23] = "modeling and acting.\n\0";
  char stringFour[37] = "I was gonna be a movie star y'know\n\0";

  ck_assert_pstr_eq(s21_strncat(tFour, stringThree, 23),
                    strncat(tFive, stringThree, 23));
  ck_assert_pstr_eq(s21_strncat(tFour, stringFour, 37),
                    strncat(tFive, stringFour, 37));

  char tSix[50] = " \n\0";
  char tSeven[50] = " \n\0";
  char stringFive[] = " \n\0";

  ck_assert_pstr_eq(s21_strncat(tSix, stringFive, 4),
                    strncat(tSeven, stringFive, 4));

  char tEight[50] = "\n\0";
  char tNine[50] = "\n\0";
  char stringSix[50] = "\n\0";

  ck_assert_pstr_eq(s21_strncat(tEight, stringSix, 4),
                    strncat(tNine, stringSix, 4));

  char tTen[50] = "\0";
  char tEl[50] = "\0";
  char stringSeven[2] = "\0";

  ck_assert_pstr_eq(s21_strncat(tTen, stringSeven, 2),
                    strncat(tEl, stringSeven, 2));

  char forEmpty[700] =
      "♂Dungeon♂Master♂ now with a full dungeon in my house and It's going "
      "really well. ";
  char forEmptyOne[700] =
      "♂Dungeon♂Master♂ now with a full dungeon in my house and It's going "
      "really well. ";
  char random[168] =
      "Fisting is 300 bucks and usually the guy is pretty much hard on pop to "
      "get really relaxed y'know and I have this long latex glove that goes "
      "all the way up to my armpit";
  char randomOne[90] =
      "and it's a long process y'know to get your whole arm up there but it's "
      "an intense feeling";

  ck_assert_pstr_eq(s21_strncat(forEmpty, random, 168),
                    strncat(forEmptyOne, random, 168));
  ck_assert_pstr_eq(s21_strncat(forEmpty, randomOne, 90),
                    strncat(forEmptyOne, randomOne, 90));

  // char Alabama[] = "My name is Patrick Bateman. I'm 27 years old.";
  // ck_assert_pstr_eq(s21_strncat(Alabama, Alabama, 44), strncat(Alabama,
  // Alabama, 44));
}

START_TEST(strchr_test) {
  char source[] = "for the other person I think for myself too";
  ck_assert_pstr_eq(s21_strchr(source, 12), strchr(source, 12));
  ck_assert_pstr_eq(s21_strchr(source, 'o'), strchr(source, 'o'));
  ck_assert_pstr_eq(s21_strchr(source, '\0'), strchr(source, '\0'));
  ck_assert_pstr_eq(s21_strchr(source, 'I'), strchr(source, 'I'));
  ck_assert_pstr_eq(s21_strchr(source, 'f'), strchr(source, 'f'));
  ck_assert_pstr_eq(s21_strchr(source, 'q'), strchr(source, 'q'));

  char sourceT[] = " \n\0";
  ck_assert_pstr_eq(s21_strchr(sourceT, 3), strchr(sourceT, 3));
  ck_assert_pstr_eq(s21_strchr(sourceT, '\0'), strchr(sourceT, '\0'));
  ck_assert_pstr_eq(s21_strchr(sourceT, ' '), strchr(sourceT, ' '));
  ck_assert_pstr_eq(s21_strchr(sourceT, '\n'), strchr(sourceT, '\n'));

  char sourceY[] = "\0";
  ck_assert_pstr_eq(s21_strchr(sourceY, 1), strchr(sourceY, 1));
  ck_assert_pstr_eq(s21_strchr(sourceY, '\0'), strchr(sourceY, '\0'));
}

START_TEST(strrchr_test) {
  char source[] =
      "you go in places that even though it's physical with your hand";
  ck_assert_pstr_eq(s21_strrchr(source, 12), strrchr(source, 12));
  ck_assert_pstr_eq(s21_strrchr(source, 'h'), strrchr(source, 'h'));
  ck_assert_pstr_eq(s21_strrchr(source, '\0'), strrchr(source, '\0'));
  ck_assert_pstr_eq(s21_strrchr(source, 'i'), strrchr(source, 'i'));
  ck_assert_pstr_eq(s21_strrchr(source, 'p'), strrchr(source, 'p'));
  ck_assert_pstr_eq(s21_strrchr(source, 'q'), strrchr(source, 'q'));

  char sourceT[] = " \n\0";
  ck_assert_pstr_eq(s21_strrchr(sourceT, 3), strrchr(sourceT, 3));
  ck_assert_pstr_eq(s21_strrchr(sourceT, '\0'), strrchr(sourceT, '\0'));
  ck_assert_pstr_eq(s21_strrchr(sourceT, ' '), strrchr(sourceT, ' '));
  ck_assert_pstr_eq(s21_strrchr(sourceT, '\n'), strrchr(sourceT, '\n'));

  char sourceY[] = "\0";
  ck_assert_pstr_eq(s21_strrchr(sourceY, 1), strrchr(sourceY, 1));
  ck_assert_pstr_eq(s21_strrchr(sourceY, '\0'), strrchr(sourceY, '\0'));
}

START_TEST(strncmp_test) {
  char ex[] = "Jesse we need to cook";
  char exOne[] = "Jesse we need to cock";

  ck_assert_int_eq(s21_strncmp(ex, exOne, 22), strncmp(ex, exOne, 22));
  ck_assert_int_eq(s21_strncmp(ex, exOne, 21), strncmp(ex, exOne, 21));
  ck_assert_int_eq(s21_strncmp(ex, exOne, 10), strncmp(ex, exOne, 10));
  ck_assert_int_eq(s21_strncmp(ex, exOne, 2), strncmp(ex, exOne, 2));

  char exTwo[] = "abcdefg";
  char exThree[] = "12345678";
  ck_assert_int_eq(s21_strncmp(exTwo, exThree, 8), strncmp(exTwo, exThree, 8));
  ck_assert_int_eq(s21_strncmp(exTwo, exThree, 2), strncmp(exTwo, exThree, 2));

  char exFour[] = " \n\0";
  char exFive[] = " \n\0";
  ck_assert_int_eq(s21_strncmp(exFour, exFive, 4), strncmp(exFour, exFive, 4));

  char exSix[] = "\0";
  char exSeven[] = "\0";
  ck_assert_int_eq(s21_strncmp(exSix, exSeven, 2), strncmp(exSix, exSeven, 2));
  ck_assert_int_eq(s21_strncmp(exSix, exSeven, 1), strncmp(exSix, exSeven, 1));
  ck_assert_int_eq(s21_strncmp(exSix, exSeven, 0), strncmp(exSix, exSeven, 0));
}

START_TEST(strcmp_test) {
  char ex[] = "Jesse we need to cook";
  char exOne[] = "Jesse we need to cock";

  ck_assert_int_eq(s21_strcmp(ex, exOne), strcmp(ex, exOne));
  ck_assert_int_eq(s21_strcmp(ex, exOne), strcmp(ex, exOne));
  ck_assert_int_eq(s21_strcmp(ex, exOne), strcmp(ex, exOne));
  ck_assert_int_eq(s21_strcmp(ex, exOne), strcmp(ex, exOne));

  char r[] = "Identical one";
  char r2[] = "Identical one";
  ck_assert_int_eq(s21_strcmp(r, r2), strcmp(r, r2));

  char exTwo[] = "abcdefg";
  char exThree[] = "12345678";
  ck_assert_int_eq(s21_strcmp(exTwo, exThree), strcmp(exTwo, exThree));
  ck_assert_int_eq(s21_strcmp(exTwo, exThree), strcmp(exTwo, exThree));

  char exFour[] = " \n\0";
  char exFive[] = " \n\0";
  ck_assert_int_eq(s21_strcmp(exFour, exFive), strcmp(exFour, exFive));

  char exSix[] = "\0";
  char exSeven[] = "\0";
  ck_assert_int_eq(s21_strcmp(exSix, exSeven), strcmp(exSix, exSeven));
  ck_assert_int_eq(s21_strcmp(exSix, exSeven), strcmp(exSix, exSeven));
  ck_assert_int_eq(s21_strcmp(exSix, exSeven), strcmp(exSix, exSeven));
}

START_TEST(strncpy_test) {
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

  char r[] = "\0";
  char r1[] = "\0";

  ck_assert_str_eq(s21_strncpy(dOne, s, 14), strncpy(origOne, s, 14));
  ck_assert_str_eq(s21_strncpy(dTwo, s, 7), strncpy(origTwo, s, 7));
  ck_assert_str_eq(s21_strncpy(dTwo, s, 100), strncpy(origTwo, s, 100));
  ck_assert_str_eq(s21_strncpy(dThree, s, 14), strncpy(origThree, s, 14));
  ck_assert_str_eq(s21_strncpy(dFour, sTwo, 15), strncpy(origFour, sTwo, 15));
  ck_assert_str_eq(s21_strncpy(dFive, sTwo, 15), strncpy(origFive, sTwo, 15));
  ck_assert_str_eq(s21_strncpy(dSix, sTwo, 5), strncpy(origSix, sTwo, 5));
  ck_assert_str_eq(s21_strncpy(dSeven, sTwo, 15), strncpy(origSeven, sTwo, 15));
  ck_assert_str_eq(s21_strncpy(dEight, sTwo, 15), strncpy(origEight, sTwo, 15));
  ck_assert_str_eq(s21_strncpy(r, r1, 2), strncpy(r, r1, 2));
}

START_TEST(strcpy_test) {
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

  char r[] = "\0";
  char r1[] = "\0";

  ck_assert_str_eq(s21_strcpy(dOne, s), strcpy(origOne, s));
  ck_assert_str_eq(s21_strcpy(dTwo, s), strcpy(origTwo, s));
  ck_assert_str_eq(s21_strcpy(dTwo, s), strcpy(origTwo, s));
  ck_assert_str_eq(s21_strcpy(dThree, s), strcpy(origThree, s));
  ck_assert_str_eq(s21_strcpy(dFour, sTwo), strcpy(origFour, sTwo));
  ck_assert_str_eq(s21_strcpy(dFive, sTwo), strcpy(origFive, sTwo));
  ck_assert_str_eq(s21_strcpy(dSix, sTwo), strcpy(origSix, sTwo));
  ck_assert_str_eq(s21_strcpy(dSeven, sTwo), strcpy(origSeven, sTwo));
  ck_assert_str_eq(s21_strcpy(dEight, sTwo), strcpy(origEight, sTwo));
  ck_assert_str_eq(s21_strcpy(r, r1), strcpy(r, r1));
}

START_TEST(strcspn_test) {
  char source[] = "Use a Tracer object. Something like this: class Tracer";
  char comparison[] = "1234 \n\n\0 T\0";
  ck_assert_uint_eq(s21_strcspn(source, comparison),
                    strcspn(source, comparison));

  char sourceTwo[] = " \n \0";
  char comparisonTwo[] = "\0";

  ck_assert_uint_eq(s21_strcspn(sourceTwo, comparisonTwo),
                    strcspn(sourceTwo, comparisonTwo));

  char sourceThree[] = "\0";
  char comparisonThree[] = "\0";
  ck_assert_uint_eq(s21_strcspn(sourceThree, comparisonThree),
                    strcspn(sourceThree, comparisonThree));

  char sourceFour[] = "Zhongli";
  char doesntExist[] = "JesusChrist";
  ck_assert_uint_eq(s21_strcspn(sourceFour, doesntExist),
                    strcspn(sourceFour, doesntExist));
}

// START_TEST(strerror_test) {

// }

START_TEST(strlen_test) {
  char s[100] = "asdasdasdasd;c";
  char ass[100] = "asdasdasdasd;c";

  ck_assert_uint_eq(s21_strlen(s), strlen(ass));

  char sTwo[100] = "PatrickBateman\n\0";
  char assTwo[100] = "PatrickBateman\n\0";

  ck_assert_uint_eq(s21_strlen(sTwo), strlen(assTwo));

  char dOne[100] = "Sweet home Alabama\0";
  char origOne[100] = "Sween home Alabama\0";

  ck_assert_uint_eq(s21_strlen(dOne), strlen(origOne));

  char dTwo[100] = {0};
  char origTwo[100] = {0};

  ck_assert_uint_eq(s21_strlen(dTwo), strlen(origTwo));

  char dThree[100] = "1241241241241241212sdadas\n\0";
  char origThree[100] = "1241241241241241212sdadas\n\0";

  ck_assert_uint_eq(s21_strlen(dThree), strlen(origThree));

  char dFour[100] = " \n\0";
  char origFour[100] = " \n\0";

  ck_assert_uint_eq(s21_strlen(dFour), strlen(origFour));

  char dFive[100] = " \0";
  char origFive[100] = " \0";

  ck_assert_uint_eq(s21_strlen(dFive), strlen(origFive));

  char dSix[100] = "Ominous\n\0";
  char origSix[100] = "Ominous\n\0";

  ck_assert_uint_eq(s21_strlen(dSix), strlen(origSix));

  char dSeven[100] = "\n\0";
  char origSeven[100] = "\n\0";

  ck_assert_uint_eq(s21_strlen(dSeven), strlen(origSeven));

  char dEight[100] = "Ominous music\0";
  char origEight[100] = "Ominous music\0";

  ck_assert_uint_eq(s21_strlen(dEight), strlen(origEight));
}

START_TEST(strpbrk_test) {}

START_TEST(strspn_test) {
  char sOne[10] = "alabama123";
  char dOne[10] = "45678910";
  char dTwo[10] = "sweet home";

  char r[] = "ee";
  ck_assert_uint_eq(s21_strspn(sOne, r), strspn(sOne, r));
  ck_assert_uint_eq(s21_strspn(dOne, r), strspn(dOne, r));
  ck_assert_uint_eq(s21_strspn(dTwo, r), strspn(dTwo, r));

  char dFive[100] = " \0";
  char dSeven[100] = "\n\0";
  char t[] = "\0";

  ck_assert_uint_eq(s21_strspn(dFive, t), strspn(dFive, t));
  ck_assert_uint_eq(s21_strspn(dSeven, t), strspn(dSeven, t));
}

int main() {
  // runner init
  int no_failed = 0;
  Suite *s = suite_create("StrT");
  SRunner *runner = srunner_create(s);

  // 1 - memchr
  TCase *tc_memchr;
  tc_memchr = tcase_create("memchr test");
  suite_add_tcase(s, tc_memchr);
  tcase_add_test(tc_memchr, memchr_test);

  // 2 - memcpy
  TCase *tc_memcpy;
  tc_memcpy = tcase_create("memcpy test");
  suite_add_tcase(s, tc_memcpy);
  tcase_add_test(tc_memcpy, memcpy_test);

  // 3 - memcmp
  TCase *tc_memcmp;
  tc_memcmp = tcase_create("memcmp test");
  suite_add_tcase(s, tc_memcmp);
  tcase_add_test(tc_memcmp, memcmp_test);

  // 4 - memmove
  TCase *tc_memmove;
  tc_memmove = tcase_create("memmove test");
  suite_add_tcase(s, tc_memmove);
  tcase_add_test(tc_memmove, memmove_test);

  // 5 - memset
  TCase *tc_memset;
  tc_memset = tcase_create("memset test");
  suite_add_tcase(s, tc_memset);
  tcase_add_test(tc_memset, memset_test);

  // 6 - strcat
  TCase *tc_strcat;
  tc_strcat = tcase_create("strcat test");
  suite_add_tcase(s, tc_strcat);
  tcase_add_test(tc_strcat, strcat_test);

  // 7 - strncat
  TCase *tc_strncat;
  tc_strncat = tcase_create("strncat test");
  suite_add_tcase(s, tc_strncat);
  tcase_add_test(tc_strncat, strncat_test);

  // 8 - strchr
  TCase *tc_strchr;
  tc_strchr = tcase_create("strchr test");
  suite_add_tcase(s, tc_strchr);
  tcase_add_test(tc_strchr, strchr_test);

  // 9 - strrchr
  TCase *tc_strrchr;
  tc_strrchr = tcase_create("strrchr test");
  suite_add_tcase(s, tc_strrchr);
  tcase_add_test(tc_strrchr, strrchr_test);

  // 10 - strcmp
  TCase *tc_strcmp;
  tc_strcmp = tcase_create("strcmp test");
  suite_add_tcase(s, tc_strcmp);
  tcase_add_test(tc_strcmp, strcmp_test);

  // 11 - strncmp
  TCase *tc_strncmp;
  tc_strncmp = tcase_create("strncmp test");
  suite_add_tcase(s, tc_strncmp);
  tcase_add_test(tc_strncmp, strncmp_test);

  // 12 - strncpy
  TCase *tc_strncpy;
  tc_strncpy = tcase_create("strncpy test");
  suite_add_tcase(s, tc_strncpy);
  tcase_add_test(tc_strncpy, strncpy_test);

  // 13 - strcpy
  TCase *tc_strcpy;
  tc_strcpy = tcase_create("strcpy test");
  suite_add_tcase(s, tc_strcpy);
  tcase_add_test(tc_strcpy, strcpy_test);

  // 14 - strcspn LOOK INTO 18 TOO
  TCase *tc_strcspn;
  tc_strcspn = tcase_create("strcspn test");
  suite_add_tcase(s, tc_strcspn);
  tcase_add_test(tc_strcspn, strcspn_test);

  // // 15 - strerror
  // TCase *tc_strerror;
  // tc_strerror = tcase_create("strerror test");
  // suite_add_tcase(s, tc_strerror);
  // tcase_add_test(tc_strerror, strerror_test);

  // 16 - strlen
  TCase *tc_strlen;
  tc_strlen = tcase_create("strlen test");
  suite_add_tcase(s, tc_strlen);
  tcase_add_test(tc_strlen, strlen_test);

  // 17 - strpbrk
  TCase *tc_strpbrk;
  tc_strpbrk = tcase_create("strpbrk test");
  suite_add_tcase(s, tc_strpbrk);
  tcase_add_test(tc_strpbrk, strpbrk_test);

  // 18 - strspn LOOK INTO 14 TOO
  TCase *tc_strspn;
  tc_strspn = tcase_create("strspn test");
  suite_add_tcase(s, tc_strspn);
  tcase_add_test(tc_strspn, strspn_test);

  // runner
  srunner_run_all(runner, CK_VERBOSE);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}