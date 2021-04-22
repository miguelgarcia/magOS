/*
 * include/asm-i386/segments.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-24
 */

/*
 * Segments manipulation and initialization
 */

#ifndef __ASM_SEGMENTS_H__
#define __ASM_SEGMENTS_H__

#include <types.h>
#include <asm/types.h>

#define SEGMENT_DESC_SIZE		sizeof(ia32_segment_descriptor_t)

#define SEGMENTS_COUNT 6

// Segments selectors indexes
#define NULL_SELECTOR_INDEX	0
#define CS_SELECTOR_L0_INDEX	1
#define DS_SELECTOR_L0_INDEX	2
#define CS_SELECTOR_L3_INDEX	3
#define DS_SELECTOR_L3_INDEX	4
#define TSS_SELECTOR_INDEX		5

// Segments selectors
#define NULL_SELECTOR	(NULL_SELECTOR_INDEX * SEGMENT_DESC_SIZE)
#define CS_SELECTOR_L0	(CS_SELECTOR_L0_INDEX * SEGMENT_DESC_SIZE)
#define DS_SELECTOR_L0	(DS_SELECTOR_L0_INDEX * SEGMENT_DESC_SIZE)
#define CS_SELECTOR_L3	(CS_SELECTOR_L3_INDEX * SEGMENT_DESC_SIZE)
#define DS_SELECTOR_L3	(DS_SELECTOR_L3_INDEX * SEGMENT_DESC_SIZE)
#define TSS_SELECTOR		(TSS_SELECTOR_INDEX * SEGMENT_DESC_SIZE)

// Segments options

#define GRANULARITY_BYTE 0
#define GRANULARITY_KB 0x80

#define GDT_DEFAULT_OP_SIZE_32 0x40
#define GDT_DEFAULT_OP_SIZE_16 0

#define IDT_DEFAULT_OP_SIZE_32 0x8
#define IDT_DEFAULT_OP_SIZE_16 0

// Segment system/not system

#define SEG_SYSTEM 0x00
#define SEG_NON_SYSTEM 0x10

// Segment types for non system segments

#define SEG_TYPE_DATA				0x0
#define SEG_TYPE_RO 					0x0
#define SEG_TYPE_RW 					0x2
#define SEG_TYPE_EXPAND_DOWN 		0x4

#define SEG_TYPE_CODE 			0x8
#define SEG_TYPE_EXEC_ONLY 	0x0
#define SEG_TYPE_READ 			0x2
#define SEG_TYPE_CONFORMING 	0x4

// Segment types for system segments
#define SEG_TYPE_TSS	0x9
#define SEG_TYPE_LDT 0x2

// Segment privelege levels
#define SEG_PRIVILEGE_LEVEL_0 0x00
#define SEG_PRIVILEGE_LEVEL_1 0x20
#define SEG_PRIVILEGE_LEVEL_2 0x40
#define SEG_PRIVILEGE_LEVEL_3 0x60

// Segment present/not present
#define SEGMENT_PRESENT 0x80
#define SEGMENT_NOT_PRESENT 0x00

typedef struct {
	uint16 limit_low;
	uint16 base_low;
	uint8  base_middle;
	uint8  access; // P DPL S TYPE
	uint8  limit_high; // G D/B L AVL LIMIT
	uint8  base_high;
} __attribute__((packed)) ia32_segment_descriptor_t;

typedef struct {
	uint16 limit;
	uint32 base;		// Should be 8 bytes aligned
} __attribute__((packed)) ia32_gdt_ptr_t;


#define TSS_BUSY 			0x2
#define TSS_AVAILABLE 	0x0

typedef struct {
	selector_t previous_task_link;
	uint16 res_1;

	reg_t esp0;
	selector_t ss0;
	uint16 res_2;

	reg_t esp1;
	selector_t ss1;
	uint16 res_3;

	reg_t esp2;
	selector_t ss2;
	uint16 res_4;

	reg_t cr3;
	reg_t eip;
	reg_t eflags;
	reg_t eax;
	reg_t ecx;
	reg_t edx;
	reg_t ebx;
	reg_t esp;
	reg_t ebp;
	reg_t esi;
	reg_t edi;

	selector_t es;
	uint16 res_5;

	selector_t cs;
	uint16 res_6;

	selector_t ss;
	uint16 res_7;

	selector_t ds;
	uint16 res_8;

	selector_t fs;
	uint16 res_9;

	selector_t gs;
	uint16 res_10;

	selector_t ldt;
	uint16 res_11;
	
	uint16 debug;
	uint16 io_map_base;
} __attribute__((packed)) ia32_tss_t;

/**
 * Initializes the memory segmentation mechanism and the TSS.
 */
void mem_segments_init();

#endif // !__ASM_SEGMENTS_H__
