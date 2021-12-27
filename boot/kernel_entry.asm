global _start;
[bits 32]

_start:
    [extern start_kernel] 
    call start_kernel
    jmp $