CC = gcc
CFLAGS = -g -O2 -std=c11 -lm -Wall -Wextra -pedantic 

.PHONY:all
all : primes 


primes: error.o erastothenes.o  primes.o 
	$(CC) $(CFLAGS)  -o primes  error.o erastothenes.o primes.o

primes.o: primes.c bitset.h 
	$(CC) $(CFLAGS) -c primes.c

erastothenes.o: erastothenes.c erastothenes.h bitset.h
	$(CC) $(CFLAGS) -c erastothenes.c  

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

steg: error.o erastothenes.o ppm.o steg-decode.o
	$(CC) $(CFLAGS) -o steg error.o erastothenes.o ppm.o steg-decode.o

steg-decode.o: steg-decode.c bitset.h
	$(CC) $(CFLAGS) -c steg-decode.c

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c


.PHONY : run
run: primes.o erastothenes.h erastothenes.o bitset.h primes-i.o
	./primes; ./primes-i;
