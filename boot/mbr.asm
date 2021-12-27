[org 0x7c00]
KERNEL_OFFSET equ 0x1000 

mov [BOOT_DRIVE], dl 
mov bp, 0x9000
mov sp, bp

mov bx, MSG_16BIT_MODE
call print16
call print16_nl

call load_kernel 
call switch_to_32bit 
jmp $

%include "boot/print-16bit.asm"
%include "boot/print-32bit.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/switch-to-32bit.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print16
    call print16_nl

    mov bx, KERNEL_OFFSET 
    mov dh, 31
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_32BIT:
    mov ebx, MSG_32BIT_MODE
    call print32
    call KERNEL_OFFSET 
    jmp $ 


BOOT_DRIVE db 0 
MSG_16BIT_MODE db "[Sonix] Started in 16-bit Real Mode", 0
MSG_32BIT_MODE db "[Sonix] Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "[Sonix] Loading kernel into memory", 0

times 510 - ($-$$) db 0
dw 0xaa55
