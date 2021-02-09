#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa1: lex.yy.c
	gcc -o etapa1 lex.yy.c
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm -rf lex.yy.c etapa1 etapa1.tgz

test: lex.yy.c
	gcc -o etapa1 lex.yy.c
	chmod +x etapa1
	./etapa1 test.txt

compress: clean
	mkdir etapa1
	cp hash.c hash.h main.c Makefile scanner.l test.txt tokens.h ./etapa1
	tar czf etapa1.tgz ./etapa1 
	rm -r etapa1