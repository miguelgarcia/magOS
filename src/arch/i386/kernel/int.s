;
; Warning not SMP compatible
;
;

[BITS 32]

[EXTERN isr_handler]

; ------------------------------------------------------------------------------

%macro ISR_NO_ERR_CODE 1
[GLOBAL isr_%1]
isr_%1:
cli					; disable interrupts
push dword 0		; error code
push dword %1		; interrupt vector

jmp common_isr
%endm

; ------------------------------------------------------------------------------

%macro ISR_ERR_CODE 1
[GLOBAL isr_%1]
isr_%1:
cli					; disable interrupts
push dword %1		; interrupt vector

jmp common_isr
%endm

;-------------------------------------------------------------------------------
; Saves CPU context
; this is called after an interrupt
; the kernel stack for this thread will look like this:
;
; ds
; edi
; esi
; ebp
; esp
; ebx
; edx
; ecx
; eax
; interrupt vector
; execption error code
; eip
; cs
; eflags
; old esp							Only if privilege level have changed
; old ss								Only if privilege level have changed
;
; after this ax = ds
;-------------------------------------------------------------------------------

%macro save_cpu_context 0
pushad			; save state
mov ax, ds		; save data segment
push eax
%endm

;-------------------------------------------------------------------------------
; Loads CPU context pointed by esp and saved by save_cpu_context 
;-------------------------------------------------------------------------------

%macro load_cpu_context 0
pop eax
mov ds, ax 		; Loads data segment
mov es, ax
mov fs, ax
mov gs, ax
popad 			; Load registers

add esp, 8		; jump over interrupt vector and exception error code

sti				; enable interrupts
iretd
%endm

;-------------------------------------------------------------------------------
; Common code for all ISRs
;
;-------------------------------------------------------------------------------
common_isr:
; Note: interrupts are disabled
save_cpu_context
mov cx, ss
cmp ax, cx
je .task
mov ds, cx										; if user process then load kernel data segment
mov es, cx
mov fs, cx
mov gs, cx
jmp .notTask
.task:
.notTask:

push esp
call isr_handler								; C code isr
add esp, dword 4
load_cpu_context


;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; The ISRs
;-------------------------------------------------------------------------------
ISR_NO_ERR_CODE 0
ISR_NO_ERR_CODE 1
ISR_NO_ERR_CODE 2
ISR_NO_ERR_CODE 3
ISR_NO_ERR_CODE 4
ISR_NO_ERR_CODE 5
ISR_NO_ERR_CODE 6
ISR_NO_ERR_CODE 7
ISR_ERR_CODE 8
ISR_NO_ERR_CODE 9
ISR_ERR_CODE 10
ISR_ERR_CODE 11
ISR_ERR_CODE 12
ISR_ERR_CODE 13
ISR_ERR_CODE 14
;ISR_NO_ERR_CODE 15
ISR_NO_ERR_CODE 16
ISR_ERR_CODE 17
ISR_NO_ERR_CODE 18
ISR_NO_ERR_CODE 19

;-------------------------------------------------------------------------------
; IRQS ISR
;-------------------------------------------------------------------------------
ISR_NO_ERR_CODE 32
ISR_NO_ERR_CODE 33
ISR_NO_ERR_CODE 34
ISR_NO_ERR_CODE 35
ISR_NO_ERR_CODE 36
ISR_NO_ERR_CODE 37
ISR_NO_ERR_CODE 38
ISR_NO_ERR_CODE 39
ISR_NO_ERR_CODE 40
ISR_NO_ERR_CODE 41
ISR_NO_ERR_CODE 42
ISR_NO_ERR_CODE 43
ISR_NO_ERR_CODE 44
ISR_NO_ERR_CODE 45
ISR_NO_ERR_CODE 46
ISR_NO_ERR_CODE 47


