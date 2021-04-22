/*
 * include/asm-i386/types.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-24
 */

/*
 * IA-32 data types
 */

#ifndef __ASM_TYPES_H__
#define __ASM_TYPES_H__

#include <types.h>

// CPU general purpose register
typedef uint32 reg_t;

// Segment selector
typedef uint16 selector_t;

typedef uint8 interrupt_t;

typedef uint32 vaddr_t;

typedef uint32 paddr_t;

#endif
