#include <asm/monitor.h>
#include <magos/config.h>
#include <const.h>
#include <types.h>

static uint8 cursor_x = 0, cursor_y = 0;
static uint8 color = 0x06;

// start of video memory
static uint16 *vid_mem = (uint16 *) VIDEO_ADDR;

// ---------------------------------------------------------------------------

void monitor_init(uint16 *video_base) {
	vid_mem = video_base;
}

/**
 * Sets the cursor position and if necessary scrolls the screen one line up
 */
static void setCursorPosition(uint8 x, uint8 y) {
   cursor_x = x;
   cursor_y = y;

   if(cursor_y >= HEIGHT) {
      monitor_scroll();
   }
}

/**
 * Scrolls the screen one line up and puts the cursor at the beginning of
 * the last line.
 */
static void monitor_scroll() {
   uint16 i;

   // Do the scrolling by copying all characters one line up.
   for(i=0; i < (HEIGHT-1) * WIDTH; i++) {
      vid_mem[i] = vid_mem[i + WIDTH];
   }

   /* Fill the last line with white spaces with black as background and
    * foreground color.
    */
   for(i= (HEIGHT-1) * WIDTH; i < HEIGHT * WIDTH; i++) {
      vid_mem[i] = 0x0020;
   }

   setCursorPosition(0, HEIGHT - 1);
}

/**
 * Prints a character on the screen at the current location and moves the
 * cursor to the next position.
 */
void monitor_putchar(char c) {
   switch(c) {
      case '\n':
         setCursorPosition(0, cursor_y + 1);
         break;
      default:
         // Print the character
         *(vid_mem + cursor_y * WIDTH + cursor_x) = (color << 8) | c;

         // Update cursor
         if(cursor_x == WIDTH - 1) {
            setCursorPosition(0, cursor_y + 1);
         }
         else {
            setCursorPosition(cursor_x + 1, cursor_y);
         }
         break;
   }
}

/**
 * Prints a null terminated string of characters on the screen at the cursor
 * location.
 * At the end cursor will be located next to the string.
 */
void monitor_puts(const char *s) {
   while(*s != '\0') {
      monitor_putchar(*s);
      s++;
   }
}

/**
 * Clears the screen, and puts the cursor at the beginning of the last line.
 */
void monitor_clear() {
   uint16 i;

   for(i=0; i < WIDTH * (HEIGHT - 1); i++) {
      /* Puts a white space with black as background and foreground color
       * in every screen position. 
       */
      vid_mem[i] = 0x0020;  
   }

   // puts the cursor at the beginning of the last line
   cursor_x = 0;
   cursor_y = HEIGHT - 1;
}
