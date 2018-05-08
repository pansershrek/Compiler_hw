#include <stdio.h>
#include <math.h>
#include "ast.h"

char buf[1001];
int main(int argc, char *argv[]) {
    printf("Max length of input is 1000 symbols\n");
    if (argc == 2) {
        FILE *file = fopen(argv[1], "w");
        if (!file) {
            printf("Cant open file\n");
            return 0;
        }
        while (fgets(buf, sizeof(buf), stdin)) {
            char *str = buf;
            tree T = NULL;
            int f = ast_getExpr(&str, &T);
            if (f) {
                fprintf(file, "Bad gen tree\n");
            } else {
                print_file(T, file);
                fprintf(file, "\n");
            }
            erase(T);
        }
        fclose(file);
    } else if (argc == 1) {
        while (fgets(buf, sizeof(buf), stdin)) {
            char *str = buf;
            tree T = NULL;
            int f = ast_getExpr(&str, &T);
            if (f) {
                printf("Bad gen tree\n");
            } else {
                calculate(&T);
                if (islist(T)) {
                    if (isnan(T->val.ans)) {
                        printf("Bad operators\n");
                    } else {
                        printf("calculete %.10g\n", T->val.ans);
                    }
                } else {
                    printf("Bad calculate expr\n");
                }
            }
            erase(T);
        }
    } else {
        printf("Bad argv\n");
    }
    return 0;
}