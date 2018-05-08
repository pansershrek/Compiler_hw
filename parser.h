#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void parser_notspace(char **rest);
int parser_isnum(char **rest);
double parser_getN(char **rest); // Return NAN if this expression is incorrect
double parser_getTerm(char **rest); // Return NAN if this expression is incorrect
double parser_getProd(char **rest); // Return NAN if this expression is incorrect
double parser_getExpr(char **rest); // Return NAN if this expression is incorrect