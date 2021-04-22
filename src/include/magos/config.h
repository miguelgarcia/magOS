/*
 * include/magos/config.h
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-12-21
 */

/*
 * magOS configuration
 */

#ifndef __MAGOS_CONFIG_H__
#define __MAGOS_CONFIG_H__

#include <magos/const.h>

#define MAGOS_VERSION "0.1"

#define MAGOS_ARCH ARCH_IA32


/**
 * ARCH specific configuration
 */
#if MAGOS_ARCH == ARCH_IA32

// Minimum assignable memory unit size in bytes
#define PAGE_SIZE   4096

// Kernel command line size in bytes
#define KERNEL_CMD_LINE_SIZE 256

#define VIDEO_ADDR 0xB8000
#define VIDEO_SIZE (25*80*2)

#endif // MAGOS_ARCH == ARCH_IA32

#endif
