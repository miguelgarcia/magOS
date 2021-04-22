#include <asm/interrupts.h>
#include <asm/cpucontext.h>
#include <asm/segments.h>
#include <asm/low.h>
#include <magos/vmpmalloc.h>
#include <const.h>

#define SET_ISR(x) (setup_isr(x, isr_##x))

static ia32_idt_ptr_t idt_ptr;
static ia32_interrupt_gate_t idt_entries[INTERRUPTS_COUNT] __attribute__((aligned(8)));

//static void (**interrupts_handlers)(interrupt_t);

/**
 * Initializes IDT.
 */
static void init_idt() {
	idt_ptr.base = (uint32) &idt_entries;
	idt_ptr.limit = (INTERRUPTS_COUNT * sizeof(ia32_interrupt_gate_t)) - 1;

	memset(&idt_entries, 0, INTERRUPTS_COUNT * sizeof(ia32_interrupt_gate_t));

	load_idt((uint32) &idt_ptr);
}

/**
 * Setups an entry in the IDT.
 */
static void idt_set_gate(uint8 index, uint32 offset, uint16 segment_selector, \
				uint8 dpl, uint8 present, uint8 op_size) {

	idt_entries[index].offset_low = offset & 0xFFFF;

	idt_entries[index].offset_high = (offset >> 16) & 0xFFFF;
	idt_entries[index].segment_selector = segment_selector;
	idt_entries[index].zero = 0;
	idt_entries[index].attrs = present | dpl | op_size | 0x6 ;	
}

/**
 * Installs an interrupt service routine for an interrupt vector.
 */
static void setup_isr(interrupt_t vector, void *isr) {
	idt_set_gate(vector, (uint32) isr, CS_SELECTOR_L0, SEG_PRIVILEGE_LEVEL_0, SEGMENT_PRESENT, IDT_DEFAULT_OP_SIZE_32);
}

/**
 * Initializes IDT entries.
 */
static void init_isrs() {
	SET_ISR(0);
	SET_ISR(1);
	SET_ISR(2);
	SET_ISR(3);
	SET_ISR(4);
	SET_ISR(5);
	SET_ISR(6);
	SET_ISR(7);
	SET_ISR(8);
	SET_ISR(9);
	SET_ISR(10);
	SET_ISR(11);
	SET_ISR(12);
	SET_ISR(13);
	SET_ISR(14);
	SET_ISR(16);
	SET_ISR(17);
	SET_ISR(18);
	SET_ISR(19);
	SET_ISR(32);
	SET_ISR(33);
	SET_ISR(34);
	SET_ISR(35);
	SET_ISR(36);
	SET_ISR(37);
	SET_ISR(38);
	SET_ISR(39);
	SET_ISR(40);
	SET_ISR(41);
	SET_ISR(42);
	SET_ISR(43);
	SET_ISR(44);
	SET_ISR(45);
	SET_ISR(46);
	SET_ISR(47);
}

/**
 * Initializes the interrupts mechanism.
 */
void interrupts_init() {
	init_idt();
	init_isrs();
}

/**
 * Enables interrupts.
 */
void disable_interrupts() {
	asm("cli");
}

/**
 * Disables interrupts.
 */
void enable_interrupts() {
	asm("sti");
}

/**
 * Handles all interrupts.
 */
void isr_handler(cpu_context_t *ctx) {
	kprintf("interrupt: %X\n", ctx->vector);
}
