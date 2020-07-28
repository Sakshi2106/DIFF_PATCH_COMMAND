#diff
all : diff patch
make diff: main.o readline.o output1.o lcs.o lcslinefil2.o 
	cc main.o readline.o output1.o lcs.o lcslinefil2.o -o diff	
main: main.c main.h
	cc -c main.c
readline : readline.c main.h
	cc -c readline.c
output1: output1.c main.h
	cc -c output1.c
lcs : lcs.c main.h
	cc -c lcs.c
lcslinefil2: lcslinefil2.c main.h
	cc -c lcslinefil2.c

#patch
make patch:readline.o patch1.o
	cc readline.o patch1.o -o patch
readline.o: readline.c main.h
	cc -c readline.c
patch1.o: patch1.c
	cc -c patch1.c
clean: 
	rm *.o
