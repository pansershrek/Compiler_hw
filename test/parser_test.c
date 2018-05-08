#include <stdio.h>
#include "../parser.h"

const int MAX_TEST = 10;
char *tests[] = {"8*8+8", "2+2*2", "100-100*3", "10+3*4", "(-5+10000)",
"100*3+1/2", "100+3.14", "6/2/3", "-(-(-123))", "(1-2)*((2*(1-3)))"};
double ans[] = {72, 6, -200, 22, 9995, 300.5, 103.14, 1, -123, 4};

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