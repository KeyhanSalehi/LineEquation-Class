/*!
 * @addtogroup LineEq.cpp
 * @brief Line Equation Module Implementation
 * @details Implementation of line equation operations
 * @author Salehi.K
 * @date Jan 6, 2026
 * @version 1.0
 * @note Any changes must be documented here
 */

#include <cmath>
#include "lineEq.h"

namespace Tools {

/*!
 * @brief Creates a new LineEquation object from two points.
 * @param p1 The first point on the line.
 * @param p2 The second point on the line.
 * @param minOut The minimum output value of the line equation.
 * @param maxOut The maximum output value of the line equation.
 */
void LineEq::create(point_t p1, point_t p2, float minOut, float maxOut) {
    /* Store output limits */
    _lineEq.min_output = minOut;
    _lineEq.max_output = maxOut;
    
    /* Calculate slope and intercept */
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    
    /* Handle vertical lines (slope undefined) */
    if (std::fabs(dx) < 1e-6f) {
        _lineEq.isVertical = true;
        _lineEq.slope = 0.0f;
        _lineEq.y_intercept = p1.x; /* Store x-coordinate for vertical lines */
    } else {
        _lineEq.isVertical = false;
        _lineEq.slope = dy / dx;
        _lineEq.y_intercept = p1.y - _lineEq.slope * p1.x;
    }
}

/*!
 * @brief Calculates the y-value of the line equation at a given x-coordinate.
 * @param x The x-coordinate.
 * @return The y-value of the line equation at the given x-coordinate,
 *         clamped between min_output and max_output.
 */
float LineEq::evaluate(float x) {
    float y = 0.0f;
    
    /* Calculate y based on line type */
    if (!_lineEq.isVertical) {
        y = _lineEq.slope * x + _lineEq.y_intercept;
    } else {
        /* For vertical lines, return the x-coordinate (or could return 0) */
        y = _lineEq.y_intercept;
    }
    
    /* Apply output limits */
    if (y < _lineEq.min_output) {
        y = _lineEq.min_output;
    } else if (y > _lineEq.max_output) {
        y = _lineEq.max_output;
    }
    
    return y;
}

} /* namespace Tools */
