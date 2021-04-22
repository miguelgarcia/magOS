/*
 * kernel/vmpmalloc.h
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

#include <magos/vmpmalloc.h>
#include <magos/const.h>

static vaddr_t _next, _limit;

/**
 * Initializes the virtual memory placement malloc mechanism.
 *
 * @param base: base address to use for vmpmalloc.
 * @param limit: max address to use for vmpmalloc.
 */
void vmpmalloc_init(vaddr_t base, vaddr_t limit) {
	if(!VM_PAGE_ALIGNED(base)) {
		_next = VM_PAGE_ALIGN(base) + (1 << VM_PAGE_SHIFT);
	} else {
		_next = VM_PAGE_ALIGN(base);
	}

	_limit = limit;
}

/**
 * Returns the start address of an area of sz bytes or NULL if it fails.
 *
 * @param sz: The size in bytes of the address space to alloc
 */
vaddr_t vmpmalloc(size_t sz) {
	vaddr_t res;

	if(!VM_PAGE_ALIGNED(sz)) {
		sz = VM_PAGE_ALIGN(sz) + (1 << VM_PAGE_SHIFT);
	}

	if(_next + sz - 1 > _limit) {
		return (vaddr_t) NULL;
	}
	
	res = _next;
	_next = _next + sz;
	return res;
}

/**
 * Returns the next free address
 */
vaddr_t vmpmalloc_get_next_addr() {
	return _next;
}

