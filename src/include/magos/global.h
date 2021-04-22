/*
 * include/magos/global.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2008-01-29
 */

/*
 * Kernel global variables.
 */

#ifndef __MAGOS_GLOBAL_H__
#define __MAGOS_GLOBAL_H__

#include <magos/magos.h>
#include <magos/boot.h>
#include <asm/vm.h>

#ifdef _GLOBAL
#undef EXTERN
#define EXTERN
#endif

/*
 * System information, loaded at boot time.
 */
EXTERN magos_boot_info_t g_boot_info;

// TODO: In future versions space for mem_map should be
// allocated at boot time and freed after use
EXTERN magos_boot_mem_map_t g_boot_mem_map[10];

EXTERN vm_page_directory_t *vm_kernel_pd;

#endif /* ! __MAGOS_GLOBAL_H__ */

