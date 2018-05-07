#include <stdio.h>
#include "parser.h"

const int MAX_TEST = 5;
char *tests[] = {"10+3*4", "-5+10000", "100*3+1/2", "100++1++2++3.14", "6/2/3"};
double ans[] = {22, 9995, 300.5, 106.14, 1};

int main(int argc, char *argv[]) {
    printf("Begin pasrser tests\n");
    for (int i = 0; i < MAX_TEST; ++i) {
        printf("%d Test: ", i + 1 );
        double parser_ans = parser_getExpr(&tests[i]);
        if (parser_ans != ans[i]) {
            printf("expected %.10g, get %.10g\n", ans[i], parser_ans);
        } else {
            printf("OK\n");
        }
    }
    printf("End pasrser tests\n");
    return 0;
}