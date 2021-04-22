/*
 * arch/i386/kernel/vm.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-27
 */

/*
 * VM low level functions for IA-32
 */

#include <asm/vm.h>
#include <magos/const.h>
#include <string.h>
#include <types.h>

// TODO: marcar las pagetables como nocache pues se cachean en TLB
// TODO: estas dos funciones podrian estar en otro archivo
static __inline__ void vm_flush_page(vaddr_t addr) {
	asm("invlpg %0"::"m"(*(uint32 *) addr));
}

static __inline__ paddr_t vm_get_cr3() {
	uint32 val;
	asm("mov %%cr3, %0":"=r"(val));
	return val;
}

/**
 * Maps the page of the virtual address `vir_addr` points to physical page
 * of `phys_addr`.
 *
 * @param dir: pointer to the page directory to modify.
 * @param vir_addr: virtual address in the page to map.
 * @param phys_addr: physical address in the page to map to.
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
void vm_map_page_d(vm_page_directory_t *dir, vaddr_t vir_addr, paddr_t phys_addr) {
	uint16 table = vir_addr >> 22;
	uint16 pageIdx = (vir_addr >> 12) & 0x3FF;

	// TODO: optimize this creatin the value using shifts and | and assign it to
	// dir->tables[table]->pages[pageIdx]
	dir->tables[table]->pages[pageIdx].base_addr = PHYS_PAGE(phys_addr);
	dir->tables[table]->pages[pageIdx].accessed = 0;
	dir->tables[table]->pages[pageIdx].dirty = 0;
	dir->tables[table]->pages[pageIdx].present = 1;


	if(dir->phys_addr == vm_get_cr3()) {
		vm_flush_page(vir_addr);
	}
}

/**
 * Marks a virtual page as not present
 *
 * @param addr An address in the virtual page
 */
void vm_unmap_page_d(vm_page_directory_t *dir, vaddr_t addr) {
	uint16 table = addr >> 22;
	uint16 pageIdx = (addr >> 12) & 0x3FF;
		
	dir->tables[table]->pages[pageIdx].accessed = 0;
	dir->tables[table]->pages[pageIdx].dirty = 0;
	dir->tables[table]->pages[pageIdx].present = 0;

	if(dir->phys_addr == vm_get_cr3()) {
		vm_flush_page(addr);
	}
}

/**
 * Initializes a page directory
 * Marks all pages as not present.
 *
 * @param dir: pointer to the page directory to initialize.
 */
void vm_init_directory(vm_page_directory_t *dir) {
	memset(&dir->tables_phys, 0, sizeof(vm_page_table_attr_t) * 1024);
	memset(&dir->tables, 0, sizeof(vm_page_table_t *) * 1024);
	//dir->phys_addr = vm_get_phys(dir);
}
