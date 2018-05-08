#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>

struct node {
    struct node *l, *r;
    union val {
        char oper;
        double ans;
    } val;
};
typedef struct node *tree;

tree make_new();
tree join(tree l, tree r, char oper);
int islist(tree t);
int fullnode(tree t);
double get_ans(double l, double r, char oper);
void erase(tree t);
void calculate(tree *t);
void print_debug(tree t);
void print_file(tree t, FILE *file);

void ast_notspace(char **rest);
int ast_isnum(char **rest);
int ast_getN(char **rest, tree *T); // Return 1 if this expression is incorrect else return 0
int ast_getTerm(char **rest, tree *T); // Return 1 if this expression is incorrect else return 0
int ast_getProd(char **rest, tree *T); // Return 1 if this expression is incorrect else return 0
int ast_getExpr(char **rest, tree *T); // Return 1 if this expression is incorrect else return 0