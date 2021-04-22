;
; hal/low.s
;
; @author: Miguel Angel Garcia
; @date: 2007-12-24

;
; Routines to manipulate GDTR and the Task register
;

%define L0_DS_OFFSET 0x10
%define L0_CS_OFFSET 0x8

[BITS 32]

[GLOBAL load_gdt]
[GLOBAL load_tss]
[GLOBAL load_idt]

; ------------------------------------------------------------------------------

;
; Loads a GDT into gdtr
; load_gdt(ia32_gdt_ptr_t *)
;

load_gdt:
	mov eax, [esp + 4] 				; Tell the cpu where is the gdt_ptr 
	lgdt [eax]
	
	; load data segment
	mov ax, L0_DS_OFFSET
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp L0_CS_OFFSET:.load_cs
.load_cs:
	ret

; ------------------------------------------------------------------------------

;
; Sets the current TSS
; load_tss(uint16 tss_offset)
;

load_tss:
	mov ax, word [esp + 4]
	ltr ax
	ret

; ------------------------------------------------------------------------------

;
; Sets the current IDT
; load_idt(ia32_idt_ptr_t *)
;

load_idt:
	mov eax, [esp + 4]
	lidt [eax]
	ret
