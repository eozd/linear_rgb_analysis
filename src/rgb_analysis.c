#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rgb_analysis.h"
#include "linear_regression.h"
#include "line_params_2D.h"
#include "utils.h"

static void write_gnuplot_script(FILE* stream, int num_colors, const int* orig_arrs[3], const double* pred_arrs[3], const char* title_arr[3]) {
	char* color_names[3];
	color_names[0] = "red";
	color_names[1] = "green";
	color_names[2] = "blue";

	int i;
	for (i = 0; i < 3; ++i) {
		fprintf(stream, "set terminal qt %d title \"%s\"\n", i, title_arr[i]);
		fprintf(stream, "set title \"%s\"\n", title_arr[i]);
		fprintf(stream, "set xlabel \"Index\"\n");
		fprintf(stream, "set ylabel \"%s value\"\n", title_arr[i]);
		fprintf(stream, "plot \"-\" with circles lc rgb \"%s\" fill solid title \"%s source\", \\\n", color_names[i], title_arr[i]);
		fprintf(stream, "     \"-\" with line lc rgb \"0x000000\" title \"%s predicted\"\n", title_arr[i]);

		int j;
		for (j = 0; j < num_colors; ++j) {
			fprintf(stream, "%d %d %f\n", j, orig_arrs[i][j], 0.25);
		}
		fprintf(stream, "EOF\n");
		for (j = 0; j < num_colors; ++j) {
			fprintf(stream, "%d %f\n", j, pred_arrs[i][j]);
		}
		fprintf(stream, "EOF\n");
	}
}

static void calculate_stats(int num_colors, const int* orig_arrs[3], const double* pred_arrs[3], const struct LineParams2D* line_arrs[3], struct RGBStatistics* out_stats) {
	out_stats->red_line_slope = line_arrs[0]->slope;
	out_stats->red_line_mse = mse(num_colors, orig_arrs[0], pred_arrs[0]);
	out_stats->red_line_R_squared = r_squared(num_colors, orig_arrs[0], pred_arrs[0]);

	out_stats->green_line_slope = line_arrs[1]->slope;
	out_stats->green_line_mse = mse(num_colors, orig_arrs[1], pred_arrs[1]);
	out_stats->green_line_R_squared = r_squared(num_colors, orig_arrs[1], pred_arrs[1]);

	out_stats->blue_line_slope = line_arrs[2]->slope;
	out_stats->blue_line_mse = mse(num_colors, orig_arrs[2], pred_arrs[2]);
	out_stats->blue_line_R_squared = r_squared(num_colors, orig_arrs[2], pred_arrs[2]);

}


struct RGBStatistics analyze_rgb(int num_colors, const int* r_orig, const int* g_orig, const int* b_orig, int draw_graphs) {
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

	struct RGBStatistics result_stats;
	calculate_stats(num_colors, orig_arrs, pred_arrs, line_arrs, &result_stats);

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

	return result_stats;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
