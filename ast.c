#include <stdio.h>
#include "ast.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        char *str = argv[1];
        tree T = NULL;
        int f = ast_getExpr(&str, &T);
        if (f) {
            printf("Bad gen tree\n");
            erase(T);
            return 0;
        }
        FILE *file = fopen(argv[2], "w");
        if (!file) {
            printf("Cant open file\n");
            fclose(file);
            erase(T);
            return 0;
        }
        print_file(T, file);
        erase(T);
        fclose(file);
    } else if (argc == 2) {
        char *str = argv[1];
        tree T = NULL;
        int f = ast_getExpr(&str, &T);
        if (f) {
            printf("Bad gen tree\n");
            erase(T);
            return 0;
        }
        calculate(&T);
        if (islist(T)) {
            if (T->val.ans == NAN) {
                printf("Bad operators\n");
            } else {
                printf("%.10g\n", T->val.ans);
            }
        } else {
            printf("Bad calculate expr\n");
        }
        erase(T);
    } else {
        printf("Bad argv\n");
    }
    return 0;
}