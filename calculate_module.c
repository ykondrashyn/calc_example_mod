#include "calculate_module.h"

#ifndef UNIT_TEST
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#else
#include "calculate_module_mocks.h"
#endif

static int number1 = 0;
static int number2 = 0;
static char *operation = "add";

module_param(number1, int, S_IRUGO);
MODULE_PARM_DESC(number1, "First number");
module_param(number2, int, S_IRUGO);
MODULE_PARM_DESC(number2, "Second number");
module_param(operation, charp, S_IRUGO);
MODULE_PARM_DESC(operation, "Operation: add, subtract, divide, multiply, power");

static int __init calc_init(void) {
    int result = 0;

    printk(KERN_INFO "Module loaded with arguments: number1=%d, number2=%d, operation=%s\n", number1, number2, operation);

    result = calculate(number1, number2, operation);
    printk(KERN_INFO "Result: %d\n", result);

    return 0;
}

static void __exit calc_exit(void) {
    printk(KERN_INFO "Module unloaded\n");
}

module_init(calc_init);
module_exit(calc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module that performs basic arithmetic operations using heap memory");
