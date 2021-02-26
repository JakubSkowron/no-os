# GRUB, multiboot header
# x86, 32-bit protected mode
# build using cross binutils/gcc --target=i686-elf

# Multiboot header
# [ https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-layout ]
    .section .multiboot
    .align 4
    .set MB_MAGIC, 0x1BADB002  # multiboot magic number
    .set MB_FLAGS, 0x04     # flags: 1 - align boot modules to 4KB boundary
                            #        2 - make mem_* and mmap_* fields available
    .long MB_MAGIC    
    .long MB_FLAGS
    .long - MB_MAGIC - MB_FLAGS   # checksum, all should sum to 0
    .skip 20
    .long 1     # mode_type: EGA text mode
    .long 80    # width
    .long 50    # height
    .long 0     # bpp

# Uninitialized data
    .section .bss
    .align 16
stack_bottom:
    .skip 16384     # 16KB stack
stack_top:

# Code
    .text
    .global kernel_entry
    .global halt
kernel_entry:
    mov $stack_top, %esp    # setup stack
    call kernel_start

halt:
    cli
    hlt
    jmp halt    # if woken by NMI


