#include "calculate_module.h"

#ifndef UNIT_TEST
#include <linux/string.h>
#include <linux/slab.h>
#else
#include "calculate_module_mocks.h"
#endif

enum operation_code get_op_code(const char *op) {
    enum operation_code op_code = OP_INVALID;

    switch (op[0]) {
        case 'a':
            if (strcmp(op, "add") == 0)
                op_code = OP_ADD;
            break;
        case 's':
            if (strcmp(op, "subtract") == 0)
                op_code = OP_SUBTRACT;
            break;
        case 'm':
            if (strcmp(op, "multiply") == 0)
                op_code = OP_MULTIPLY;
            break;
        case 'd':
            if (strcmp(op, "divide") == 0)
                op_code = OP_DIVIDE;
            break;
        case 'p':
            if (strcmp(op, "power") == 0)
                op_code = OP_POWER;
            break;
        case 'g':
            if (strcmp(op, "gcd") == 0)
                op_code = OP_GCD;
            break;
        default:
            op_code = OP_INVALID;
            break;
    }

    return op_code;
}

int calculate(int a, int b, const char *op) {
    enum operation_code op_code = get_op_code(op);
    int result = 0;

    int *a_ptr = (int *)kmalloc(sizeof(int), GFP_KERNEL);
    int *b_ptr = (int *)kmalloc(sizeof(int), GFP_KERNEL);

    if (!a_ptr || !b_ptr) {
        printk("Error: Memory allocation failed\n");
        kfree(a_ptr);
        kfree(b_ptr);
        return 0;
    }

    *a_ptr = a;
    *b_ptr = b;

    switch (op_code) {
        case OP_ADD:
            result = *a_ptr + *b_ptr;
            break;
        case OP_SUBTRACT:
            result = *a_ptr - *b_ptr;
            break;
        case OP_MULTIPLY:
            result = *a_ptr * *b_ptr;
            break;
        case OP_DIVIDE:
            if (*b_ptr == 0) {
                printk("Error: Division by zero\n");
                result = 0;
            } else {
                result = *a_ptr / *b_ptr;
            }
            break;
        case OP_POWER: {
            int i;
            int *temp_result = (int *)kmalloc(sizeof(int), GFP_KERNEL);
            if (!temp_result) {
                printk("Error: Memory allocation failed\n");
                result = 0;
                break;
            }
            *temp_result = 1;
            if (*b_ptr < 0) {
                printk("Error: Negative exponent not supported\n");
                *temp_result = 0;
            } else {
                for (i = 0; i < *b_ptr; i++) {
                    *temp_result *= *a_ptr;
                }
            }
            result = *temp_result;
            kfree(temp_result);
            break;
        }
        case OP_GCD:
            result = gcd(*a_ptr, *b_ptr);
            break;
        default:
            printk("Invalid operation: %s\n", op);
            result = 0;
            break;
    }

    kfree(a_ptr);
    kfree(b_ptr);

    return result;
}
