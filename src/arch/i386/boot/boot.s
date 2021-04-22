[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[GLOBAL kaddr_start]
[GLOBAL kaddr_end]
[GLOBAL kaddr_virtual_base]
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN end]                    ; End of the last loadable section.

MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_CMD_LINE      equ 1<<2    ; Provide your kernel with CMD line
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_CMD_LINE
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB
KERNEL_DIR_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)

section .data

; Page table to map the first 4MB of physical memory
align 4096
boot_page_table:
%assign i 0 
%rep    1024
dd 0x00000003 + (i * 4096)
%assign i i+1 
%endrep

; Kernel page directory
align 0x1000
boot_page_directory:
; vm_page_directory_t.tables_phys
    dd 0x00000003 + boot_page_table - KERNEL_VIRTUAL_BASE
    times (KERNEL_DIR_NUMBER - 1) dd 0                 ; Pages before kernel space.
    ; This page directory entry defines a 4MB page containing the kernel.
    dd 0x00000003 + boot_page_table - KERNEL_VIRTUAL_BASE
    times (1024 - KERNEL_DIR_NUMBER - 1) dd 0  ; Pages after the kernel image.
; vm_page_directory_t.tables
    dd boot_page_table
    times (KERNEL_DIR_NUMBER - 1) dd 0                 ; Pages before kernel space.
    ; This page directory entry defines a 4MB page containing the kernel.
    dd boot_page_table
    times (1024 - KERNEL_DIR_NUMBER - 1) dd 0  ; Pages after the kernel image.
; vm_page_directory_t.phys_addr
	dd boot_page_directory - KERNEL_VIRTUAL_BASE

section .text
[BITS 32]                       ; All instructions should be 32-bit.


[GLOBAL _loader]                 ; Kernel entry point.
[EXTERN start]                 ; This is the entry point of our C code

mboot:
	dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                               ; 4-byte boundary in your kernel file
	dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
	dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct
	dd  mboot                   ; Location of this descriptor
kaddr_start:	dd  code        ; Start of kernel '.text' (code) section.
	dd  bss                     ; End of kernel '.data' section.
kaddr_end:	dd  end            ; End of kernel.
	dd  _loader                 ; Kernel entry point (initial EIP).
kaddr_virtual_base: dd KERNEL_VIRTUAL_BASE ; Kernel start virtual address

_loader:

	; Initialize VM
	; TODO: set CR4 state
	
   mov ecx, (boot_page_directory - KERNEL_VIRTUAL_BASE)
	mov cr3, ecx                  ; Load Page Directory Base Register.
	mov ecx, cr0
	or ecx, 0x80000000            ; enable paging.
;	and ecx, 0x00010000 				; CR0.WP = 0
	mov cr0, ecx

   ; Start fetching instructions in kernel space.
   lea ecx, [StartInHigherHalf]
   jmp ecx

StartInHigherHalf:
;	mov [boot_page_directory], dword 0
	; Load multiboot information:
	mov esp, kernel_stack       ; Setup kernel stack
	push    ebx
	push boot_page_directory
	; Execute the C init:
	cli                   		 ; Disable interrupts.
	call start 
	jmp $                       ; Avoid executing unknown things if start return


section .bss
   resb 8192                    ; Kernel stack
kernel_stack:

