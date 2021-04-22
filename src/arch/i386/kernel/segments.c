/*
 * hal/segments.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-17
 */

/*
 * Setup global descriptor table and TSS
 *
 * @see: Intel 64 and IA-32 Architectures  Software Developer's Manual Volume 3A
 */

#include <asm/segments.h>
#include <asm/low.h>
#include <const.h>
#include <types.h>

// Segments
ia32_gdt_ptr_t gdt_ptr;
ia32_segment_descriptor_t gdt_entries[SEGMENTS_COUNT] __attribute__((aligned(8)));

// The TSS to use
ia32_tss_t tss;

/**
 * Initializes the TSS.
 */
static void init_tss() {
	tss.ss0 = DS_SELECTOR_L0;
	tss.io_map_base = sizeof(tss);	// Empty IO map
	tss.res_1 = tss.res_2 = tss.res_3 = tss.res_4 = tss.res_5 = tss.res_6 = \
	tss.res_7 = tss.res_8 = tss.res_9 = tss.res_10 = tss.res_11 = 0;
}

/**
 * Setups an entry in the GDT.
 */
static void gdt_set_gate(uint32 index, uint32 base, uint32 limit, uint8 type, uint8 sys, \
						 uint8 dpl, uint8 present, uint8 op_size, uint8 granularity) {

	gdt_entries[index].limit_low = limit & 0xFFFF;
	gdt_entries[index].limit_high = (limit >> 16) & 0x0F;

	gdt_entries[index].base_low = base & 0xFFFF;
	gdt_entries[index].base_middle = (base >> 16) & 0xFF;
	gdt_entries[index].base_high = (base >> 24) & 0xFF;

	gdt_entries[index].access = present | dpl | sys | type;
	gdt_entries[index].limit_high |= granularity | op_size;

}

/**
 * Initializes the memory segmentation and also setups the TSS.
 */
void mem_segments_init() {
	init_tss();

	gdt_ptr.base = (uint32) &gdt_entries;
	gdt_ptr.limit = (sizeof(ia32_segment_descriptor_t) * SEGMENTS_COUNT) - 1;

	// null descriptor
	gdt_set_gate(NULL_SELECTOR_INDEX, 0, 0, 0, 0, 0, 0, 0, 0); 

   // code segment descriptor
	gdt_set_gate(CS_SELECTOR_L0_INDEX, 0, 0xFFFFFFFF, SEG_TYPE_CODE | SEG_TYPE_READ, \
		 SEG_NON_SYSTEM, SEG_PRIVILEGE_LEVEL_0, SEGMENT_PRESENT, GDT_DEFAULT_OP_SIZE_32, \
		 GRANULARITY_KB);

   // data segment descriptor
	gdt_set_gate(DS_SELECTOR_L0_INDEX, 0, 0xFFFFFFFF, SEG_TYPE_DATA | SEG_TYPE_RW, \
		 SEG_NON_SYSTEM, SEG_PRIVILEGE_LEVEL_0, SEGMENT_PRESENT, GDT_DEFAULT_OP_SIZE_32, \
		 GRANULARITY_KB);	

   // user code segment descriptor
	gdt_set_gate(CS_SELECTOR_L3_INDEX, 0, 0xFFFFFFFF, SEG_TYPE_CODE | SEG_TYPE_READ, \
		SEG_NON_SYSTEM, SEG_PRIVILEGE_LEVEL_3, SEGMENT_PRESENT, GDT_DEFAULT_OP_SIZE_32, \
		GRANULARITY_KB);

   // user data segment descriptor
	gdt_set_gate(DS_SELECTOR_L3_INDEX, 0, 0xFFFFFFFF, SEG_TYPE_DATA | SEG_TYPE_RW, \
		 SEG_NON_SYSTEM, SEG_PRIVILEGE_LEVEL_3, SEGMENT_PRESENT, GDT_DEFAULT_OP_SIZE_32, \
		 GRANULARITY_KB);

	gdt_set_gate(TSS_SELECTOR_INDEX, (uint32) &tss, sizeof(tss), SEG_TYPE_TSS, SEG_SYSTEM, SEG_PRIVILEGE_LEVEL_0, \
		SEGMENT_PRESENT, GDT_DEFAULT_OP_SIZE_32, GRANULARITY_BYTE);

	load_gdt(&gdt_ptr); // Tell the cpu to use the new gdt
	load_tss(TSS_SELECTOR);
}
