#include "../quadratic.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int compare(double a, double b, double epsilon) {
  if (epsilon == 0) {
    epsilon = 1E-7;
  }
  return fabs(a - b) < epsilon;
}

void test1() {
  double roots[2];
  double a = 0;
  double b = 0;
  double c = -1;
  int roots_count = calculate(a, b, c, roots, 0);
  assert(roots_count == -1);
}

void test2() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1;
  int roots_count = calculate(a, b, c, roots, 0);
  assert(roots_count == 2);
  assert(compare(roots[0], -1, 0));
  assert(compare(roots[1], 1, 0));
}

void test3() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = 0;
  int roots_count = calculate(a, b, c, roots, 0);
  assert(roots_count == 1);
  assert(compare(roots[0], 0, 0));
}

void test4() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = 1;
  int roots_count = calculate(a, b, c, roots, 0);
  assert(roots_count == 0);
}

void test5() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1E-7;
  int roots_count = calculate(a, b, c, roots, 4);
  assert(roots_count == 2);
  assert(compare(roots[0], -3E-4, 1E-4));
  assert(compare(roots[1], 3E-4, 1E-4));
}

void test6() {
  double roots[2];
  double a = 1;
  double b = -1E+10;
  double c = -1;
  int roots_count = calculate(a, b, c, roots, 11);
  assert(roots_count == 2);
  assert(compare(roots[0], -1E-10, 1E-11));
  assert(compare(roots[1], 1E+10, 1E-11));
}

void test7() {
  double roots[2];
  double a = 1;
  double b = 0;
  double c = -1E-8;
  int roots_count = calculate(a, b, c, roots, 7);
  assert(roots_count == 1);
  assert(compare(roots[0], 0, 0));
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  return 1;
}