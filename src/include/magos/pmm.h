/*
 * include/magos/pmm.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-29
 */

/*
 * Physical memory manager
 */

#ifndef __MAGOS_PMM_H__
#define __MAGOS_PMM_H__

#include <magos/types.h>

/**
 * Initializes the physical memory manager
 *
 * @param memsize Physical memory size. 
 */
void pmm_init(size_t memsize);

/**
 * Returns the physical address of a free physical memory page
 * or NULL if no free memory left.
 *
 * @return the physical address of a free physical memory page or NULL if no memory left.
 */
paddr_t pmm_alloc();

/**
 * Marks a physical page as free.
 *
 * @param addr a physical address in the phyisical page.
 */
void pmm_free(paddr_t addr);

#endif /* ! __MAGOS_PMM_H__ */
