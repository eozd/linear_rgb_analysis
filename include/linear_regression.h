#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "line_params_2D.h"

/**
 * @brief Fit a 2D line to the given output values and return the parameters of
 * the line as a LineParams2D struct.
 *
 * This function fits a linear regression model to the given x and y
 * coordinates. A linear regression model fits a line to the given data points.
 * This is performed according to the following formula:
 *
 * \f[
 *     \boldsymbol{Y} = \boldsymbol{X}\boldsymbol{\beta} + \epsilon
 * \f]
 *
 * where \f$\boldsymbol{Y}\f$ is the vector of output values and
 * \f$\boldsymbol{X}\f$ is the vector of inputs. Here, \f$\boldsymbol{\beta}\f$
 * corresponds to model parameters. When the coordinates are 2D,
 * \f$\boldsymbol{\beta}\f$ consists of two values: slope and y-intercept.
 *
 * @param num_values Number of data points to fit.
 * @param x_arr Pointer to the beginning of input variable array
 * (\f$\boldsymbol{X}\f$).
 * @param y_arr Pointer to the beginning of output variable array
 * (\f$\boldsymbol{Y}\f$).
 *
 * @return LineParams2D struct containing the slope and y-intercept of the
 * fitted 2D line.
 */
struct LineParams2D linear_regression(int num_values, const int* x_arr,
                                      const int* y_arr);

#endif
