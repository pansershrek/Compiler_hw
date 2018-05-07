#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void parser_notspace(char **rest) {
    while ((**rest != '\0') && (isspace(**rest))) {
        ++(*rest);
    }
}

int parser_isnum(char **rest) {
    parser_notspace(rest);
    return (**rest != '\0' ) && ((**rest >= '0') && (**rest <= '9'));
}
double parser_getExpr(char **rest);
double parser_getN(char **rest) {
    double ans = 0;
    parser_notspace(rest);
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

double parser_getTerm(char **rest) {
    parser_notspace(rest);
    if (parser_isnum(rest)) {
        return parser_getN(rest);
    } else if ((**rest != '\0') && (**rest == '-')) {
        (*rest)++;
        return -parser_getTerm(rest);
    } else if ((**rest != '\0') && (**rest == '(')) {
        (*rest)++;
        double mid = parser_getExpr(rest);
        if ((**rest == '\0') || (**rest != ')')) {
            return NAN;
        }
        (*rest)++;
        return mid;
    } else {
        return NAN;
    }
}

double parser_getProd(char **rest) {
    parser_notspace(rest);
    double lpart = parser_getTerm(rest);
    parser_notspace(rest);
    while ((**rest != '\0') && ((**rest == '*') || (**rest == '/'))) {
        char oper = (**rest);
        (*rest)++;
        parser_notspace(rest);
        double rpart = parser_getTerm(rest);
        parser_notspace(rest);
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

double parser_getExpr(char **rest) {
    parser_notspace(rest);
    double lpart = parser_getProd(rest);
    parser_notspace(rest);
    while ((**rest != '\0') && ((**rest == '+') || (**rest == '-'))) {
        char oper = (**rest);
        (*rest)++;
        parser_notspace(rest);
        double rpart = parser_getProd(rest);
        parser_notspace(rest);
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