#include <stdlib.h>
#include "linear_regression.h"
#include "line_params_2D.h"

struct LineParams2D linear_regression(const int* y_arr, int num_values) {
	struct LineParams2D result;
	result.slope = 1;
	result.y_intercept = 1;

	int epochs = 100000;
	double eta = 0.0001;
	int iter;
	int i;
	double* y_curr = (double*)(malloc(num_values * sizeof(double)));
	double cost;
	double diff;
	double slope_grad;
	double intercept_grad;

	for (iter = 0; iter < epochs; ++iter) {
		for (i = 0; i < num_values; ++i) {
			y_curr[i] = result.slope * i + result.y_intercept;
		}

		cost = 0;
		for (i = 0; i < num_values; ++i) {
			diff = y_arr[i] - y_curr[i];
			cost += diff * diff;
		}
		cost /= num_values;

		slope_grad = 0;
		intercept_grad = 0;
		for (i = 0; i < num_values; ++i) {
			slope_grad -= (2.0 / num_values) * i * (y_arr[i] - y_curr[i]);
			intercept_grad -= (2.0 / num_values) * (y_arr[i] - y_curr[i]);
		}

		result.slope -= eta * slope_grad;
		result.y_intercept -= eta * intercept_grad;
	}

	free(y_curr);
	return result;
}
