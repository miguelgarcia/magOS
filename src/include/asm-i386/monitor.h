#ifndef __HAL_ASM_MONITOR_H__
#define __HAL_ASM_MONITOR_H__

#include <types.h>

#define VIDEO_MEMORY_BASE 0xB8000
#define WIDTH (uint8) 80
#define HEIGHT (uint8) 25

/**
 * Sets the cursor position and if necessary scrolls the screen one line up
 */
static void setCursorPosition(uint8, uint8);

/**
 * Scrolls the screen one line up and puts the cursor at the beginning of
 * the last line.
 */
static void monitor_scroll();

/**
 * Prints a character on the screen at the current location and moves the
 * cursor to the next position.
 */
void monitor_putchar(char);

/**
 * Prints a null terminated string of characters on the screen at the cursor
 * location.
 * At the end cursor will be located next to the string.
 */
void monitor_puts(const char *);

/**
 * Clears the screen, and puts the cursor at the beginning of the last line.
 */
void monitor_clear();

/**
 * Initializes the video output using `video_base` as the base address
 * of the memory mapped video.
 */
void monitor_init(uint16 *video_base);

#endif
