#include "rgb_analysis.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void read_hex_arr(FILE* stream, int* out_arr, int num_values) {
    char line[10];
    int value;
    int i;
    for (i = 0; i < num_values; ++i) {
        fgets(line, sizeof(line), stream);
        value = strtol(line, NULL, 16);
        out_arr[i] = value;
    }
}

static void separate_rgb_arr(const int* rgb_arr, int num_values, int* r_arr,
                             int* g_arr, int* b_arr) {
    int i = 0;
    while (i < num_values) {
        int color_idx = i / 3;
        r_arr[color_idx] = rgb_arr[i++];
        g_arr[color_idx] = rgb_arr[i++];
        b_arr[color_idx] = rgb_arr[i++];
    }
}

static void print_stats(const struct RGBStatistics* stats) {
    printf("RED Stream Statistics\n");
    printf("---------------------\n");
    printf("Predicted line right angle          : %f\n", stats->red_line_angle);
    printf("Mean squared error (less is better) : %f\n", stats->red_line_mse);
    printf("\n");

    printf("GREEN Stream Statistics\n");
    printf("-----------------------\n");
    printf("Predicted line right angle          : %f\n",
           stats->green_line_angle);
    printf("Mean squared error (less is better) : %f\n", stats->green_line_mse);
    printf("\n");

    printf("BLUE Stream Statistics\n");
    printf("----------------------\n");
    printf("Predicted line right angle          : %f\n",
           stats->blue_line_angle);
    printf("Mean squared error (less is better) : %f\n", stats->blue_line_mse);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    FILE* datafile = fopen(argv[1], "r");

    char buffer[7];
    fgets(buffer, 7, datafile);
    int num_lines = strtol(buffer, NULL, 10);

    int* rgb_arr = (int*)(malloc(num_lines * sizeof(int)));
    read_hex_arr(datafile, rgb_arr, num_lines);
    fclose(datafile);

    assert(num_lines % 3 == 0);
    int num_colors = num_lines / 3;

    int* r_orig = (int*)(malloc(num_colors * sizeof(int)));
    int* g_orig = (int*)(malloc(num_colors * sizeof(int)));
    int* b_orig = (int*)(malloc(num_colors * sizeof(int)));

    separate_rgb_arr(rgb_arr, num_lines, r_orig, g_orig, b_orig);
    struct RGBStatistics stats =
        analyze_rgb(num_colors, r_orig, g_orig, b_orig, "HX42457NTH", 1);
    print_stats(&stats);

    free(rgb_arr);
    free(r_orig);
    free(g_orig);
    free(b_orig);

    int x;
    scanf("%d", &x);
}
