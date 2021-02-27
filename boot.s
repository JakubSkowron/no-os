# Use BOOTBOOT loader
# x86-64
# build using cross binutils/gcc --target=x86_64-elf

    .text
    .global kernel_entry
    .global halt
    .global get_proc_id
kernel_entry:
    mov  $1, %eax       # cpuid: get processor info
    cpuid
    shr  $24, %ebx      # %ebx bits 31-24: local APIC ID (logical processor)
    movl %ebx, %edi      # 1st argument: APIC ID
    call kernel_start
    jmp  halt

halt:
    cli
    hlt
    jmp halt    # if woken by NMI

