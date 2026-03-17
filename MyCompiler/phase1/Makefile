all:
	flex alpha.l
	gcc lex.yy.c -o a.out

run: all
	./a.out

clean:
	rm -f lex.yy.c a.out
