CC=gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra -fPIC

HTAB_OBJS = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o

all: tail wordcount wordcount-dynamic

libhtab.a: $(HTAB_OBJS)
	ar rcs $@ $^

libhtab.so: $(HTAB_OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@

htab_bucket_count.o: htab_bucket_count.c htab.h htab_private.h
htab_clear.o: htab_clear.c htab.h htab_private.h
htab_erase.o: htab_erase.c htab.h htab_private.h
htab_find.o: htab_find.c htab.h htab_private.h
htab_for_each.o: htab_for_each.c htab.h htab_private.h
htab_free.o: htab_free.c htab.h htab_private.h
htab_hash_function.o: htab_hash_function.c
htab_init.o: htab_init.c htab.h htab_private.h
htab_lookup_add.o: htab_lookup_add.c htab.h htab_private.h
htab_size.o: htab_size.c htab.h htab_private.h
htab_statistics.o: htab_statistics.c htab.h htab_private.h

tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

wordcount-cc: wordcount-.cc io.o
	$(CXX) $(CXXFLAGS) $^ -o $@

wordcount: wordcount.o libhtab.a io.o
	$(CC) $(CFLAGS_N) -static $^ -o $@

wordcount-dynamic: wordcount.o libhtab.so io.o
	$(CC) $(CFLAGS_N) $^ -o $@

test: test.c all wordcount-cc
	$(CC) $(CFLAGS_N) -o $@ $< libhtab.a
	bash test.sh

clean:
	rm -f *.o *.out *.zip tail libhtab.a libhtab.so