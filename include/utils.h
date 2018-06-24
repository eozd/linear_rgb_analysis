#ifndef UTILS_H_
#define UTILS_H_

/**
 * \mainpage RGB Analysis
 *
 * \section and Data Structures and Functions
 * You can refer to individual function documentations from the below list.
 *
 * @see analyze_rgb
 * @see RGBStatistics
 * @see LineParams2D
 * @see linear_regression
 * @see mse
 *
 * \section Usage
 * @see README.md file for installation and usage instructions.
 */

/**
 * @brief PI number.
 */
#define PI 3.1415926535897

/**
 * @brief Calculate mean squared error computed using the given true and
 * predicted output values.
 *
 * Mean squared error is defined as
 *
 * \f[
 *     \frac{1}{N}\sum_{i = 1}^N (f^2 - y^2)
 * \f]
 *
 * where \f$f\f$ is the predicted output value and \f$y\f$ is the true
 * output value. A prediction line fits a given data points better if the
 * resulting mean squared error value is smaller.
 *
 * @param num_values Number of output values in each of y_true and y_pred.
 * @param y_true True output values.
 * @param y_pred Predicted output values.
 *
 * @return Mean squared error (MSE).
 */
double mse(int num_values, const int* y_true, const double* y_pred);

#endif
