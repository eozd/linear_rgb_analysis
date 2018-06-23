#include "utils.h"

void separate_rgb_arr(const int* rgb_arr, int num_values, int* r_arr, int* g_arr,
                      int* b_arr) {
    int i = 0;
    while (i < num_values) {
        int color_idx = i / 3;
        r_arr[color_idx] = rgb_arr[i++];
        g_arr[color_idx] = rgb_arr[i++];
        b_arr[color_idx] = rgb_arr[i++];
    }
}

