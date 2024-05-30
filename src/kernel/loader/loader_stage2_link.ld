ENTRY(_start)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(0x1000)
    {
        *(.text.start)
        *(.text)
    }

    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }

    .data : ALIGN(0x1000)
    {
        *(.data)
    }

    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }
}
