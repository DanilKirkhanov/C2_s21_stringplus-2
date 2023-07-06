#include "s21_string.h"
#include <stdio.h>

int main () {
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, res1 = 0, res2 = 0;
    //  test %d
    res1 = s21_sscanf("0123 456 789", "%d %*d %002d", &d1, &d2);
    res2 = sscanf("0123 456 789", "%d %*d %002d", &d3, &d4);
    printf("S21:%d : %d\n", d1, d2);
    printf("STR:%d : %d\n", d3, d4);
    printf("%d\n%d\n", res1, res2);

}
