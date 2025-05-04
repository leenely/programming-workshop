#include "quadratic.h"
#include <math.h>

int compare(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}

int sign(double value) {
  if (value >= 0)
    return 1;
  else
    return -1;
}

int calculate(double a, double b, double c, double *roots, double accuracy) {
  if (compare(a, 0, accuracy)) {
    return NOT_A_QUADRATIC;
  }
  double discriminant = b * b - 4 * a * c;

  if (compare(discriminant, 0, accuracy)) {
    double x = -b / (2 * a);
    roots[0] = x;
    return ONE_ROOT;
  } else if (discriminant > accuracy) {
    double x1;
    double x2;
    x2 = -(b + sign(b) * sqrt(discriminant)) / (2 * a);
    x1 = c / (a * x2);
    if (x1 < x2) {
      roots[0] = x1;
      roots[1] = x2;
    } else {
      roots[0] = x2;
      roots[1] = x1;
    }
    return TWO_ROOTS;
  } else {
    return ZERO_ROOTS;
  }
}
