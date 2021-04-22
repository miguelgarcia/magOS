/*
 * include/magos/vmpmalloc.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-30
 */

/*
 * Virtual memory placement malloc functions
 *
 * It works assigning contiguos virtual address space
 *
 * The return address of vmpmalloc is always page aligned !!!
 */

#ifndef __MAGOS_VPMALLOC_H__
#define __MAGOS_VPMALLOC_H__

#include <magos/types.h>

/**
 * Initializes the virtual memory placement malloc mechanism.
 *
 * @param base: base address to use for vmpmalloc.
 * @param limit: max address to use for vmpmalloc.
 */
void vmpmalloc_init(vaddr_t base, vaddr_t limit);

/**
 * Returns the start address of an area of sz bytes or NULL if it fails.
 *
 * @param sz: The size in bytes of the address space to alloc
 */
vaddr_t vmpmalloc(size_t sz);

/**
 * Returns the next free address
 */
vaddr_t vmpmalloc_get_next_addr();

#endif /* ! __MAGOS_VPMALLOC_H__ */
