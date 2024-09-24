#include "calculate_module.h"

#ifndef UNIT_TEST
#include <linux/kernel.h>
#else
#include "calculate_module_mocks.h"
#endif

int gcd(int a, int b) {
    if (a == 0)
        return b;
    while (b != 0) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}
