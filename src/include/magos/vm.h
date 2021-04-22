/*
 * include/magos/vm.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-02-06
 */

/*
 * VM functions for magOS.
 */

#ifndef __MAGOS_VM_H__
#define __MAGOS_VM_H__

#include <magos/magos.h>
#include <asm/vm.h>

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
 * Marks the page containing the address `vir_addr` as not present in the
 * current page directory.
 *
 * @param dir: pointer to the page directory to modify.
 * @param vir_addr: virtual address in the page to unmap.
 *
 * @requires vm_page_alloced(dir, vir_addr)
 */
void vm_unmap_page(vaddr_t vir_addr);

#endif /* ! __MAGOS_VM_H__ */
