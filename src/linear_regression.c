#include "linear_regression.h"
#include "line_params_2D.h"
#include <stdio.h>
#include <stdlib.h>

struct LineParams2D linear_regression(int num_values, const int* x_arr,
                                      const int* y_arr) {
    double sumx = 0.0;
    double sumx2 = 0.0;
    double sumxy = 0.0;
    double sumy = 0.0;
    double sumy2 = 0.0;

    for (int i = 0; i < num_values; i++) {
        sumx += x_arr[i];
        sumx2 += x_arr[i] * x_arr[i];
        sumxy += x_arr[i] * y_arr[i];
        sumy += y_arr[i];
        sumy2 += y_arr[i] * y_arr[i];
    }

    struct LineParams2D result;
    const double denom = (num_values * sumx2 - sumx * sumx);
    if (denom == 0) {
        // singular matrix. can't solve the problem.
        result.slope = 0;
        result.y_intercept = 0;
        return result;
    }

    result.slope = (num_values * sumxy - sumx * sumy) / denom;
    result.y_intercept = (sumy * sumx2 - sumx * sumxy) / denom;

    return result;
}
