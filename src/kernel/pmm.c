/*
 * kernel/pmm.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-28
 */

/*
 * Physical memory manager
 *
 * This implementation uses a stack for free pages
 * The stack grows upwards
 *
 * If a page is freed and no space left on the stack then this page
 * is used as stack.
 *
 * When a stack page becomes empty then automatically the page used for
 * stack is the returned by pmm_alloc.
 */

#include <magos/magos.h>
#include <magos/vm.h>
#include <magos/pmm.h>
#include <magos/vmpmalloc.h>

/**
 * Top of the free pages stack.
 */
static paddr_t *top;

/**
 * Count of free physical memory pages.
 */
static size_t free;

/**
 * Initializes the physical memory manager
 *
 * @param memsize Physical memory size. 
 */
void pmm_init(size_t memsize)
{
	top = vmpmalloc(sizeof(paddr_t) * memsize / PHYS_PAGE_SIZE);
	if(top == NULL) {
		kpanic("Couldn't allocate virtual address space in pmm_init.");
	}
	top--;
	free = 0;
}

/**
 * Returns the physical address of a free physical memory page
 * or NULL if no free memory left.
 *
 * @return the physical address of a free physical memory page or NULL if no memory left.
 */
paddr_t pmm_alloc() {
	paddr_t res;

	if(free == 0)
		return 0;

	res = *top;

	if(VM_PAGE_ALIGNED(top)) {
		vm_unmap_page(top);
	}

	top--;
	free--;
	return res;
}

/**
 * Marks a physical page as free.
 *
 * @param addr a physical address in the phyisical page.
 */
void pmm_free(paddr_t addr) {
	addr = PHYS_PAGE_ALIGN(addr);
	top++;
	
	if(VM_PAGE_ALIGNED(top)) {
		vm_map_page(top, PHYS_PAGE_ALIGN(addr));
	}

	*top = addr;
	free++;
}
