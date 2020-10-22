#########################################
#Makefile				#
#Filip Januška FIT VUTBR		#
#Řešení IJC-DU2			#
#9.4.2020				#
#Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1) #
#########################################
CC = gcc
CFLAGS = -g -O2 -std=c99 -pedantic -Wall -Wextra
OBJECTS = tail wordcount wordcount-dynamic
MODULES = htab_init.o htab_size.o htab_bucket_count.o htab_hash_fun.o htab_end.o htab_find.o htab_lookup_add.o htab_begin.o \
	  htab_iterator_next.o htab_erase.o htab_clear.o htab_free.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_set_value.o
.PHONY:all
all: $(OBJECTS)

# ########### #
# executables #
# ########### #

tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o wordcount wordcount.o libhtab.a io.o

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.o libhtab.so io.o

# ######### #
# libraries #
# ######### #

libhtab.a: table_struct.h htab.h $(MODULES)
	ar rcs libhtab.a $(MODULES)

libhtab.so: table_struct.h htab.h $(MODULES)
	$(CC) $(CFLAGS) -shared -fPIC $(MODULES) -o libhtab.so

# ############ #
# object files #
# ############ #

wordcount.o: wordcount.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c wordcount.c

tail.o: tail.c
	$(CC) $(CFLAGS) -fPIC -c tail.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

# ############### #
# library modules #
# ############### #


htab_init.o: htab_init.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_init.c

htab_size.o: htab_size.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_size.c

htab_bucket_count.o: htab_bucket_count.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c

htab_hash_fun.o: htab_hash_fun.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_hash_fun.c

htab_end.o: htab_end.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_end.c

htab_find.o: htab_find.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_find.c

htab_lookup_add.o: htab_lookup_add.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c

htab_begin.o: htab_begin.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_begin.c

htab_iterator_next.o: htab_iterator_next.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_next.c

htab_erase.o: htab_erase.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_erase.c

htab_clear.o: htab_clear.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c

htab_free.o: htab_free.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_free.c

htab_iterator_get_key.o: htab_iterator_get_key.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_get_key.c
 
htab_iterator_get_value.o: htab_iterator_get_value.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_get_value.c

htab_iterator_set_value.o: htab_iterator_set_value.c htab.h table_struct.h
	$(CC) $(CFLAGS) -fPIC -c htab_iterator_set_value.c 

.PHONY:clean
clean:
	rm *.o && rm *.a && rm $(OBJECTS) && rm *.so
