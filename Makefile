parser:
	gcc -o proj_parser -std=gnu11 parser.c
ast:
	gcc -o proj_ast -std=gnu11 ast.c
parser_test:
	gcc -o parser_test -std=gnu11 parser_test.c
ast_test:
	gcc -o ast_test -std=gnu11 ast_test.c