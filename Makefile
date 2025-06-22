TEST_FILES := quadratic_test integral_test list_test stack_test arraylist_test hashtable_test linear_alloc_test pool_alloc_test cycled_links_test destructor_test garbage_collector_test

# -- Утилиты

clear:
	rm -rf *.o *.a *_test integral quadratic list stack

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

# -- Сборка 

quadratic.o: utils/quadratic.c utils/quadratic.h
	gcc -g -c utils/quadratic.c -o quadratic.o -lm

quadratic.a: quadratic.o
	ar rc quadratic.a quadratic.o -lm

integral.o: utils/integral.c utils/integral.h
	gcc -g -c utils/integral.c -o integral.o -lm

integral.a: integral.o
	ar rc integral.a integral.o -lm

list.o: data_structures/list.c data_structures/list.h
	gcc -g -c data_structures/list.c -o list.o

list.a: list.o
	ar rc list.a list.o

stack.o: data_structures/stack.c data_structures/stack.h
	gcc -g -c data_structures/stack.c -o stack.o

stack.a: stack.o
	ar rc stack.a stack.o

arraylist.o: data_structures/arraylist.c data_structures/arraylist.h
	gcc -g -c data_structures/arraylist.c -o arraylist.o -lm

arraylist.a: arraylist.o
	ar rc arraylist.a arraylist.o -lm

hashtable.o: data_structures/hashtable.c data_structures/hashtable.h
	gcc -g -c data_structures/hashtable.c -o hashtable.o -lm

hashtable.a: hashtable.o
	ar rc hashtable.a hashtable.o -lm

linear_alloc.o: memory/linear_alloc.c memory/linear_alloc.h
	gcc -g -c memory/linear_alloc.c -o linear_alloc.o -lm

linear_alloc.a: linear_alloc.o
	ar rc linear_alloc.a linear_alloc.o -lm

pool_alloc.o: memory/pool_alloc.c memory/pool_alloc.h
	gcc -g -c memory/pool_alloc.c -o pool_alloc.o -lm

pool_alloc.a: pool_alloc.o
	ar rc pool_alloc.a pool_alloc.o -lm

cycled_links.o: garbage_collection/cycled_links.c garbage_collection/cycled_links.h
	gcc -g -c garbage_collection/cycled_links.c -o cycled_links.o -lm

cycled_links.a: cycled_links.o
	ar rc cycled_links.a cycled_links.o -lm

destructor.o: garbage_collection/destructor.c garbage_collection/destructor.h
	gcc -g -c garbage_collection/destructor.c -o destructor.o -lm

destructor.a: destructor.o
	ar rc destructor.a destructor.o -lm

garbage_collector.o: garbage_collection/garbage_collector.c garbage_collection/garbage_collector.h
	gcc -g -c garbage_collection/garbage_collector.c -o garbage_collector.o -lm

garbage_collector.a: garbage_collector.o
	ar rc garbage_collector.a garbage_collector.o -lm

# -- Сборка тестов

quadratic_test.o: utils/tests/quadratic_test.c utils/quadratic.h
	gcc -g -c utils/tests/quadratic_test.c -o quadratic_test.o -lm

quadratic_test: quadratic_test.o quadratic.a
	gcc -g -static -o quadratic_test quadratic_test.o quadratic.a -lm

integral_test.o: utils/tests/integral_test.c utils/integral.h
	gcc -g -c utils/tests/integral_test.c -o integral_test.o -lm

integral_test: integral_test.o integral.a
	gcc -g -static -o integral_test integral_test.o integral.a -lm

list_test.o: data_structures/tests/list_test.c data_structures/list.h
	gcc -g -c data_structures/tests/list_test.c -o list_test.o

list_test: list_test.o list.a
	gcc -g -static -o list_test list_test.o list.a 

stack_test.o: data_structures/tests/stack_test.c data_structures/stack.h
	gcc -g -c data_structures/tests/stack_test.c -o stack_test.o

