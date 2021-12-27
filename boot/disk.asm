disk_load:
    pusha
    push dx

    mov ah, 0x02 
    mov al, dh   
    mov cl, 0x02
                
    mov ch, 0x00
    mov dh, 0x00 

    int 0x13      
    jc disk_error 
    pop dx
    cmp al, dh    
    jne sectors_error
    popa
    ret


disk_error:
    mov bx, DISK_ERROR
    call print16
    call print16_nl
    mov dh, ah
    call print16_hex 
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print16

disk_loop:
    jmp $

DISK_ERROR: db "[Sonix] Disk read error", 0
SECTORS_ERROR: db "[Sonix] Incorrect number of sectors read", 0
