#include <stdio.h>
#include <math.h>
#include <assert.h>

double Integral(double (*function)(double), int a, int b, int num_of_parts) {
  double part = (b - a) / (double)num_of_parts;
  double res = 0;
  
  for (int i = 0; i < num_of_parts; i++) {
    double x1 = a + i * part;
    double x2 = a + (i + 1) * part;
    double s = 0.5 * (function(x1) + function(x2)) * part;
    res += s;
  }
  
  return res;
}

