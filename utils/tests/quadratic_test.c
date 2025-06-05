#include "../quadratic.h"
#include <assert.h>

void test1() {
  double roots[2];
  double a = 0;
  double b = 0;
  double c = -1;
  double accuracy = default_accuracy;
  int roots_count = calculate(a, b, c, roots, accuracy);
  assert(roots_count == NOT_A_QUADRATIC);
}

void test2() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1;
  double accuracy = default_accuracy;
  int roots_count = calculate(a, b, c, roots, accuracy);
  assert(roots_count == TWO_ROOTS);
  assert(compare(roots[0], -1, accuracy));
  assert(compare(roots[1], 1, accuracy));
}

void test3() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = 0;
  double accuracy = default_accuracy;
  int roots_count = calculate(a, b, c, roots, accuracy);
  assert(roots_count == ONE_ROOT);
  assert(compare(roots[0], 0, accuracy));
}

void test4() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = 1;
  double accuracy = default_accuracy;
  int roots_count = calculate(a, b, c, roots, accuracy);
  assert(roots_count == ZERO_ROOTS);
}

void test5() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1E-7;
  double accuracy = default_accuracy;
  int roots_count = calculate(a, b, c, roots, accuracy);
  assert(roots_count == TWO_ROOTS);
  assert(compare(roots[0], -3E-4, 1E-4));
  assert(compare(roots[1], 3E-4, 1E-4));
}

void test6() {
  double roots[2];
  double a = 1;
  double b = -1E+10;
  double c = -1;
  double accuracy = 1E-11;
  int roots_count = calculate(a, b, c, roots, accuracy);
  assert(roots_count == TWO_ROOTS);
  assert(compare(roots[0], -1E-10, accuracy));
  assert(compare(roots[1], 1E+10, accuracy));
}

void test7() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1E-8;
  double accuracy = 1E-7;
  int roots_count = calculate(a, b, c, roots, accuracy);
  assert(roots_count == ONE_ROOT);
  assert(compare(roots[0], 0, accuracy));
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  return 0;
}
