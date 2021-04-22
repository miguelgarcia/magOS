/*
 * kernel/main.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-28
 */

/*
 * magOS initialization
 */

#include <magos/magos.h>
#include <magos/boot.h>
#include <magos/pmm.h>

static size_t get_physical_mem_size() {
	magos_boot_mem_map_t *mmap;
	size_t i, freemem=0;
	
	mmap = g_boot_info.mmap;
	for(i=0; i< g_boot_info.mem_map_entries_count; i++) {
		if(mmap->type == MAGOS_BOOT_MMAP_FREE) {
			freemem += mmap->size;
		}
		mmap++;
	}
	
	return freemem;
}

static void register_free_mem() {
	magos_boot_mem_map_t *mmap;
	paddr_t x;
	size_t i, freemem=0;
	
	mmap = g_boot_info.mmap;
	for(i=0; i< g_boot_info.mem_map_entries_count; i++) {
		if(mmap->type == MAGOS_BOOT_MMAP_FREE) {
			for(x=PHYS_PAGE_ROUND(mmap->start);x < mmap->start + mmap->size; x+=PHYS_PAGE_SIZE)
			{
				// TODO: Avoid freeing kernel or modules memory
				pmm_free(x);
			}
		}
		mmap++;
	}
}

/**
 * magOS main entry point.
 * Initializes architecture independant system parts.
 */
int main() {
	
	// Initialize physical memory manager address space
	pmm_init(get_physical_mem_size());
	register_free_mem();
	
	
	kprintf("running the magOS kernel...");
}
