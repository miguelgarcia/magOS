#include <magos/util.h>
#include <asm/monitor.h>
#include <asm/interrupts.h>
#include <stdarg.h>
#include <const.h>

/**
 * printf for use inside the kernel
 */
int kprintf(const char *format, ...) {
	int ret;
	va_list args;

	va_start(args, format);
	ret = kvprintf(format, args);
    va_end(args);

	return ret;
}

/**
 * vprintf for use inside the kernel
 */
int kvprintf(const char *format, va_list args) {
	int ret;

	char buffer[512];
	ret = vsprintf(buffer, format, args);

	monitor_puts(buffer);
	return ret;
}

/**
 * Prints the error message,
 * disables interrupts 
 * and enters an infinite loop.
 */
void kpanic(const char *format, ...) {
	va_list args;
	va_start(args, format);

	kvprintf(format, args);
	disable_interrupts();
	while(TRUE) {}
}
