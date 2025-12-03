INCLUDE memory_map.ld

SECTIONS 
{
    .text :
    {
        KEEP(*(.vectors))

        *(.text*)

        *(.rodata*)

        . = ALIGN(4);

        _etext = .;
    } > boot

    .data : 
    {
        . = ALIGN(4);
        _sdata = .;

        *(.data*)

        . = ALIGN(4);
        _edata = .;
    } > ram AT > boot

    .bss :
    {
            . = ALIGN(4);
            _sbss = .;

            *(.bss*)
            *(COMMON)

            * = ALIGN(4);
            _ebss = .;
    } > ram
}