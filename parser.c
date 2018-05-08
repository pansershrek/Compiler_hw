#include <stdio.h>
#include <math.h>
#include "parser.h"

char buf[1001];

int main(int argc, char *argv[]) {
    printf("Max length of input is 1000 symbols\n");
    while (fgets(buf, sizeof(buf), stdin)) {
        char *str = buf;
        double ans = parser_getExpr(&str);
        if (isnan(ans)) {
           printf("Bad expression\n");
        } else {
            printf("%.10g\n", ans);
        }
    }
    return 0;
}