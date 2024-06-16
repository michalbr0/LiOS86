[org 0x7c00]
[bits 16]

    xor ax, ax
    mov ds, ax
    mov es, ax

relocateMbr:
    mov si, 0x7c00
    mov di, 0x7a00
    mov cx, 256
.copyWord:
    lodsw
    stosw
    loop .copyWord

    jmp 0x0000:0x7a20

times 440-($-$$) db 0
