# -- Утилиты

clear:
	rm -rf *.o *.a *_test integral quadratic list stack

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


# -- Сборка статических библиотек

arraylist.o: arraylist.c arraylist.h
	gcc -g -c arraylist.c -o arraylist.o -lm

arraylist.a: arraylist.o
	ar rc arraylist.a arraylist.o -lm

hashtable.o: hashtable.c hashtable.h
	gcc -g -c hashtable.c -o hashtable.o -lm

hashtable.a: hashtable.o
	ar rc hashtable.a hashtable.o -lm

linear_alloc.o: linear_alloc.c linear_alloc.h
	gcc -g -c linear_alloc.c -o linear_alloc.o -lm

linear_alloc.a: linear_alloc.o
	ar rc linear_alloc.a linear_alloc.o -lm

pool_alloc.o: pool_alloc.c pool_alloc.h
	gcc -g -c pool_alloc.c -o pool_alloc.o -lm

pool_alloc.a: pool_alloc.o
	ar rc pool_alloc.a pool_alloc.o -lm


# -- Сборка тестов

arraylist_test.o: tests/arraylist_test.c arraylist.h
	gcc -g -c tests/arraylist_test.c -o arraylist_test.o -lm

arraylist_test: arraylist_test.o arraylist.a linear_alloc.a
	gcc -g -o arraylist_test arraylist_test.o arraylist.a linear_alloc.a -lm

hashtable_test.o: tests/hashtable_test.c hashtable.h
	gcc -g -c tests/hashtable_test.c -o hashtable_test.o -lm

hashtable_test: hashtable_test.o hashtable.a pool_alloc.a
	gcc -g -o hashtable_test hashtable_test.o hashtable.a pool_alloc.a -lm

linear_alloc_test.o: tests/linear_alloc_test.c linear_alloc.h
	gcc -g -c tests/linear_alloc_test.c -o linear_alloc_test.o -lm

linear_alloc_test: linear_alloc_test.o linear_alloc.a
	gcc -g -static -o linear_alloc_test linear_alloc_test.o linear_alloc.a -lm

pool_alloc_test.o: tests/pool_alloc_test.c pool_alloc.h
	gcc -g -c tests/pool_alloc_test.c -o pool_alloc_test.o -lm

pool_alloc_test: pool_alloc_test.o pool_alloc.a
	gcc -g -static -o pool_alloc_test pool_alloc_test.o pool_alloc.a -lm

run_tests: arraylist_test hashtable_test linear_alloc_test pool_alloc_test
	./arraylist_test
	./hashtable_test
	./linear_alloc_test
	./pool_alloc_test


# -- Сборка бинарников без тестов

arraylist: arraylist.o arraylist.a
	gcc -g -static -o arraylist arraylist.o arraylist.a -lm
	./arraylist

hashtable: hashtable.o hashtable.a
	gcc -g -static -o hashtable hashtable.o hashtable.a -lm
	./hashtable

linear_alloc: linear_alloc.o linear_alloc.a
	gcc -g -static -o linear_alloc linear_alloc.o linear_alloc.a -lm
	./linear_alloc

pool_alloc: pool_alloc.o pool_alloc.a
	gcc -g -static -o pool_alloc pool_alloc.o pool_alloc.a -lm
	./pool_alloc
