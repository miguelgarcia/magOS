/*
 * include/magos/const.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-24
 */

/*
 * Global constants in magos
 */

#ifndef __MAGOS_CONST_H__
#define __MAGOS_CONST_H__

#include <asm/const.h>

// Archs:
#define ARCH_IA32 1

#define EXTERN extern

#define NULL ((void *) 0)

#define FALSE 0
#define TRUE 1

#define VM_PAGE_ALIGN(x) (((vaddr_t) x) >> VM_PAGE_SHIFT << VM_PAGE_SHIFT)
#define VM_PAGE_ALIGNED(x) (((vaddr_t) x) == VM_PAGE_ALIGN(x))
#define VM_PAGE_OFFSET_MASK ((vaddr_t) ((1 << VM_PAGE_SHIFT) - 1))


#define PHYS_PAGE_ALIGN(x) (((paddr_t) x) >> PHYS_PAGE_SHIFT << PHYS_PAGE_SHIFT)
#define PHYS_PAGE_ALIGNED(x) (((paddr_t) x) == PHYS_PAGE_ALIGN(x))
#define PHYS_PAGE(x) (((paddr_t) x) >> PHYS_PAGE_SHIFT)
#define PHYS_PAGE_OFFSET_MASK ((paddr_t) ((1 << PHYS_PAGE_SHIFT) - 1))
#define PHYS_PAGE_OFFSET(x) (((paddr_t) x) & PHYS_PAGE_OFFSET_MASK)
#define PHYS_PAGE_ROUND(x) (PHYS_PAGE_ALIGNED(x) ? x : PHYS_PAGE_ALIGN(x) + (1 << PHYS_PAGE_SHIFT))

#endif /* __MAGOS_CONST_H__ */
