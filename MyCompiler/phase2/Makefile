all:
	bison --yacc --defines --output=alpha2.c alpha.y
	flex --outfile=alpha1.c alpha.l
	gcc -g alpha2.c alpha1.c

run: all
	./a.out

clean:
	rm -f a.exe alpha1.c alpha1.c alpha1.h alpha2.c alpha2.h
