CFLAGS= -std=c99 -Wall -Wextra -pedantic
.PHONY: run purge clear
all: main modulA modulB modulC modulD

main: main.c
	gcc $(CFLAGS) main.c -o main
modulA: modulA*.c
	gcc $(CFLAGS) modulA1.c modulA2.c -o modulA
modulB: modulB*.c
	#gcc $(CFLAGS) modulB1.c modulB2.c -o modulB
modulC: modulC*.c
	gcc $(CFLAGS) modulC1.c modulC2.c -o modulC	
modulD: modulD*.c
	#gcc $(CFLAGS) modulD1.c modulD2.c -o modulD

clear: 
	rm -f *.o
purge: 
	rm -f *.o main modulA modulB modulC modulD
