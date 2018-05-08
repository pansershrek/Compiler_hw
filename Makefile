parser:
	gcc -o proj_parser -std=gnu11 parser.c parser_func.c
ast:
	gcc -o proj_ast -std=gnu11 ast.c ast_func.c
clean:
	rm proj_*