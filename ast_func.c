#include "ast.h"

tree make_new() {
    tree node_new = (tree) malloc(sizeof(struct node));
    node_new->l = node_new->r = NULL;
    node_new->val.oper = '#';
    return node_new;
}

tree join(tree l, tree r, char oper) {
    tree node_new = (tree) malloc(sizeof(struct node));
    node_new->l = l;
    node_new->r = r;
    node_new->val.oper = oper;
    return node_new;
}

int islist(tree t) {
    return !(t->l || t->r);
}

int fullnode(tree t) {
    return (t->l && t->r);
}

double get_ans(double l, double r, char oper) {
    switch(oper) {
        case('+'): return l + r;
        case('-'): return l - r;
        case('*'): return l * r;
        case('/'): if (r != 0) {
            return l / r;
        } else {
            return NAN;
        }
        default: return NAN;
    }
}

void erase(tree t) {
    if (!t) {
        return;
    }
    if (t->l) {
        erase(t->l);
    }
    if (t->r) {
        erase(t->r);
    }
    free(t);
}

void calculate(tree *t) {
    if ((*t)->l) {
        calculate(&(*t)->l);
    }
    if ((*t)->r) {
        calculate(&(*t)->r);
    }
    if (((*t)->l) && ((*t)->r) && islist((*t)->l) && islist((*t)->r)) {
        (*t)->val.ans = get_ans((*t)->l->val.ans, (*t)->r->val.ans, (*t)->val.oper);
        free((*t)->l);
        free((*t)->r);
        (*t)->l = (*t)->r = NULL;
    }
}

void print_debug(tree t) {
    if (t->l) {
        if (!islist(t->l)) {
            printf("(");
        }
        print_debug(t->l);
        if (!islist(t->l)) {
            printf(")");
        }
    }
    if ((t->l) || (t->r)) {
        printf("%c", t->val.oper);
    } else {
        printf("%.10g", t->val.ans);
    }
    if (t->r) {
        if (!islist(t->r)) {
            printf("(");
        }
        print_debug(t->r);
        if (!islist(t->r)) {
            printf(")");
        }
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

void ast_notspace(char **rest) {
    while ((**rest != '\0') && (isspace(**rest))) {
        ++(*rest);
    }
}

int ast_isnum(char **rest) {
    ast_notspace(rest);
    return (**rest != '\0' ) && ((**rest >= '0') && (**rest <= '9'));
}

int ast_getN(char **rest, tree *T) {
    double ans = 0;
    ast_notspace(rest);
    while ((**rest != '\0') && ((**rest >= '0') && (**rest <= '9'))) {
        ans = ans * 10 + (**rest - '0');
        (*rest)++;
    }
    if ((**rest != '\0') && (**rest == '.')) {
        (*rest)++;
        double del = 10;
        while ((**rest != '\0') && ((**rest >= '0') && (**rest <= '9'))) {
            ans = ans + (**rest - '0') / del;
            del *= 10;
            (*rest)++;
        }
    }
    (*T) = make_new();
    (*T)->val.ans = ans;
    return 0;
}

int ast_getTerm(char **rest, tree *T) {
    ast_notspace(rest);
    if (ast_isnum(rest)) {
        return ast_getN(rest, T);
    } else if ((**rest != '\0') && (**rest == '-')) {
        (*rest)++;
        (*T) = make_new();
        (*T)->l = make_new();
        (*T)->l->val.ans = -1;
        (*T)->val.oper = '*';
        return ast_getTerm(rest, &(*T)->r);
    } else if ((**rest != '\0') && (**rest == '(')) {
        (*rest)++;
        int f = ast_getExpr(rest, T);
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

int ast_getProd(char **rest, tree *T) {
    ast_notspace(rest);
    tree tl = NULL;
    int f = ast_getTerm(rest, &tl);
    if (f) {
        return f;
    }
    ast_notspace(rest);
    while ((**rest != '\0') && ((**rest == '*') || (**rest == '/'))) {
        char oper = (**rest);
        (*rest)++;
        ast_notspace(rest);
        tree tr = NULL;
        f = ast_getTerm(rest, &tr);
        tl = join(tl, tr, oper);
        if (f) {
            return f;
        }
        ast_notspace(rest);
    }
    (*T) = tl;
    return 0;
}

int ast_getExpr(char **rest, tree *T) {
    ast_notspace(rest);
    tree tl = NULL;
    int f = ast_getProd(rest, &tl);
    if (f) {
        return f;
    }
    ast_notspace(rest);
    while ((**rest != '\0') && ((**rest == '+') || (**rest == '-'))) {
        char oper = (**rest);
        (*rest)++;
        ast_notspace(rest);
        tree tr = NULL;
        f = ast_getProd(rest, &tr);
        tl = join(tl, tr, oper);
        if (f) {
            return f;
        }
        ast_notspace(rest);
    }
    (*T) = tl;
    return 0;
}