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
 * This function analyzes the individual red (R), green (G) and blue (B)
 * channels by fitting a line to the given data points (pixels). Afterwards,
 * various statistics such as angle and prediction error as mean squared error
 * (see mse) are calculated.
 *
 * Graphical representation of the given pixel values and the predicted line
 * can be obtained by enabling the draw_graph value. In this case, serial number
 * of the tested device is taken as input to set it as the title of the graph
 * window.
 *
 * @param num_colors Number of pixel values in each of R, G and B channels.
 * Number of pixels in each channel is assumed to be the same.
 * @param r_orig Pointer to the beginning of Red channel pixel values stored as
 * integers.
 * @param g_orig Pointer to the beginning of Green channel pixel values stored
 * as integers.
 * @param b_orig Pointer to the beginning of Blue channel pixel values stored as
 * integers.
 * @param serial_no Serial number of the tested device as a string. This number
 * will be displayed as the graphical window title.
 * @param draw_graph If set to 1, a graphical representation of the analysis
 * will be displayed. If set to 0, no graphics are displayed.
 */
struct RGBStatistics analyze_rgb(int num_colors, const int* r_orig,
                                 const int* g_orig, const int* b_orig,
                                 const char* serial_no, int draw_graph);

#endif
