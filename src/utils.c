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

double r_squared(int num_values, const int* y_true, const double* y_pred) {
	const double eps = 1e-50;
	double y_mean = 0;
	double tot_sum_squared = 0;
	double res_sum_squared = 0;
	double diff;

	int i;
	for (i = 0; i < num_values; ++i) {
		y_mean += y_true[i];
	}
	y_mean /= num_values;

	for (i = 0; i < num_values; ++i) {
		diff = y_true[i] - y_mean;
		tot_sum_squared += diff * diff;
	}

	for (i = 0; i < num_values; ++i) {
		diff = y_true[i] - y_pred[i];
		res_sum_squared += diff * diff;
	}

	return 1 - (res_sum_squared / (tot_sum_squared + eps));
}

