#ifndef RGB_ANALYSIS_H
#define RGB_ANALYSIS_H

struct RGBStatistics {
	double red_line_slope;
	double red_line_mse;
	double red_line_R_squared;
	double green_line_slope;
	double green_line_mse;
	double green_line_R_squared;
	double blue_line_slope;
	double blue_line_mse;
	double blue_line_R_squared;
};

struct RGBStatistics analyze_rgb(int num_colors, const int* r_orig, const int* g_orig, const int* b_orig, int draw_graph);

#endif
