extern _init
extern kloader
extern _fini
extern KERNEL_MEMORY_START_ADDRESS

section .text.start
global _start
_start:
    call _init
    call kloader
    call _fini
    jmp [KERNEL_MEMORY_START_ADDRESS]
