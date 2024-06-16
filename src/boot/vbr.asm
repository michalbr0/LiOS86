[org 0x7c5a]                ; VBR starting at 0x7c00, bootstrap code offset 0x5a
[bits 16]

loadBootloader:
.reset:
    mov ah, 0               ; reset disk system mode
    int 0x13
    jc  .reset

.read:
    mov ah, 0x02            ; read sectors from drive mode
    mov al, 49              ; number of sectors to read (dest. 0x7e00-0xdfff)

    ; starting with sector 6184 (LBA) - first file cluster
    ; assuming SPT=63 and HPC=64
    mov ch, 1               ; starting cylinder
    mov dh, 34              ; starting head
    mov cl, 11              ; starting sector

    xor bx, bx
    mov es, bx              ; destination segment
    xor bx, 0x7e00          ; destination offset
    int 0x13
    jc .reset

    jmp 0x0000:0x7e00

times 420-($-$$) db 0
