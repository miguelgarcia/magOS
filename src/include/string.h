/*
 * include/string.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-23
 */

/*
 * Strings manipulation functions
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <types.h>

char *strncpy(char *, const char *, size_t);

void *memset(void *, int, size_t);

size_t strlen(const char *);

#endif /* ! __STRING_H__ */
