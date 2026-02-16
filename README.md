# LineEq C++ Class

A simple, well-documented C++ class for representing and evaluating line equations in 2D space with output limiting. The code includes comprehensive Doxygen-style comments and is organized into a clean header/implementation pair.

## Overview

The `LineEq` class (inside the `Tools` namespace) allows you to:

- Define a line from two points.
- Specify minimum and maximum output bounds.
- Evaluate the line at any x‑coordinate, with automatic clamping to the output limits.
- Correctly handle vertical lines (slope undefined).

This implementation is suitable for embedded systems, mathematical modeling, or any application requiring constrained linear interpolation.

## Features

- **Point-based construction** – create a line from two `point_t` structures.
- **Vertical line support** – detection and handling of vertical lines.
- **Output clamping** – ensure evaluated values stay within `[min_output, max_output]`.
- **Doxygen documentation** – every function, struct, and member is commented for automatic documentation generation.
- **Packed structures** – `__attribute__((packed))` ensures minimal memory footprint (useful for embedded targets).
- **Namespace encapsulation** – all components reside in `Tools` to avoid name clashes.

## Requirements

- C++ compiler with C++11 support (or later).
- Standard library (`<cmath>` for `fabs`).
- (Optional) Doxygen to generate HTML/PDF documentation.

## Installation

Simply copy `lineEq.h` and `lineEq.cpp` into your project and include the header where needed.

```cpp
#include "lineEq.h"
```
## Usage
- 1. Define two points

```cpp
Tools::LineEq::point_t p1 = {1.0f, 2.0f};
Tools::LineEq::point_t p2 = {3.0f, 4.0f};
```

- 2. Create a line with output limits
     
```cpp
Tools::LineEq line;
line.create(p1, p2, -10.0f, 10.0f);  // min_output = -10, max_output = 10
```

- 3. Evaluate at a given x

```cpp
float y = line.evaluate(2.5f);  // returns the clamped y value
```

## Example

```cpp
#include <iostream>
#include "lineEq.h"

int main() {
    using namespace Tools;

    LineEq::point_t a = {0.0f, 0.0f};
    LineEq::point_t b = {5.0f, 5.0f};

    LineEq line;
    line.create(a, b, 0.0f, 10.0f);   // line y = x, but output limited to [0,10]

    std::cout << "f(2.0) = " << line.evaluate(2.0f) << std::endl;   // 2.0
    std::cout << "f(12.0) = " << line.evaluate(12.0f) << std::endl; // 10.0 (clamped)

    return 0;
}
```





