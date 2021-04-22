/*
 * lib/vsprintf.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-23
 */

/*
 * vsprintf implementation
 */

#include <stdarg.h>
#include <types.h>
#include <string.h>
#include <magos/klib.h>

int vsprintf(char *s, const char *format, va_list args) {
	static char hex_up_table[] = "0123456789ABCDEF";
	char buffer[11];
	
	unsigned int arg_uint;
	int arg_int;
	char *arg_string;
	uint8 i;
	int ret;

	while(*format) {
		if(*format == '%') {
			switch(*(++format)) {
				case 'X':
					arg_uint = va_arg(args, unsigned int);
					*s++ = '0';
					*s++ = 'x';
				
					for(i=0; i < sizeof(unsigned int) * 2; i++) {
						*s++ = hex_up_table[ (arg_uint & (0xF << (sizeof(unsigned int) * 8 - 4))) >> (sizeof(unsigned int) * 8 - 4)];
						arg_uint <<= 4;
					}
					ret += 2 + sizeof(unsigned int) * 2;
					break;
				case 'd':
					arg_int = va_arg(args, int);
					itoa(arg_int, buffer);
					i=0;
					while(buffer[i] != '\0') {
						*s++ = buffer[i++];
						ret++;
					}
					break;
				case 's':
					arg_string = va_arg(args, char *);
					while(*arg_string) {
						*s++ = *arg_string++;
						ret++;
					}
					break;
				case '%':
					*s++ = '%';
					ret++;
					break;
			}
		}
		else {
			*s++ = *format;
			ret++;
		}
	format++;
	}  
	*s = '\0';

	return ret;
}
