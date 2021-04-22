/*
 * include/asm-i386/types.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-24
 */

/*
 * IA-32 low level functions
 */

#ifndef __HAL_ASM_LOW_H__
#define __HAL_ASM_LOW_H__

#include <asm/segments.h>
#include <types.h>

/**
 * Loads the global descriptors table.
 */
extern void load_gdt(ia32_gdt_ptr_t *);

/**
 * Sets the current TSS.
 */
extern void load_tss(uint16);

/**
 * Loads IDT.
 */
extern void load_idt(uint32);

#endif // !__HAL_ASM_LOW_H__
