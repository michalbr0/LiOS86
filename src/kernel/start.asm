extern _init
extern kmain
extern _fini

section .text.start
global _start
_start:
    call _init
    call kmain
    call _fini
    jmp $
