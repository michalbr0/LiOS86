[org 0x7e00]
[bits 16]

loader:
setup_stack:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7a00 
    mov bp, 0x7a00      

detect_memory:
    xor ax, ax
    mov es, ax 
    xor ebx, ebx
    xor bp, bp
    mov word [0x1000], 0        ; memory map entry count
    mov di, 0x1004              ; base address of the memory map  
.loop:
    mov edx, 0x534d4150
    mov eax, 0xe820
    mov ecx, 24
    mov [es:di + 20], dword 1   ; set the ACPI 3.0 Extended Attributes bitfield to 'valid' (in case the result is 20 bytes not extended)
    int 0x15
    cmp ebx, 0
    je  .end_loop
    add di, 24
    inc dword [0x1000]
    jmp .loop
.end_loop:

restore_registers:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7a00 
    mov bp, 0x7a00  

enable_a20:
    in  al, 0x92
    or  al, 2
    out 0x92, al

load_gdt:
    lgdt [gdt_descriptor]

enter_protected_mode:
    mov eax, cr0
    or  eax, 1
    mov cr0, eax
    jmp 0x8:protected_mode_entrypoint

gdt_null_descriptor:
    dd  0
    dd  0
gdt_code_descriptor:        ; offset 0x8 from the start of GDT
    dw  0xffff              ; limit low
    dw  0x0000              ; base low
    db  0x00                ; base mid
    db  10011010b           ; flags
    db  11001111b           ; flags and limit high
    db  0x00                ; base high
gdt_data_descriptor:        ; offset 0x10 from the start of GDT
    dw  0xffff              ; limit low
    dw  0x0000              ; base low
    db  0x00                ; base mid
    db  10010010b           ; flags
    db  11001111b           ; flags and limit high
    db  0x00                ; base high
gdt_end:
gdt_descriptor:
    dw  gdt_end - gdt_null_descriptor - 1           ; size
    dd  gdt_null_descriptor                         ; offset

[bits 32]

protected_mode_entrypoint:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    xor esi, esi
    xor edi, edi
    mov esp, 0x90000
    mov ebp, 0x90000

    jmp 0x8000

times 512-($-$$) db 0
