#ifndef CALCULATE_MODULE_H
#define CALCULATE_MODULE_H

enum operation_code {
    OP_INVALID = 0,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_POWER,
    OP_GCD
};

enum operation_code get_op_code(const char *op);
int calculate(int a, int b, const char *op);
int gcd(int a, int b);

#endif /* CALCULATE_MODULE_H */
