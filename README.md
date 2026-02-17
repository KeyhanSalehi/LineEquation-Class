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

## Industrial 4-20mA Scaling Example
A common industrial use case is scaling a 4‑20 mA current loop sensor reading to an engineering unit (e.g., temperature, pressure). The sensor outputs 4 mA at the minimum physical value and 20 mA at the maximum. Using LineEq, you can define a line that maps current (mA) to the physical quantity and optionally clamp the result to safe limits.


```cpp
#include <iostream>
#include "lineEq.h"

// Simulated ADC reading to current (mA) conversion
float adc_to_mA(uint16_t adc_value, float adc_ref_voltage, float resistor) {
    // Assume ADC range 0-4095, voltage = (adc_value / 4095.0) * adc_ref_voltage
    float voltage = (adc_value / 4095.0f) * adc_ref_voltage;
    // Current through sense resistor: I = V / R
    return voltage / resistor;
}

int main() {
    using namespace Tools;

    // Sensor specifications: 4-20 mA corresponds to -40 to 85 °C
    constexpr float MIN_MA = 4.0f;
    constexpr float MAX_MA = 20.0f;
    constexpr float MIN_TEMP = -40.0f;
    constexpr float MAX_TEMP = 85.0f;

    // Define the scaling line: (mA, temp)
    LineEq::point_t p_low  = {MIN_MA, MIN_TEMP};
    LineEq::point_t p_high = {MAX_MA, MAX_TEMP};

    // Create line with output limits set to the sensor range (optional)
    LineEq scale;
    scale.create(p_low, p_high, MIN_TEMP, MAX_TEMP);

    // Simulate an ADC reading (e.g., 12 mA = 2048 counts with 3.3V ref, 165 Ω resistor)
    uint16_t adc_raw = 2048;   // 12 mA midpoint
    float current = adc_to_mA(adc_raw, 3.3f, 165.0f);

    // Convert current to temperature using the line equation
    float temperature = scale.evaluate(current);

    std::cout << "ADC raw: " << adc_raw << std::endl;
    std::cout << "Current: " << current << " mA" << std::endl;
    std::cout << "Temperature: " << temperature << " °C" << std::endl;

    // Test with out-of-range current (e.g., 3 mA – below 4 mA)
    current = 3.0f;
    temperature = scale.evaluate(current);   // Clamped to MIN_TEMP (-40°C)
    std::cout << "\nCurrent: " << current << " mA (out of range)" << std::endl;
    std::cout << "Temperature: " << temperature << " °C (clamped to min)" << std::endl;

    return 0;
}
```

