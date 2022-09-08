# file name: makefile
# last name: Kravitz
# first name: Steven
# LU email: swk324@lehigh.edu

CFLAGS = -Wall -Wextra -g -Wwrite-strings -Wno-discarded-qualifiers

default: fns

fns.o: fns.c
	gcc ${CFLAGS} fns.c -c -o fns.o

fnslib.o: fns.c
	gcc ${CFLAGS} -fPIC -c fnslib.c -o fnslib.o

libfns.so: fns.o
	gcc -shared -o libfnslib.so fnslib.o

fns: fns.o fnslib.o libfns.so
	gcc fns.o -Wl,-rpath=/home/swk324/cse202/prog3-fns-SWK324 -L. -lfnslib -o fns

clean:
	rm -f *.o
	rm -f *.so
	rm -f fns

