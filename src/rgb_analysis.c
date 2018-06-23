#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rgb_analysis.h"
#include "utils.h"
#include "linear_regression.h"
#include "line_params_2D.h"

static void write_gnuplot_script(FILE* stream, int num_colors, const int* orig_arrs[3], const double* pred_arrs[3], const char* title_arr[3]) {
	char* color_names[3];
	color_names[0] = "red";
	color_names[1] = "green";
	color_names[2] = "blue";

	int i;
	for (i = 0; i < 3; ++i) {
		fprintf(stream, "set terminal qt %d title \"%s\"\n", i, title_arr[i]);
		fprintf(stream, "plot \"-\" with points lc rgb \"%s\" title \"%s source\", \\\n", color_names[i], title_arr[i]);
		fprintf(stream, "     \"-\" with points lc rgb \"0x000000\" title \"%s predicted\"\n", title_arr[i]);

		int j;
		for (j = 0; j < num_colors; ++j) {
			fprintf(stream, "%d\n", orig_arrs[i][j]);
		}
		fprintf(stream, "EOF\n");
		for (j = 0; j < num_colors; ++j) {
			fprintf(stream, "%f\n", pred_arrs[i][j]);
		}
		fprintf(stream, "EOF\n");
	}
}


static double mse(int num_colors, const int* orig, const double* pred) {
	double result = 0;
	double diff;
	int i;
	for (i = 0; i < num_colors; ++i) {
		diff = orig[i] - pred[i];
		result += diff * diff;
	}
	result /= num_colors;
	return result;
}


static double r_squared(int num_colors, const int* orig, const double* pred) {
	double pred_mean = 0;
	double tot_sum_squared = 0;
	double res_sum_squared = 0;
	double diff;

	int i;
	for (i = 0; i < num_colors; ++i) {
		pred_mean += pred[i];
	}
	pred_mean /= num_colors;

	for (i = 0; i < num_colors; ++i) {
		diff = orig[i] - pred_mean;
		tot_sum_squared += diff * diff;
	}

	for (i = 0; i < num_colors; ++i) {
		diff = orig[i] - pred[i];
		res_sum_squared += diff * diff;
	}

	return 1 - (res_sum_squared / tot_sum_squared);
}


static void print_stats(int num_colors, const int* orig_arrs[3], const double* pred_arrs[3], const struct LineParams2D* line_arrs[3], const char* title_arr[3]) {
	int i;
	for (i = 0; i < 3; ++i) {
		printf("%s Stream Statistics\n", title_arr[i]);
		int j;
		for (j = 0; j < strlen(title_arr[i]); ++j) {
			printf("-");
		}
		printf(  "------------------\n");
		printf("Predicted line slope                : %f\n", line_arrs[i]->slope);
		printf("Mean squared error (less is better) : %f\n", mse(num_colors, orig_arrs[i], pred_arrs[i]));
		printf("R squared (1 is perfect)            : %f\n", r_squared(num_colors, orig_arrs[i], pred_arrs[i]));
		printf("\n");
	}
}


void analyze_rgb(const int* rgb_arr, int num_values, int draw_graphs) {
	assert(num_values % 3 == 0);
    int num_colors = num_values / 3;
    int* r_orig = (int*)(malloc(num_colors * sizeof(int)));
    int* g_orig = (int*)(malloc(num_colors * sizeof(int)));
    int* b_orig = (int*)(malloc(num_colors * sizeof(int)));
    separate_rgb_arr(rgb_arr, num_values, r_orig, g_orig, b_orig);

	struct LineParams2D r_line = linear_regression(r_orig, num_colors);
	struct LineParams2D g_line = linear_regression(g_orig, num_colors);
	struct LineParams2D b_line = linear_regression(b_orig, num_colors);

    double* r_pred = (double*)(malloc(num_colors * sizeof(double)));
    double* g_pred = (double*)(malloc(num_colors * sizeof(double)));
    double* b_pred = (double*)(malloc(num_colors * sizeof(double)));

	int i;
	for (i = 0; i < num_colors; ++i) {
		r_pred[i] = i * r_line.slope + r_line.y_intercept;
		g_pred[i] = i * g_line.slope + g_line.y_intercept;
		b_pred[i] = i * b_line.slope + b_line.y_intercept;
	}

	const int* orig_arrs[3];
	orig_arrs[0] = r_orig;
	orig_arrs[1] = g_orig;
	orig_arrs[2] = b_orig;

	const double* pred_arrs[3];
	pred_arrs[0] = r_pred;
	pred_arrs[1] = g_pred;
	pred_arrs[2] = b_pred;

	const struct LineParams2D* line_arrs[3];
	line_arrs[0] = &r_line;
	line_arrs[1] = &g_line;
	line_arrs[2] = &b_line;

	const char* title_arr[3];
	title_arr[0] = "RED";
	title_arr[1] = "GREEN";
	title_arr[2] = "BLUE";

	FILE* gnuplot_script = fopen("gnuplot_script.plt", "w");
	write_gnuplot_script(gnuplot_script, num_colors, orig_arrs, pred_arrs, title_arr);
	fclose(gnuplot_script);

	print_stats(num_colors, orig_arrs, pred_arrs, line_arrs, title_arr);

    free(r_orig);
    free(g_orig);
    free(b_orig);
    free(r_pred);
    free(g_pred);
    free(b_pred);

	if (draw_graphs) {
#ifdef LINUX
		system("gnuplot -p -c gnuplot_script.plt");
#elif defined WINDOWS
		system("gnuplot\\bin\\gnuplot.exe -p -c gnuplot_script.plt");
#else
		printf("Undefined platform. Define LINUX or WINDOWS!\n");
#endif
	}

	int x;
	scanf("%d", &x);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
