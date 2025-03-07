#include "../integral.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

double square_function(double x) {
  return x * x;
}
  
double cos_function(double x) {
  return cos(x);
}
  
void test_integral_1() {
  int a = -10;
  int b = -2;
  int num_of_parts = 300000;
  double result = Integral(square_function, a, b, num_of_parts);
 
  assert(fabs(result - 330.6666666676213) < 1E-14);
}

void test_integral_2() {
  int a = -1;
  int b = 5;
  int num_of_parts = 300000;
  double result = Integral(square_function, a, b, num_of_parts);
 
  assert(fabs(result - 42.00000000039978) < 1E-14);
}

void test_integral_3() {
  int a = 15;
  int b = 200;
  int num_of_parts = 300000;
  double result = Integral(square_function, a, b, num_of_parts);
 
  assert(fabs(result - 2665541.666678384) < 1E-14);
}

void test_integral_4() {
  int a = -1;
  int b = 10;
  int num_of_parts = 400000;
  double result = Integral(cos_function, a, b, num_of_parts);
  
  assert(fabs(result - 0.2974498738998142) < 1E-14);
}

void test_integral_5() {
  int a = 15;
  int b = 20;
  int num_of_parts = 400000;
  double result = Integral(cos_function, a, b, num_of_parts);
  
  assert(fabs(result - 0.26265741056707675) < 1E-14);
}

void test_integral_6() {
  int a = -9;
  int b = -7;
  int num_of_parts = 400000;
  double result = fabs(Integral(cos_function, a, b, num_of_parts));
  
  assert(fabs(result - 0.24486811347653092) < 1E-14);
}

int main() { 
  test_integral_1();
  test_integral_2();
  test_integral_3();
  test_integral_4();
  test_integral_5();
  test_integral_6();
  
  return 0; 
}

