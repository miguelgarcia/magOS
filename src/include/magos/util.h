/*
 * kernel/util.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-23
 */

/*
 * Useful functions for use inside the kernel.
 */

#ifndef __MAGOS_UTIL_H__
#define __MAGOS_UTIL_H__

#include <stdarg.h>

/**
 * Printf for use inside the kernel.
 */
int kprintf(const char *, ...);

/**
 * Prints the error message, disables interrupts and enters an infinite loop.
 */
void kpanic(const char *, ...);

/**
 * Like vprintf.
 */
int kvprintf(const char *format, va_list args);

/**
 * vsprintf.
 */
int vsprintf(char *s, const char *format, va_list args);

#endif
