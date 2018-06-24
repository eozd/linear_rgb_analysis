#include "utils.h"

double mse(int num_values, const int* y_true, const double* y_pred) {
    double result = 0;
    double diff;
    int i;
    for (i = 0; i < num_values; ++i) {
        diff = y_true[i] - y_pred[i];
        result += diff * diff;
    }
    result /= num_values;
    return result;
}
