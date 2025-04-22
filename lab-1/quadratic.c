#include "quadratic.h"
#include <math.h>

int compare(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}

int sign(double value) {
  if (value > 0)
    return 1;
  else if (value < 0)
    return -1;
  else
    return 0;
}

int calculate(double a, double b, double c, double *roots) {
  if (compare(a, 0, default_accuracy)) {
    return NOT_A_QUADRATIC;
  }
  double discriminant = b * b - 4 * a * c;

  if (discriminant < -default_accuracy) {
    return ZERO_ROOTS;
  } else if (compare(discriminant, 0, default_accuracy)) {
    double x = -b / (2 * a);
    roots[0] = x;
    return ONE_ROOT;
  } else {
    double x1;
    double x2;
    if (b * b / fabs(4 * a * c) <= 10) {
      x1 = (-b - sqrt(discriminant)) / (2 * a);
      x2 = (-b + sqrt(discriminant)) / (2 * a);
    } else {
      x2 = -(b + sign(b) * sqrt(discriminant)) / (2 * a);
      x1 = c / (a * x2);
    }
    roots[0] = x1;
    roots[1] = x2;
    return TWO_ROOTS;
  }
}
