#include <stdio.h>
#include <stdlib.h>
#include "rgb_analysis.h"

void read_hex_arr(FILE* stream, int* out_arr, int num_values) {
    char line[10];
    int value;
    int idx = 0;
    while (fgets(line, sizeof(line), stream)) {
        value = strtol(line, NULL, 16);
        out_arr[idx++] = value;
    }
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return -1;
	}
	FILE* datafile = fopen(argv[1], "r");

    int num_lines;
    fscanf(datafile, "%d\n", &num_lines);
    int* rgb_arr = (int*)(malloc(num_lines * sizeof(int)));
    read_hex_arr(datafile, rgb_arr, num_lines);
	fclose(datafile);

	analyze_rgb(rgb_arr, num_lines, 1);

    free(rgb_arr);
}
