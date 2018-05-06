#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

struct node {
    struct node *l, *r;
    union val {
        char oper;
        double ans;
    } val;
};
typedef struct node *tree;

tree make_new() {
    tree node_new = (tree) malloc(sizeof(struct node));
    node_new->l = node_new->r = NULL;
    return node_new;
}

int islist(tree t) {
    return !(t->l || t->r);
}

double get_ans(double l, double r, char oper) {
    switch(oper) {
        case('+'): return l + r;
        case('-'): return l - r;
        case('*'): return l * r;
        case('/'): return l / r;
        default: return NAN;
    }
}

void erase(tree t) {
    if (t->l) {
        erase(t->l);
    }
    if (t->r) {
        erase(t->r);
    }
    free(t);
}

void calculate(tree t) {
    if (t->l) {
        calculate(t->l);
    }
    if (t->r) {
        calculate(t->r);
    }
    if (islist(t->l) && islist(t->r)) {
        t->val.ans = get_ans(t->l->val.ans, t->r->val.ans, t->val.oper);
        erase(t->l);
        erase(t->r);
    }
}

void print_file(tree t, FILE *file) {
    if (t->l) {
        if (!islist(t->l)) {
            fprintf(file, "(");
        }
        print_file(t->l, file);
        if (!islist(t->l)) {
            fprintf(file, ")");
        }
    }
    if ((t->l) || (t->r)) {
        fprintf(file, "%c", t->val.oper);
    } else {
        fprintf(file, "%.10g", t->val.ans);
    }
    if (t->r) {
        if (!islist(t->r)) {
            fprintf(file, "(");
        }
        print_file(t->r, file);
        if (!islist(t->r)) {
            fprintf(file, ")");
        }
    }
}

void notspace(char **rest) {
    while ((**rest != '\0') && (isspace(**rest))) {
        ++(*rest);
    }
}

int isnum(char **rest) {
    notspace(rest);
    return (**rest != '\0' ) && ((**rest >= '0') && (**rest <= '9'));
}
int getExpr(char **rest, tree T);
int getN(char **rest, tree T) {
    double ans = 0;
    notspace(rest);
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
    T->val.ans = ans;
    return 0;
}

int getTerm(char **rest, tree T) {
    notspace(rest);
    if (isnum(rest)) {
        return getN(rest, T);
    } else if ((**rest != '\0') && (**rest == '-')) {
        (*rest)++;
        T->l = make_new();
        T->l->val.ans = -1;
        T->val.oper = '*';
        T->r = make_new();
        T = T->r;
        return getTerm(rest, T);
    } else if ((**rest != '\0') && (**rest == '(')) {
        (*rest)++;
        int f = getExpr(rest, T);
        if (f) {
            return f;
        }
        if ((**rest == '\0') || (**rest != ')')) {
            return 1;
        }
        (*rest)++;
        return 0;
    } else {
        return 1;
    }
}

int getProd(char **rest, tree T) {
    notspace(rest);
    T->l = make_new();
    int f = getTerm(rest, T->l);
    if (f) {
        return f;
    }
    notspace(rest);
    while ((**rest != '\0') && ((**rest == '*') || (**rest == '/'))) {
        char oper = (**rest);
        T->val.oper = oper;
        T->r = make_new();
        T = T->r;
        T->l = make_new();
        (*rest)++;
        notspace(rest);
        f = getTerm(rest, T->l);
        if (f) {
            return f;
        }
        notspace(rest);
    }
    return 0;
}

int getExpr(char **rest, tree T) {
    notspace(rest);
    T->l = make_new();
    int f = getProd(rest, T->l);
    if (f) {
        return f;
    }
    notspace(rest);
    while ((**rest != '\0') && ((**rest == '+') || (**rest == '-'))) {
        char oper = (**rest);
        T->val.oper = oper;
        T->r = make_new();
        T = T->r;
        T->l = make_new();
        (*rest)++;
        notspace(rest);
        f = getProd(rest, T->l);
        if (f) {
            return f;
        }
        notspace(rest);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        char *str = argv[1];
        tree T = make_new();
        int f = getExpr(&str, T);
        if (f) {
            printf("Bad expression\n");
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
        printf("2 arg\n");
        char *str = argv[1];
        tree T = make_new();
        int f = getExpr(&str, T);
        if (f) {
            printf("Bad expression\n");
            erase(T);
            return 0;
        }
        calculate(T);
        if (islist(T)) {
            if (T->val.ans == NAN) {
                printf("Bad expression\n");
            } else {
                printf("%.10g\n", T->val.ans);
            }
        } else {
            printf("Bad expression\n");
        }
        erase(T);
    } else {
        printf("Bad argv\n");
    }
    return 0;
}