/* GNU linker script, gcc -T */

ENTRY(kernel_entry)

SECTIONS {
    . = 1M;     /* start at 1MB */

    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)   /* multiboot header */
        *(.text)        /* code */
    }

    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K) {
        *(.bss)
        *(COMMON)   /* everything else */
    }
}