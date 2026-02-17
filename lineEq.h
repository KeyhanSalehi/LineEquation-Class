/**
 * @addtogroup LineEq
 * @brief Line Equation Module
 * @details This module provides functionality for representing and evaluating
 *          line equations in 2D space with output limiting.
 * @author Salehi.K
 * @date Jan 6, 2026
 * @version 1.0
 * @note Any changes must be documented here
 */

#pragma once

#include <stdint.h>
#include <cmath>

namespace Tools {

/*!
 * @class LineEq
 * @brief Represents a line equation in 2D space with output constraints.
 */
class LineEq {
public:
    /*!
     * @struct point_t
     * @brief Represents a point in 2D space.
     */
    typedef struct __attribute__((packed)) {
        float x; /**< X-coordinate */
        float y; /**< Y-coordinate */
    } point_t;

    /*!
     * @brief Creates a new LineEquation object from two points.
     * @param p1 The first point on the line.
     * @param p2 The second point on the line.
     * @param minOut The minimum output value of the line equation.
     * @param maxOut The maximum output value of the line equation.
     */
    void create(point_t p1, point_t p2, float minOut, float maxOut);

    /*!
     * @brief Calculates the y-value of the line equation at a given x-coordinate.
     * @param x The x-coordinate.
     * @return The y-value of the line equation at the given x-coordinate,
     *         clamped between min_output and max_output.
     */
    float evaluate(float x);

private:
    /*!
     * @struct lineEq_t
     * @brief Internal representation of a line equation.
     */
    typedef struct __attribute__((packed)) {
        float slope;        /**< Slope of the line (m) */
        float y_intercept;  /**< Y-intercept of the line (b) */
        float min_output;   /**< Minimum allowed output value */
        float max_output;   /**< Maximum allowed output value */
        bool isVertical;    /**< Flag indicating if the line is vertical */
    } lineEq_t;

    lineEq_t _lineEq = { 0.0f, 0.0f, 0.0f, 0.0f, false };
};

} /* namespace Tools */
