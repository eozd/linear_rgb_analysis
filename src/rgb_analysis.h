#ifndef RGB_ANALYSIS_H
#define RGB_ANALYSIS_H

/**
 * @brief Struct to hold the output statistics of an RGB analysis.
 */
struct RGBStatistics {
	/**
	 * @brief Angle of the line that is fitted to red channel data values.
	 */
	double red_line_angle;
	/**
	 * @brief Mean squared error between the red channel points and the line
	 * fitted to red channel data values.
	 *
	 * @see mse function documentation for info about mean squared error.
	 */
	double red_line_mse;
	/**
	 * @brief Angle of the line that is fitted to green channel data values.
	 */
	double green_line_angle;
	/**
	 * @brief Mean squared error between the green channel points and the line
	 * fitted to green channel data values.
	 *
	 * @see mse function documentation for info about mean squared error.
	 */
	double green_line_mse;
	/**
	 * @brief Angle of the line that is fitted to blue channel data values.
	 */
	double blue_line_angle;
	/**
	 * @brief Mean squared error between the blue channel points and the line
	 * fitted to blue channel data values.
	 *
	 * @see mse function documentation for info about mean squared error.
	 */
	double blue_line_mse;
};

/**
 * @brief Compute various statistics and optionally plot illustrations for each
 * of the given R, G, B channels.
 *
 *
 */
struct RGBStatistics analyze_rgb(int num_colors, const int* r_orig, const int* g_orig, const int* b_orig, const char* serial_no, int draw_graph);

#endif
