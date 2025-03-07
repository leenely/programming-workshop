#include "quadratic.h"
#include <math.h>

double get_accuracy(double value, int accuracy) {
  double pow_10 = pow(10, accuracy);
  return round(value * pow_10) / pow_10;
}

int calculate(double a, double b, double c, double roots[2], int accuracy) {

  if (accuracy == 0) {
    accuracy = 1E-7; // точность по умолчанию
  }

  if (a == 0) {
    return -1;
  }

  double discriminant = b * b - 4 * a * c;
  discriminant = get_accuracy(discriminant, 7);

  if (discriminant < 0) {
    return 0;
  } else if (discriminant == 0) {
    double x = -b / (2 * a);
    roots[0] = get_accuracy(x, accuracy);
    return 1;
  } else {
    double x1 = (-b - sqrt(discriminant)) / (2 * a);
    double x2 = (-b + sqrt(discriminant)) / (2 * a);
    if (fabs(x1) < 1E-10) {
      x1 = c / (a * x2);
    } else if (fabs(x2) < 1E-10) {
      x2 = c / (a * x1);
    }
    roots[0] = get_accuracy(x1, accuracy);
    roots[1] = get_accuracy(x2, accuracy);
    return 2;
  }
}
