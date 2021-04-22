/*
 * include/asm-i386/cpu_context.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-29
 */

/*
 * CPU context
 */

#ifndef __HAL_ASM_CPU_CONTEXT__
#define __HAL_ASM_CPU_CONTEXT__

#include <types.h>
#include <asm/types.h>

typedef struct cpu_context_s {
	reg_t ds;
	reg_t esi;
	reg_t edi;
	reg_t ebp;
	reg_t esp0;
	reg_t ebx;
	reg_t edx;
	reg_t ecx;	
	reg_t eax;
	uint32 vector;
	uint32 err;
	reg_t eip;
	reg_t cs;
	reg_t eflags;
	reg_t esp;
	reg_t ss;
} __attribute__((packed)) cpu_context_t;
#endif
