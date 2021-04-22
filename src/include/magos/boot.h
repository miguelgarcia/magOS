/*
 * include/magos/boot.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-29
 */

/*
 * Boot information data structures
 */

#ifndef __MAGOS_BOOT_H__
#define __MAGOS_BOOT_H__

#include <magos/types.h>

/*
 * Types for memory map entries.
 */
#define MAGOS_BOOT_MMAP_FREE 1
#define MAGOS_BOOT_MMAP_RESERVED 2

typedef struct {
	paddr_t start;
	size_t size;
	uint32 type;
} magos_boot_mem_map_t;

typedef struct {
	paddr_t kstart;
	size_t ksize;
	vaddr_t kstart_vir;
	size_t mod_count;
	size_t mem_map_entries_count;
	magos_boot_mem_map_t *mmap;
	char *cmd;
} magos_boot_info_t;

typedef struct {
	paddr_t start;
	size_t size;
	char *cmd;
} magos_boot_module_t;

#endif
