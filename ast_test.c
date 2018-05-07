#include <stdio.h>
#include "ast.h"

const int MAX_TEST = 5;
char *tests[] = {"10+3*4", "-5+10000", "100*3+1/2", "100++1++2++3.14", "6/2/3"};
double ans[] = {22, 9995, 300.5, 106.14, 1};

int main(int argc, char *argv[]) {
    printf("Begin ast tests\n");
    for (int i = 0; i < MAX_TEST; ++i) {
        printf("%d Test: ", i + 1 );
        tree T = NULL;
        ast_getExpr(&tests[i], &T);
        calculate(&T);
        double ast_ans = T->val.ans;
        if (ast_ans != ans[i]) {
            printf("expected %.10g, get %.10g\n", ans[i], ast_ans);
        } else {
            printf("OK\n");
        }
    }
    printf("End ast tests\n");
    return 0;
}