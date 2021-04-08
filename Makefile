#
# UFRGS - Compiladores B - Jobe Diego Dylbas dos Santos- 2020/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa4: y.tab.c lex.yy.c semantic
	gcc -o etapa4 lex.yy.c semantic.o
	chmod +x etapa4
	./etapa4 source.txt eq1.txt
	./etapa4 eq1.txt eq2.txt
	diff eq1.txt eq2.txt

lex.yy.c: scanner.l
	lex scanner.l

y.tab.c: parser.y
	yacc parser.y -d

clean:
	rm -rf lex.yy.c etapa4 etapa4.tgz y.tab.c y.tab.h output.txt outputreal.txt semantic.o

test: y.tab.c lex.yy.c semantic
	gcc -o etapa4 lex.yy.c semantic.o
	chmod +x etapa4
	./etapa4 test.txt output.txt
	./etapa4 output.txt outputreal.txt

finalTest: y.tab.c lex.yy.c semantic
	gcc -o etapa4 lex.yy.c semantic.o
	chmod +x etapa4
	./etapa4 sample.txt output.txt
	./etapa4 output.txt outputreal.txt
	diff output.txt outputreal.txt


compress: clean
	tar cvzf etapa4.tgz hash.c hash.h main.c Makefile scanner.l parser.y ast.c ast.h semantic.c semantic.h

semantic: semantic.c
	gcc -c semantic.c