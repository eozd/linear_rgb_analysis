#include "rgb_analysis.h"
#include "line_params_2D.h"
#include "linear_regression.h"
#include "utils.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Write the gnuplot script that will be used to produce analysis graphs.
 *
 * @param stream File object to write the script.
 * @param num_colors Number of values in each R, G and B channel.
 * @param orig_arrs Array containing original red, green and blue channel
 * values.
 * @param pred_arrs Red, green and blue channel predictions.
 * @param title_arr Array of graph titles for each of R, G and B.
 * @param stat_arr Array of stat arrays for R, G and B channels. Each stat array
 * must contain the angle and the MSE value, respectively.
 */
static void write_gnuplot_script(FILE* stream, int num_colors,
                                 const int* orig_arrs[3],
                                 const double* pred_arrs[3],
                                 const char* title_arr[3],
                                 const double* stat_arr[3]) {
    char* color_names[3];
    color_names[0] = "Red";
    color_names[1] = "Green";
    color_names[2] = "Blue";

    char gnuplot_color_name[10];
    memset(gnuplot_color_name, 0, 10);

    int i;
    for (i = 0; i < 3; ++i) {
        fprintf(stream, "set terminal \'qt\' %d title \"%s\" persist\n", i,
                title_arr[i]);
        fprintf(stream, "set title \"%s\"\n", color_names[i]);
        fprintf(stream, "set xlabel \"Sample\"\n");
        fprintf(stream, "set ylabel \"%s value\"\n", color_names[i]);
        fprintf(stream, "set yrange [-25:300]\n");
        fprintf(stream, "unset label\n");
        fprintf(
            stream,
            "set label \"Angle\\t: %f\\nMSE\\t: %f\\n\" at graph 0.04, 0.96\n",
            stat_arr[i][0], stat_arr[i][1]);

        strcpy(gnuplot_color_name, color_names[i]);
        gnuplot_color_name[0] = tolower(gnuplot_color_name[0]);

        fprintf(stream,
                "plot \"-\" with circles lc rgb \"%s\" fill solid title \"%s "
                "source\", \\\n",
                gnuplot_color_name, color_names[i]);
        fprintf(
            stream,
            "     \"-\" with line lc rgb \"0x000000\" title \"%s predicted\"\n",
            color_names[i]);

        int j;
        for (j = 0; j < num_colors; ++j) {
            fprintf(stream, "%d %d %f\n", j, orig_arrs[i][j], 0.25);
        }
        fprintf(stream, "e\n");
        for (j = 0; j < num_colors; ++j) {
            fprintf(stream, "%d %f\n", j, pred_arrs[i][j]);
        }
        fprintf(stream, "pause mouse close\n");
        fprintf(stream, "EOF\n");
        fprintf(stream, "pause 0.1\n");
    }
}

/**
 * @brief Calculate output statistics and save the results to given
 * RGBStatistics output pointer.
 *
 * @param num_colors Number of values in each R, G and B channel.
 * @param orig_arrs Array containing original red, green and blue channel
 * values.
 * @param pred_arrs Red, green and blue channel predictions.
 * @param line_arrs Array of LineParams2D structs containing the line parameters
 * for R, G and B channels.
 * @param out_stats RGBStatistics struct to write the resulting statistics.
 */
static void calculate_stats(int num_colors, const int* orig_arrs[3],
                            const double* pred_arrs[3],
                            const struct LineParams2D* line_arrs[3],
                            struct RGBStatistics* outputs) {
    outputs->red_line_angle = atan(line_arrs[0]->slope) * 180.0 / PI;
    outputs->red_line_mse = mse(num_colors, orig_arrs[0], pred_arrs[0]);

    outputs->green_line_angle = atan(line_arrs[1]->slope) * 180.0 / PI;
    outputs->green_line_mse = mse(num_colors, orig_arrs[1], pred_arrs[1]);

    outputs->blue_line_angle = atan(line_arrs[2]->slope) * 180.0 / PI;
    outputs->blue_line_mse = mse(num_colors, orig_arrs[2], pred_arrs[2]);
}

int analyze_rgb(int num_colors, const int* r_orig, const int* g_orig,
                const int* b_orig, bool draw_graphs, const char* serial_no,
                const char* gnuplot_path, struct RGBStatistics* outputs) {
    int* x_arr = (int*)(malloc(num_colors * sizeof(int)));
    int i;
    for (i = 0; i < num_colors; ++i) {
        x_arr[i] = i + 1;
    }

    struct LineParams2D r_line = linear_regression(num_colors, x_arr, r_orig);
    struct LineParams2D g_line = linear_regression(num_colors, x_arr, g_orig);
    struct LineParams2D b_line = linear_regression(num_colors, x_arr, b_orig);

    double* r_pred = (double*)(malloc(num_colors * sizeof(double)));
    double* g_pred = (double*)(malloc(num_colors * sizeof(double)));
    double* b_pred = (double*)(malloc(num_colors * sizeof(double)));

    for (i = 0; i < num_colors; ++i) {
        r_pred[i] = x_arr[i] * r_line.slope + r_line.y_intercept;
        g_pred[i] = x_arr[i] * g_line.slope + g_line.y_intercept;
        b_pred[i] = x_arr[i] * b_line.slope + b_line.y_intercept;
    }

    free(x_arr);

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

    int title_buffer_size = strlen(serial_no) + 10;
    char* red_title = (char*)(calloc(title_buffer_size, sizeof(char)));
    char* green_title = (char*)(calloc(title_buffer_size, sizeof(char)));
    char* blue_title = (char*)(calloc(title_buffer_size, sizeof(char)));

    sprintf(red_title, "%s_%s", "RED", serial_no);
    sprintf(green_title, "%s_%s", "GREEN", serial_no);
    sprintf(blue_title, "%s_%s", "BLUE", serial_no);
    const char* title_arr[3];
    title_arr[0] = red_title;
    title_arr[1] = green_title;
    title_arr[2] = blue_title;

    calculate_stats(num_colors, orig_arrs, pred_arrs, line_arrs, outputs);

    char* filename = (char*)(calloc(strlen(serial_no) + 50, sizeof(char)));
    sprintf(filename, "gnuplot_%s.plt", serial_no);
    FILE* gnuplot_script = fopen(filename, "w");
    double red_stats[2];
    red_stats[0] = outputs->red_line_angle;
    red_stats[1] = outputs->red_line_mse;

    double green_stats[2];
    green_stats[0] = outputs->green_line_angle;
    green_stats[1] = outputs->green_line_mse;

    double blue_stats[2];
    blue_stats[0] = outputs->blue_line_angle;
    blue_stats[1] = outputs->blue_line_mse;

    const double* stat_arr[3] = {red_stats, green_stats, blue_stats};

    write_gnuplot_script(gnuplot_script, num_colors, orig_arrs, pred_arrs,
                         title_arr, stat_arr);
    fclose(gnuplot_script);

    if (draw_graphs) {
        int gnuplot_path_len = strlen(gnuplot_path);
        int cmd_len = gnuplot_path_len + strlen(filename) + 100;

        char* cmd = (char*)(calloc(cmd_len, sizeof(char)));
        sprintf(cmd, "%s -p -c %s", gnuplot_path, filename);
        system(cmd);
        free(cmd);
    }

    free(filename);
    free(red_title);
    free(green_title);
    free(blue_title);
    free(r_pred);
    free(g_pred);
    free(b_pred);

    return 0;
}
