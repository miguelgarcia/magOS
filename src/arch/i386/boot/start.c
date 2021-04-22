/*
 * arch/i386/boot/start.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-27
 */

/*
 * System initialization
 */

#include <magos/magos.h>
#include <magos/vmpmalloc.h>

#include <asm/segments.h>
#include <asm/interrupts.h>
#include <asm/vm.h>

#include <multiboot.h>

// TODO: there can be problems if multiboot header or memory map
// cross page boundaries.
// TODO: rename monitor by screen :o)
// TODO: implementar vmpmalloc delloc para liberar el espacio del mboot y mboot mem map

extern paddr_t kaddr_start, kaddr_end;
extern vaddr_t kaddr_virtual_base;

/**
 * Initializes basic video output.
 */
static void boot_init_monitor() {
	vaddr_t vid = vmpmalloc(VIDEO_SIZE);
	if(vid == (vaddr_t) NULL) { 
		kpanic("Couldn't allocate virtual address for screen");
	}
	vm_map_page(vid, VIDEO_ADDR);
	monitor_init(vid);
}

/**
 * Initializes boot memory map.
 *
 * @param mboot Pointer to multiboot information struct.
 */
static void boot_init_mem_map(mboot_info_t *mboot) {
	mboot_memory_map_t *mmap;
	vaddr_t mmap_base;
	size_t map_index;
	
	if(!(mboot->flags & MBOOT_INFO_FLAGS_MEM_MAP)) {
		kpanic("multiboot memory map not present");
	}
	
	mmap_base = vmpmalloc(mboot->mmap_length);
	if(mmap_base == NULL) { 
		kpanic("Couldn't allocate virtual address for multiboot memory map");
	}
		
	vm_map_page(mmap_base, mboot->mmap_addr);
	mmap_base = mmap_base + PHYS_PAGE_OFFSET(mboot->mmap_addr);

	map_index = 0;
	for (mmap = mmap_base; 
		 (unsigned long) mmap < mmap_base + mboot->mmap_length; 
		 mmap = (mboot_memory_map_t *) ((vaddr_t) mmap + mmap->size + sizeof (mmap->size))) {
		 
		g_boot_mem_map[map_index].start = mmap->base_addr_low;
		g_boot_mem_map[map_index].size = mmap->length_low;
			 
		switch(mmap->type) {
			case 1:
	 			g_boot_mem_map[map_index].type = MAGOS_BOOT_MMAP_FREE;
				break;
			default:
				g_boot_mem_map[map_index].type = MAGOS_BOOT_MMAP_RESERVED;
				break;
		}
		
		map_index++;
	}
	
	g_boot_info. mem_map_entries_count = map_index;
	g_boot_info.mmap = &g_boot_mem_map;
}

/**
 * Does low level initialization and then call main.
 *
 * @param pd: pointer to the current PD.
 * @param boot_info: address in physical memory of the multiboot info.
 */
void start(vm_page_directory_t *pd, paddr_t boot_info_ptr)
{
	mboot_info_t *mboot = NULL;
	
	// sets kernel page directory
	vm_kernel_pd = pd;

	// Initialize memory segmentation
	mem_segments_init();

	// Initialize software interrupts
	interrupts_init();
	
	// Load boot info
	g_boot_info.kstart = kaddr_start;
	g_boot_info.ksize = kaddr_end - kaddr_start + 1;
	g_boot_info.kstart_vir = kaddr_virtual_base;
	
	// Initialize vmpmalloc
	// From the end of the kernel to kaddr_virutal_base + 4MB
	// if more is needed we should allocate another page table in boot.s
	vmpmalloc_init(kaddr_virtual_base + kaddr_end + 1, kaddr_virtual_base + 0x003FFFFF - 1);

	// Initialize monitor
	boot_init_monitor();

	// Make the multiboot info readable
	mboot = vmpmalloc(sizeof(mboot_info_t));
	if(mboot == NULL) {
		kpanic("Couldn't allocate address space for mboot");
	}
	vm_map_page(mboot, boot_info_ptr);
	
	// Initialize boot memory map
	boot_init_mem_map(mboot);

	// Call kernel main
	main();
}
