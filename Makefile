#
# UFRGS - Compiladores B - Jobe Diego Dylbas dos Santos- 2020/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa1: y.tab.c lex.yy.c
	gcc -o etapa1 lex.yy.c
lex.yy.c: scanner.l
	lex scanner.l
y.tab.c: parser.y
	yacc parser.y -d
clean:
	rm -rf lex.yy.c etapa1 etapa1.tgz

test: lex.yy.c
	gcc -o etapa1 lex.yy.c
	chmod +x etapa1
	./etapa1 test.txt
	
compress: clean
	tar cvzf etapa1.tgz hash.c hash.h main.c Makefile scanner.l test.txt tokens.h