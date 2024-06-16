[org 0x7a20]
[bits 16]

checkActivePartition:
    mov si, 0x7bbe
    mov al, byte [si]
    cmp al, 0x80
    je loadVBR
    mov si, 0x7bce
    mov al, byte [si]
    cmp al, 0x80
    je loadVBR
    mov si, 0x7bde
    mov al, byte [si]
    cmp al, 0x80
    je loadVBR
    mov si, 0x7bee
    mov al, byte [si]
    cmp al, 0x80
    je loadVBR
    cli                     ; active partition not found; halt          
    hlt

loadVBR:
.reset:
    mov ah, 0               ; reset disk system mode
    int 0x13
    jc  .reset

.read:
    mov ah, 0x02            ; read sectors from drive mode
    mov al, 1               ; number of sectors to read

    ; reading sector 2048 (LBA)
    ; assuming SPT=63 and HPC=64
    mov ch, 0               ; starting cylinder
    mov dh, 32              ; starting head
    mov cl, 33              ; starting sector
    
    xor bx, bx
    mov es, bx              ; destination segment
    xor bx, 0x7c00          ; destination offset
    int 0x13
    jc .reset

    jmp 0x0000:0x7c00       ; jumping to the loaded VBR
                            ; DS:SI points to the active partition table entry
                            ; CS = 0, DS = 0, ES = 0
                            ; DL = the drive number

times 408-($-$$) db 0
