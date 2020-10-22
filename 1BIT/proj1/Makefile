#Makefile
#Řešení IJC-DU1
#15.3.2020
#Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)

CC = gcc
CFLAGS = -g -O2 -std=c11 -lm -Wall -Wextra -pedantic
OBJECTS = primes primes-i steg-decode

.PHONY:all
all : $(OBJECTS)

primes: error.o bitset.h bitset.c erastothenes.c erastothenes.h primes.c
	$(CC) $(CFLAGS)  -o primes error.o  erastothenes.c erastothenes.h primes.c

primes-i: error.o bitset.h bitset.c erastothenes.c erastothenes.h primes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -o primes-i error.o erastothenes.c erastothenes.h bitset.c bitset.h primes.c

error.o: error.h error.c
	$(CC) $(CFLAGS) -c error.c

steg-decode: error.o bitset.h erastothenes.c erastothenes.h ppm.o steg-decode.c
	$(CC) $(CFLAGS) -o steg-decode error.o erastothenes.c erastothenes.h ppm.o steg-decode.c

ppm.o: bitset.h ppm.c ppm.h error.o
	$(CC) $(CFLAGS) -c ppm.c


.PHONY : run
run: primes primes-i
	ulimit -s 500000 && ./primes && ./primes-i

.PHONY : clean
clean:
	rm *.o && rm $(OBJECTS)
