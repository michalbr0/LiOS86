[org 0x7c00]
[bits 16]

loadBootloader:
.reset:
    mov ah, 0               ; reset disk system mode
    int 0x13
    jc  .reset

.read:
    mov ah, 0x02            ; read sectors from drive mode
    mov al, 49              ; number of sectors to read (dest. 0x7e00-0xdfff)
    mov dh, byte [si+1]     ; starting head
    mov cl, byte [si+2]     ; starting sector
    inc cl
    mov ch, byte [si+3]     ; starting cylinder
    xor bx, bx
    mov es, bx              ; destination segment
    xor bx, 0x7e00          ; destination offset
    int 0x13
    jc .reset

    jmp 0x0000:0x7e00

times 510-($-$$) db 0

dw  0xaa55                  ; bootsector signature
