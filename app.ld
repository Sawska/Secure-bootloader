INCLUDE memory_map.ld

SECTIONS 
{
    .text :
    {
        _stext = .;

        KEEP(*(.vectors))

        KEEP(*(.meta))

        *(.text*)
        *(.rodata*)
        
        . = ALIGN(4);
        _etext = .;
    } > app

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > ram AT > app

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram

    _estack = ORIGIN(ram) + LENGTH(ram);
}