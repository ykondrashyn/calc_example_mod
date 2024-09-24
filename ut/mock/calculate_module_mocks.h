#ifndef CALCULATE_MODULE_MOCKS_H
#define CALCULATE_MODULE_MOCKS_H

#ifdef UNIT_TEST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Replace kernel functions with standard library functions */
#define kmalloc(size, flags) malloc(size)
#define kfree(ptr) free(ptr)
#define printk(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define GFP_KERNEL 0  /* Ignored in userspace */

/* Replace kernel module macros with empty definitions */
#define module_param(name, type, perm)
#define MODULE_PARM_DESC(name, desc)
#define module_init(func)
#define module_exit(func)
#define MODULE_LICENSE(license)
#define MODULE_AUTHOR(author)
#define MODULE_DESCRIPTION(desc)
#define __init
#define __exit
#define KERN_INFO ""  /* Ignored in userspace */
#define S_IRUGO 0     /* Ignored in userspace */

#endif /* UNIT_TEST */

#endif /* CALCULATE_MODULE_MOCKS_H */

