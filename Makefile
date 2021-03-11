#
# UFRGS - Compiladores B - Jobe Diego Dylbas dos Santos- 2020/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa2: y.tab.c lex.yy.c
	gcc -o etapa2 lex.yy.c

lex.yy.c: scanner.l
	lex scanner.l

y.tab.c: parser.y
	yacc parser.y -d

clean:
	rm -rf lex.yy.c etapa2 etapa2.tgz y.tab.c y.tab.h

test: y.tab.c lex.yy.c
	gcc -o etapa2 lex.yy.c
	chmod +x etapa2
	./etapa2 test.txt

finalTest: y.tab.c lex.yy.c
	gcc -o etapa2 lex.yy.c
	chmod +x etapa2
	./etapa2 sample.txt

compress: clean
	tar cvzf etapa2.tgz hash.c hash.h main.c Makefile scanner.l parser.y