/* multiboot.h - the header for Multiboot */
/* Copyright (C) 1999, 2001  Free Software Foundation, Inc.
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/*
 	Modification: 
 		- Add the ifndef __MULTIBOOT_H__ stuff
 		- MBOOT_INFO_FLAGS_*
	Miguel Angel Garcia <miguel.garcia@gmail.com>
 */

#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#define MBOOT_INFO_FLAGS_MEM 0x1
#define MBOOT_INFO_FLAGS_BOOT_DEVICE 0x2
#define MBOOT_INFO_FLAGS_CMD 0x4
#define MBOOT_INFO_FLAGS_MODULES 0x8
#define MBOOT_INFO_FLAGS_AOUT_SYMS 0x10
#define MBOOT_INFO_FLAGS_ELF_HEADER 0x20
#define MBOOT_INFO_FLAGS_MEM_MAP 0x40
#define MBOOT_INFO_FLAGS_DRIVES 0x80
#define MBOOT_INFO_FLAGS_CONFIG_TABLE 0x100
#define MBOOT_INFO_FLAGS_BOOT_LOADER_NAME 0x200
#define MBOOT_INFO_FLAGS_APM_TABLE 0x400
#define MBOOT_INFO_FLAGS_GRAPHIC_TABLE 0x800

/* Types.  */

/* The Multiboot header.  */
typedef struct mboot_header_s
{
  unsigned long magic;
  unsigned long flags;
  unsigned long checksum;
  unsigned long header_addr;
  unsigned long load_addr;
  unsigned long load_end_addr;
  unsigned long bss_end_addr;
  unsigned long entry_addr;
} mboot_header_t;

/* The symbol table for a.out.  */
typedef struct aout_symbol_table_s
{
  unsigned long tabsize;
  unsigned long strsize;
  unsigned long addr;
  unsigned long reserved;
} aout_symbol_table_t;

/* The section header table for ELF.  */
typedef struct elf_section_header_table_s
{
  unsigned long num;
  unsigned long size;
  unsigned long addr;
  unsigned long shndx;
} elf_section_header_table_t;

/* The Multiboot information.  */
typedef struct mboot_info_s
{
  unsigned long flags;
  unsigned long mem_lower;
  unsigned long mem_upper;
  unsigned long boot_device;
  unsigned long cmdline;
  unsigned long mods_count;
  unsigned long mods_addr;
  union
  {
    aout_symbol_table_t aout_sym;
    elf_section_header_table_t elf_sec;
  } u;
  unsigned long mmap_length;
  unsigned long mmap_addr;
} mboot_info_t;

/* The module structure.  */
typedef struct mboot_module_s
{
  unsigned long mod_start;
  unsigned long mod_end;
  unsigned long string;
  unsigned long reserved;
} mboot_module_t;

/* The memory map. Be careful that the offset 0 is base_addr_low
   but no size.  */
typedef struct mboot_memory_map_s
{
  unsigned long size;
  unsigned long base_addr_low;
  unsigned long base_addr_high;
  unsigned long length_low;
  unsigned long length_high;
  unsigned long type;
} mboot_memory_map_t;


#endif /* ! __MULTIBOOT_H__ */
