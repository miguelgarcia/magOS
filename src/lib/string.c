/*
 * lib/string.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-23
 */

/*
 * String functions
 */

#include <string.h>

void *memset(void *to, int c, size_t n) {
	while(n-- >0) {
		*((uint8 *) to) = (uint8) c;
		to++;
	}
}

size_t strlen(const char *s) {
	size_t len = 0;
	
	while(*s++ != '\0') len++;
	return len;
}

void reverse(char *s) {
	size_t i, j;
	char tmp;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }	
}
