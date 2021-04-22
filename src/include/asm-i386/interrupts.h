/*
 * include/asm-i386/interrupts.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-19
 */

/*
 * Interrupts and interrupts handlers initialization and manipulation
 */

#ifndef __ASM_INTERRUPTS_H__
#define __ASM_INTERRUPTS_H__

#include <types.h>
#include <asm/types.h>

// Number of interrupts, IA-32 have 256
#define INTERRUPTS_COUNT 256

/**
 * IA-32 Interrupts management data structures
 */

/**
 * Pointer to IDT
 */
typedef struct {
	uint16 limit;
	uint32 base;		// Should be 8 bytes aligned
} __attribute__((packed)) ia32_idt_ptr_t;

/**
 * An interrupt gate, there should be one interrupt gate for each interrupt
 * vector in IDT
 */
typedef struct {
	uint16 offset_low;
	uint16 segment_selector;
	uint8 zero;
	uint8 attrs; // P DPL 0D110
	uint16 offset_high;
} __attribute__((packed)) ia32_interrupt_gate_t;

/**
 * Initialize the interrupts mechanism
 */
void interrupts_init();


extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
//extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();

extern void isr_32();
extern void isr_33();
extern void isr_34();
extern void isr_35();
extern void isr_36();
extern void isr_37();
extern void isr_38();
extern void isr_39();
extern void isr_40();
extern void isr_41();
extern void isr_42();
extern void isr_43();
extern void isr_44();
extern void isr_45();
extern void isr_46();
extern void isr_47();

#endif // !_ASM_INTERRUPTS_H__
