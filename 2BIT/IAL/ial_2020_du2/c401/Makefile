
PRJ=c401
#
PROGS=$(PRJ)-test $(PRJ)-test-advanced
CC=gcc
CFLAGS=-Wall -std=c99 -g -pedantic -lm

all: $(PROGS)

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c

$(PRJ)-test-advanced: $(PRJ).c $(PRJ)-test-advanced.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test-advanced.c


clean:
	rm -f *.o  $(PROGS)
#
