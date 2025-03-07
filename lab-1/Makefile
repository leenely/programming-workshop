# -- Утилиты

clear:
	rm -rf *.o *.a *_test integral quadratic list stack

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


# -- Сборка статических библиотек

quadratic.o: quadratic.c quadratic.h
	gcc -g -c quadratic.c -o quadratic.o -lm

quadratic.a: quadratic.o
	ar rc quadratic.a quadratic.o -lm


integral.o: integral.c integral.h
	gcc -g -c integral.c -o integral.o -lm

integral.a: integral.o
	ar rc integral.a integral.o -lm


list.o: list.c list.h
	gcc -g -c list.c -o list.o

list.a: list.o
	ar rc list.a list.o


stack.o: stack.c stack.h
	gcc -g -c stack.c -o stack.o

stack.a: stack.o
	ar rc stack.a stack.o


# -- Сборка тестов

quadratic_test.o: tests/quadratic_test.c quadratic.h
	gcc -g -c tests/quadratic_test.c -o quadratic_test.o -lm

quadratic_test: quadratic_test.o quadratic.a
	gcc -g -static -o quadratic_test quadratic_test.o quadratic.a -lm


integral_test.o: tests/integral_test.c integral.h
	gcc -g -c tests/integral_test.c -o integral_test.o -lm

integral_test: integral_test.o integral.a
	gcc -g -static -o integral_test integral_test.o integral.a -lm


list_test.o: tests/list_test.c list.h
	gcc -g -c tests/list_test.c -o list_test.o

list_test: list_test.o list.a
	gcc -g -static -o list_test list_test.o list.a 


stack_test.o: tests/stack_test.c stack.h
	gcc -g -c tests/stack_test.c -o stack_test.o

stack_test: stack_test.o stack.a
	gcc -g -static -o stack_test stack_test.o stack.a 


run_tests: quadratic_test integral_test list_test stack_test
	./quadratic_test
	./integral_test
	./list_test
	./stack_test


# -- Сборка бинарников без тестов

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