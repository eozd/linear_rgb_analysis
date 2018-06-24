#ifndef UTILS_H_
#define UTILS_H_

#define PI 3.1415926535897

double mse(int num_values, const int* y_true, const double* y_pred);
double r_squared(int num_values, const int* y_true, const double* y_pred);

#endif
