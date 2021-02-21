
PRJ=c402
#
PROGS=$(PRJ)-test-advanced $(PRJ)-test
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -lm

all: $(PROGS)

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c


$(PRJ)-test-advanced: $(PRJ).c $(PRJ)-test-advanced.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test-advanced.c

clean:
	rm -f *.o *.out $(PROGS)
#
