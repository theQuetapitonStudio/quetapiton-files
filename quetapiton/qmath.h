#pragma once

#define PI 3.14

static inline double sin(double x) {
    return x - (x*x*x) / 6
    + (x*x*x*x*x) / 120
    - (x*x*x*x*x*x*x) / 5040;
}

static inline double cos(double x) {
    return 1 -
    x*x/2 +
    x*x*x*x/24 -
    x*x*x*x*x*x/720 +
    x*x*x*x*x*x*x*x/40320 - 
    x*x*x*x*x*x*x*x*x*x/3628800;
}