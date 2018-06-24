#ifndef LINE_PARAMS_2D_H
#define LINE_PARAMS_2D_H

/**
 * @brief Parameters to fully define a 2D line.
 */
struct LineParams2D {
	/**
	 * @brief Slope of the line.
	 */
	double slope;
	/**
	 * @brief Value where the line intercepts the \f$y\f$-axis.
	 */
	double y_intercept;
};

#endif
