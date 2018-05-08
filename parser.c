#include <stdio.h>
#include <math.h>
#include "parser.h"

char buf[1002];
//buf[1001] contains '\0' for correct C string
//buf[1000] can contains '\n'

int main(int argc, char *argv[]) {
    printf("Max length of input is 1000 symbols\n");
    while (fgets(buf, sizeof(buf), stdin)) {
        char *str = buf;
        double ans = parser_getExpr(&str);
        if (isnan(ans)) {
           printf("Bad expression\n");
        } else {
            printf("Calculete %.10g\n", ans);
        }
        buf[1001] = '\0';
    }
    return 0;
}