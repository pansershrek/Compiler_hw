#include <stdio.h>
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *str = argv[1];
    double ans = parser_getExpr(&str);
    if (ans != NAN) {
        printf("%.10g\n", ans);
    } else {
        printf("Bad expression\n");
    }
    return 0;
}