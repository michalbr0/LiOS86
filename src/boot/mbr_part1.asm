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

dd  0x00000000              ; disk id
dw  0x0000                  ; reserved

; first partition table entry
db  0x80                    ; active partition
db  1                       ; starting head
db  1                       ; starting sector
db  0                       ; starting cylinder
db  0x7f                    ; system id
db  15                      ; ending head
db  63                      ; ending sector
db  19                      ; ending cylinder
dd  63                      ; relative starting sector (LBA)
dd  20097                   ; total sectors in partition

; second partition table entry
dq  0
dq  0

; third partition table entry
dq  0
dq  0

; fourth partition table entry
dq  0
dq  0

dw  0xaa55                  ; bootsector signature

times 10321408 db 0
