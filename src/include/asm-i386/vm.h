/*
 * include/asm-i386/vm.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-27
 */

/*
 * VM functions and data structures for IA-32
 */

#ifndef __ASM_VM_H__
#define __ASM_VM_H__

#include <types.h>
#include <asm/types.h>

#define VM_MAX_ADDRESS ((vaddr_t) 0xFFFFFFFF)

typedef struct {
	uint32 present 		: 1;
	uint32 rw 				: 1;
	uint32 user 			: 1;
	uint32 write_through : 1;
	uint32 nocache			: 1;
	uint32 accessed 		: 1;
	uint32 dirty 			: 1;
	uint32 reserved 		: 1;
	uint32 global	 		: 1;
	uint32 avail	 		: 3;
	uint32 base_addr 		: 20;
} __attribute__((packed)) vm_page_attr_t;

typedef struct {
	uint32 present 		: 1;
	uint32 rw 				: 1;
	uint32 user 			: 1;
	uint32 write_through : 1;
	uint32 nocache			: 1;
	uint32 accessed 		: 1;
	uint32 dirty 			: 1;
	uint32 reserved 		: 2;
	uint32 avail	 		: 3;
	uint32 base_addr 		: 20;
} __attribute__((packed)) vm_page_table_attr_t;

typedef struct {
	vm_page_attr_t pages[1024];
} __attribute__((packed)) vm_page_table_t;

typedef struct {
	vm_page_table_attr_t tables_phys[1024];
	vm_page_table_t *tables[1024];
	paddr_t phys_addr;
} __attribute__((packed)) vm_page_directory_t;

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
void vm_map_page_d(vm_page_directory_t *dir, vaddr_t vir_addr, paddr_t phys_addr);

/**
 * Maps the page of the virtual address `vir_addr` points to physical page
 * of `phys_addr` using kernel page directory.
 *
 * @param vir_addr: virtual address in the page to map.
 * @param phys_addr: physical address in the page to map to.
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
void vm_map_page(vaddr_t vir_addr, paddr_t phys_addr);

/**
 * Marks the page containing the address `vir_addr` as not present.
 *
 * @param dir: pointer to the page directory to modify.
 * @param vir_addr: virtual address in the page to unmap.
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
void vm_unmap_page_d(vm_page_directory_t *dir, vaddr_t vir_addr);

/**
 * Marks the page containing the address `vir_addr` as not present in the
 * current page directory.
 *
 * @param dir: pointer to the page directory to modify.
 * @param vir_addr: virtual address in the page to unmap.
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
void vm_unmap_page(vaddr_t vir_addr);

/**
 * Deletes the entry to the page in the page table and if the page
 * table gets empty also deletes the entry in the page directory.
 *
 * @param dir: pointer to the page directory to modify.
 * @param vir_addr: virtual address in the page free.
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
void vm_free_page(vm_page_directory_t *dir, vaddr_t vir_addr);

/**
 * Allocates the entry to the page in the page table and if the page
 * table doesn't exist also creates it and add the entry to the page directory.
 *
 * @param dir: pointer to the page directory to modify.
 * @param vir_addr: virtual address in the page to create.
 */
void vm_init_page(vm_page_directory_t *dir, vaddr_t vir_addr);

/**
 * Returns if the page table containing the page is present
 *
 * @param dir: pointer to the page directory.
 * @param vir_addr: virtual address in the page.
 */
bool vm_page_alloced(vm_page_directory_t *dir, vaddr_t vir_addr);

/**
 * Initializes a page directory
 * Marks all pages as not present.
 *
 * @param dir: pointer to the page directory to initialize.
 */
void vm_init_directory(vm_page_directory_t *dir);

/**
 * Frees all physical pages used for page tables by thep age directory
 *
 * Note: this will not free the physical pages mapped by virtual pages nor
 * the space occupied by the directory data structure.
 *
 * @param dir: pointer to the page directory to free.
 */
void vm_free_directory(vm_page_directory_t *dir);

/**
 * Sets the attributes of a page
 *
 * @param dir: pointer to the page directory where the page resides.
 * @param vir_addr: virtual address in the page
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
void vm_set_page_attributes(vm_page_directory_t *dir, vaddr_t vir_addr, bool rw, bool user, bool write_through, bool nocache, bool global);

/**
 * Sets the attributes of a page table
 *
 * @param dir: pointer to the page directory where the page resides.
 * @param vir_addr: virtual address in the page table
 */
void vm_set_page_table_attributes(vm_page_directory_t *dir, vaddr_t vir_addr, bool rw, bool user, bool write_through, bool nocache);

/**
 * Returns attributes of the page that contains `vir_addr`
 *
 * @param dir: pointer to the page directory where the page resides
 * @param vir_addr: virtual address in the page
 *
 * @return page attributes
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
vm_page_attr_t vm_get_page_attributes(vm_page_directory_t *dir, vaddr_t vir_addr);

/**
 * Returns attributes of the page table that contains `vir_addr`
 *
 * @param dir: pointer to the page directory where the page resides
 * @param vir_addr: virtual address in the page table
 *
 * @return page table attributes
 */
vm_page_table_attr_t vm_get_page_table_attributes(vm_page_directory_t *dir, vaddr_t vir_addr);

/**
 * Returns if a page is present or not
 *
 * @param dir: pointer to the page directory where the page resides
 * @param vir_addr: virtual address in the page
 *
 * @return TRUE if the page is present, else FALSE
 */
bool vm_is_present(vm_page_directory_t *dir, vaddr_t vir_addr);

/**
 * Returns the physical address where is mapped the virtual address ´vir_addr´
 *
 * @param dir: pointer to the page directory where the page resides
 * @param vir_addr: virtual address
 *
 * @return The physical address
 *
 * @requires vm_is_present(dir, vir_addr)
 */
paddr_t vm_get_phys_addr(vm_page_directory_t *dir, vaddr_t vir_addr);
/**
 * Sets the current page directory
 *
 * @param dir: pointer to the page directory to use.
 */
void vm_switch_directory(vm_page_directory_t *);

// TODO: provide a function to allow multiple directories share page tables

#endif /* ! __ASM_VM_H__ */
