#include "../quadratic.h"
#include <assert.h>
#include <math.h>

void test1() {
  double roots[2];
  double a = 0;
  double b = 0;
  double c = -1;
  int roots_count = calculate(a, b, c, roots);
  assert(roots_count == NOT_A_QUADRATIC);
}

void test2() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1;
  int roots_count = calculate(a, b, c, roots);
  assert(roots_count == TWO_ROOTS);
  assert(compare(roots[0], -1, default_accuracy));
  assert(compare(roots[1], 1, default_accuracy));
}

void test3() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = 0;
  int roots_count = calculate(a, b, c, roots);
  assert(roots_count == ONE_ROOT);
  assert(compare(roots[0], 0, default_accuracy));
}

void test4() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = 1;
  int roots_count = calculate(a, b, c, roots);
  assert(roots_count == ZERO_ROOTS);
}

void test5() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1E-7;
  int roots_count = calculate(a, b, c, roots);
  assert(roots_count == TWO_ROOTS);
  assert(compare(roots[0], -3E-4, 1E-4));
  assert(compare(roots[1], 3E-4, 1E-4));
}

void test6() {
  double roots[2];
  double a = 1;
  double b = -1E+10;
  double c = -1;
  int roots_count = calculate(a, b, c, roots);
  assert(roots_count == TWO_ROOTS);
  assert(compare(roots[0], -1E-10, 1E-11));
  assert(compare(roots[1], 1E+10, 1E-11));
}

void test7() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1E-8;
  int roots_count = calculate(a, b, c, roots);
  assert(roots_count == ONE_ROOT);
  assert(compare(roots[0], 0, 1E-7));
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
