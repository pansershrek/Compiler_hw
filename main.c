#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void notspace(char **rest) {
    while ((**rest != '\0') && (isspace(**rest))) {
        ++(*rest);
    }
}

int isnum(char **rest) {
    notspace(rest);
    return (**rest != '\0' ) && ((**rest >= '0') && (**rest <= '9'));
}
double getExpr(char **rest);
double getN(char **rest) {
    double ans = 0;
    notspace(rest);
    //printf("In N %s\n", *rest);
    while ((**rest != '\0') && ((**rest >= '0') && (**rest <= '9'))) {
        ans = ans * 10 + (**rest - '0');
        (*rest)++;
    }
    if ((**rest != '\0') && (**rest == '.')) {
        double del = 10;
        while ((**rest != '\0') && ((**rest >= '0') && (**rest <= '9'))) {
            ans = ans + (**rest - '0') / del;
            del *= 10;
            (*rest)++;
        }
    }
    return ans;
}

double getTerm(char **rest) {
    notspace(rest);
    //printf("In term %s\n", *rest);
    if (isnum(rest)) {
        return getN(rest);
    } else if ((**rest != '\0') && (**rest == '-')) {
        (*rest)++;
        return -getTerm(rest);
    } else if ((**rest != '\0') && (**rest == '(')) {
        (*rest)++;
        double mid = getExpr(rest);
        if ((**rest == '\0') || (**rest != ')')) {
            return NAN;
        }
        (*rest)++;
        return mid;
    } else {
        return NAN;
    }
}

double getProd(char **rest) {
    notspace(rest);
    //printf("In prod %s\n", *rest);
    double lpart = getTerm(rest);
    notspace(rest);
    while ((**rest != '\0') && ((**rest == '*') || (**rest == '/'))) {
        char oper = (**rest);
        (*rest)++;
        notspace(rest);
        double rpart = getTerm(rest);
        notspace(rest);
        if (oper == '*') {
            lpart *= rpart;
        } else if (oper == '/') {
            if (rpart != 0) {
                lpart /= rpart;
            } else {
                return NAN;
            }
        } else {
            return NAN;
        }
    }
    return lpart;
}

double getExpr(char **rest) {
    notspace(rest);
    //printf("In expr %s\n", *rest);
    double lpart = getProd(rest);
    notspace(rest);
    while ((**rest != '\0') && ((**rest == '+') || (**rest == '-'))) {
        char oper = (**rest);
        (*rest)++;
        notspace(rest);
        double rpart = getProd(rest);
        notspace(rest);
        if (oper == '+') {
            lpart += rpart;
        } else if (oper == '-') {
            lpart -= rpart;
        } else {
            return NAN;
        }
    }
    return lpart;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *str = argv[1];
    double ans = getExpr(&str);
    if (ans != NAN) {
        printf("%.10g\n", ans);
    } else {
        printf("Bad expression\n");
    }
    return 0;
}