stack_test: stack_test.o stack.a
	gcc -g -static -o stack_test stack_test.o stack.a 

arraylist_test.o: data_structures/tests/arraylist_test.c data_structures/arraylist.h
	gcc -g -c data_structures/tests/arraylist_test.c -o arraylist_test.o -lm

arraylist_test: arraylist_test.o arraylist.a linear_alloc.a
	gcc -g -static -o arraylist_test arraylist_test.o arraylist.a linear_alloc.a -lm

hashtable_test.o: data_structures/tests/hashtable_test.c data_structures/hashtable.h
	gcc -g -c data_structures/tests/hashtable_test.c -o hashtable_test.o -lm

hashtable_test: hashtable_test.o hashtable.a pool_alloc.a
	gcc -g -static -o hashtable_test hashtable_test.o hashtable.a pool_alloc.a -lm

linear_alloc_test.o: memory/tests/linear_alloc_test.c memory/linear_alloc.h
	gcc -g -c memory/tests/linear_alloc_test.c -o linear_alloc_test.o -lm

linear_alloc_test: linear_alloc_test.o linear_alloc.a
	gcc -g -static -o linear_alloc_test linear_alloc_test.o linear_alloc.a -lm

pool_alloc_test.o: memory/tests/pool_alloc_test.c memory/pool_alloc.h
	gcc -g -c memory/tests/pool_alloc_test.c -o pool_alloc_test.o -lm

pool_alloc_test: pool_alloc_test.o pool_alloc.a
	gcc -g -static -o pool_alloc_test pool_alloc_test.o pool_alloc.a -lm

cycled_links_test.o: garbage_collection/tests/cycled_links_test.c garbage_collection/cycled_links.h
	gcc -g -c garbage_collection/tests/cycled_links_test.c -o cycled_links_test.o -lm

cycled_links_test: cycled_links_test.o cycled_links.a
	gcc -g -static -o cycled_links_test cycled_links_test.o cycled_links.a -lm

destructor_test.o: garbage_collection/tests/garbage_collector_test.c garbage_collection/garbage_collector.h
	gcc -g -c garbage_collection/tests/destructor_test.c -o destructor_test.o -lm

destructor_test: destructor_test.o garbage_collector.a pool_alloc.a
	gcc -g -static -o destructor_test destructor_test.o garbage_collector.a pool_alloc.a -lm

garbage_collector_test.o: garbage_collection/tests/garbage_collector_test.c garbage_collection/garbage_collector.h
	gcc -g -c garbage_collection/tests/garbage_collector_test.c -o garbage_collector_test.o -lm

garbage_collector_test: garbage_collector_test.o garbage_collector.a pool_alloc.a
	gcc -g -static -o garbage_collector_test garbage_collector_test.o garbage_collector.a pool_alloc.a -lm


run_tests: $(TEST_FILES)
	@for test in $(TEST_FILES); do \
		valgrind --leak-check=full --show-leak-kinds=all ./$$test; \
	done


# -- Сборка без тестов

integral: integral.o integral.a
	gcc -g -static -o integral integral.o integral.a -lm
	./integral

quadratic: quadratic.o quadratic.a
	gcc -g -static -o quadratic quadratic.o quadratic.a -lm
	./quadratic

list: list.o list.a
	gcc -g -static -o list list.o list.a
	./list

stack: stack.o stack.a
	gcc -g -static -o stack stack.o stack.a
	./stack

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

cycled_links: cycled_links.o cycled_links.a
	gcc -g -static -o cycled_links cycled_links.o cycled_links.a -lm
	./cycled_links

destructor: destructor.o destructor.a
	gcc -g -static -o destructor destructor.o destructor.a -lm
	./destructor

garbage_collector: garbage_collector.o garbage_collector.a
	gcc -g -static -o garbage_collector garbage_collector.o garbage_collector.a -lm
	./garbage_collector
